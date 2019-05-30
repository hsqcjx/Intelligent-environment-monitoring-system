//文件名是 dht11.c
#include "dht11.h"
#include "includes.h" //加入 UCOS_II 的头文件
//防止在与硬件通信时发生死循环的计数范围
#define NUMBER 20
#define SIZE 5
static unsigned char status;
//存放五字节数据的数组
static unsigned char value_array[SIZE];
/*可在其他的文件引用温湿度值,实际是温度的整数的 10 倍
如 dht11 读回的温度是 26,则 temp_value = 260, 湿度同理*/
int temp_value, humi_value;
static unsigned char ReadValue(void);
extern void Delay_1ms(unsigned int ms)
{
	DelayMs(ms);
}
static void DHT11_Delay_10us(void)
{
//	OSTimeDlyHMSM(0,0,0,500);
	DelayUs(10);
}
/*读一个字节的数据*/
static unsigned char DHT11_ReadValue(void)
{
	unsigned char count, value = 0, i;
	status = OK; //设定标志为正常状态
	DHT11_IN_MODE;
	for(i = 8; i > 0; i--)
	{
		//高位在先
		value <<= 1;
		count = 0;
//		每一位数据前会有一个 50us 的低电平时间.等待 50us 低电平结束
		while(dht11_in == 0 && count++ < NUMBER)
		{
			DHT11_Delay_10us();
		}
		if(count >= NUMBER)
		{
			printf("111\n");
			status = ERROR; //设定错误标志
			return 0; //函数执行过程发生错误就退出函数
		}
		//26-28us 的高电平表示该位是 0,为 70us 高电平表该位 1
		DHT11_Delay_10us();   //		延时 30us 后检测数据线是否还是高电平
		DHT11_Delay_10us();
		DHT11_Delay_10us();
		if(dht11_in != 0)
		{
			value++;  //进入这里表示该位是 1
			//等待剩余(约 40us)的高电平结束
			count=0;
			while(dht11_in != 0 && count++ < NUMBER)
			{
				DHT11_Delay_10us();
				DHT11_OUT_MODE;
				dht11_out = 1;
				DHT11_IN_MODE
			}
			if(count >= NUMBER)
			{
				status = ERROR; //设定错误标志
				return 0;
			} 
		}
	} 
	return (value);
}
//读温度和湿度函数，读一次的数据,共五字节，读出成功函数返回 OK, 错误返回 ERROR
extern unsigned char DHT11_ReadTempAndHumi(void)
{ 
	unsigned char i = 0, check_value = 0,count = 0;
	DHT11_OUT_MODE;
	dht11_out = 0; //拉低数据线大于 18ms 发送开始信号
	Delay_1ms(20); //需大于 18 毫秒
	dht11_out = 1;  //释放数据线,用于检测低电平的应答信号
	//延时 20-40us,等待一段时间后检测应答信号,应答信号是从机拉低数据线 80us
	DHT11_IN_MODE;
	DHT11_Delay_10us();
	DHT11_Delay_10us();
	DHT11_Delay_10us();
	DHT11_Delay_10us();
	if(dht11_in != 0) //检测应答信号,应答信号是低电平
	{
//		printf("No ACK\n");
		//没应答信号
		return ERROR;
	}
	else
	{
		//有应答信号
		while(dht11_in == 0 && count++ < NUMBER) //等待应答信号结束
		{
			DHT11_Delay_10us();
		}
		if(count >= NUMBER) //检测计数器是否超过了设定的范围
		{
			printf("ACK Error\n");
			DHT11_OUT_MODE;
			dht11_out = 1;
			return ERROR;  //读数据出错,退出函数
		}
//		printf("ACK Success\n");
//		dht11_out = 0;
//		dht11_out = 1;//释放数据线
//		DHT11_IN_MODE
		//应答信号后会有一个 80us 的高电平，等待高电平结束
		while(dht11_in != 0 && count++ < NUMBER)
		{
			DHT11_Delay_10us();
		}
		if(count >= NUMBER)
		{
			printf("High TIne\n");
			DHT11_OUT_MODE;
			dht11_out = 1;
			return ERROR; //退出函数
		}
		//读出湿.温度值 
		for(i = 0; i < SIZE; i++)
		{
			value_array[i] = DHT11_ReadValue();
			if(status == ERROR)//调用 ReadValue()读数据出错会设定 status 为 ERROR
			{
				printf("Read Data Error\n");
				DHT11_OUT_MODE;
				dht11_out = 1; 
				return ERROR; 
			}
//			printf("value_array[i]=%d\n",value_array[i]);
			//读出的最后一个值是校验值不需加上去
			if(i != SIZE - 1) 
			{
				//读出的五字节数据中的前四字节数据和等于第五字节数据表示成功
				check_value += value_array[i];
			}
		}//end for
		//在没用发生函数调用失败时进行校验
		if(check_value == value_array[SIZE - 1])
		{
			//将温湿度扩大 10 倍方便分离出每一位
			humi_value = value_array[0] * 10+value_array[1];
			temp_value = value_array[2] * 10+value_array[3];
			DHT11_OUT_MODE;
			dht11_out = 1; 	
			printf("humi_value=%d  temp_value=%d\n",humi_value,temp_value);
			return OK; //正确的读出 dht11 输出的数据 
		}
		else
		{
			//校验数据出错 
			return ERROR;
		}
	} 
}