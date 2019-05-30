//�ļ����� dht11.c
#include "dht11.h"
#include "includes.h" //���� UCOS_II ��ͷ�ļ�
//��ֹ����Ӳ��ͨ��ʱ������ѭ���ļ�����Χ
#define NUMBER 20
#define SIZE 5
static unsigned char status;
//������ֽ����ݵ�����
static unsigned char value_array[SIZE];
/*�����������ļ�������ʪ��ֵ,ʵ�����¶ȵ������� 10 ��
�� dht11 ���ص��¶��� 26,�� temp_value = 260, ʪ��ͬ��*/
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
/*��һ���ֽڵ�����*/
static unsigned char DHT11_ReadValue(void)
{
	unsigned char count, value = 0, i;
	status = OK; //�趨��־Ϊ����״̬
	DHT11_IN_MODE;
	for(i = 8; i > 0; i--)
	{
		//��λ����
		value <<= 1;
		count = 0;
//		ÿһλ����ǰ����һ�� 50us �ĵ͵�ƽʱ��.�ȴ� 50us �͵�ƽ����
		while(dht11_in == 0 && count++ < NUMBER)
		{
			DHT11_Delay_10us();
		}
		if(count >= NUMBER)
		{
			printf("111\n");
			status = ERROR; //�趨�����־
			return 0; //����ִ�й��̷���������˳�����
		}
		//26-28us �ĸߵ�ƽ��ʾ��λ�� 0,Ϊ 70us �ߵ�ƽ���λ 1
		DHT11_Delay_10us();   //		��ʱ 30us �����������Ƿ��Ǹߵ�ƽ
		DHT11_Delay_10us();
		DHT11_Delay_10us();
		if(dht11_in != 0)
		{
			value++;  //���������ʾ��λ�� 1
			//�ȴ�ʣ��(Լ 40us)�ĸߵ�ƽ����
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
				status = ERROR; //�趨�����־
				return 0;
			} 
		}
	} 
	return (value);
}
//���¶Ⱥ�ʪ�Ⱥ�������һ�ε�����,�����ֽڣ������ɹ��������� OK, ���󷵻� ERROR
extern unsigned char DHT11_ReadTempAndHumi(void)
{ 
	unsigned char i = 0, check_value = 0,count = 0;
	DHT11_OUT_MODE;
	dht11_out = 0; //���������ߴ��� 18ms ���Ϳ�ʼ�ź�
	Delay_1ms(20); //����� 18 ����
	dht11_out = 1;  //�ͷ�������,���ڼ��͵�ƽ��Ӧ���ź�
	//��ʱ 20-40us,�ȴ�һ��ʱ�����Ӧ���ź�,Ӧ���ź��Ǵӻ����������� 80us
	DHT11_IN_MODE;
	DHT11_Delay_10us();
	DHT11_Delay_10us();
	DHT11_Delay_10us();
	DHT11_Delay_10us();
	if(dht11_in != 0) //���Ӧ���ź�,Ӧ���ź��ǵ͵�ƽ
	{
//		printf("No ACK\n");
		//ûӦ���ź�
		return ERROR;
	}
	else
	{
		//��Ӧ���ź�
		while(dht11_in == 0 && count++ < NUMBER) //�ȴ�Ӧ���źŽ���
		{
			DHT11_Delay_10us();
		}
		if(count >= NUMBER) //���������Ƿ񳬹����趨�ķ�Χ
		{
			printf("ACK Error\n");
			DHT11_OUT_MODE;
			dht11_out = 1;
			return ERROR;  //�����ݳ���,�˳�����
		}
//		printf("ACK Success\n");
//		dht11_out = 0;
//		dht11_out = 1;//�ͷ�������
//		DHT11_IN_MODE
		//Ӧ���źź����һ�� 80us �ĸߵ�ƽ���ȴ��ߵ�ƽ����
		while(dht11_in != 0 && count++ < NUMBER)
		{
			DHT11_Delay_10us();
		}
		if(count >= NUMBER)
		{
			printf("High TIne\n");
			DHT11_OUT_MODE;
			dht11_out = 1;
			return ERROR; //�˳�����
		}
		//����ʪ.�¶�ֵ 
		for(i = 0; i < SIZE; i++)
		{
			value_array[i] = DHT11_ReadValue();
			if(status == ERROR)//���� ReadValue()�����ݳ�����趨 status Ϊ ERROR
			{
				printf("Read Data Error\n");
				DHT11_OUT_MODE;
				dht11_out = 1; 
				return ERROR; 
			}
//			printf("value_array[i]=%d\n",value_array[i]);
			//���������һ��ֵ��У��ֵ�������ȥ
			if(i != SIZE - 1) 
			{
				//���������ֽ������е�ǰ���ֽ����ݺ͵��ڵ����ֽ����ݱ�ʾ�ɹ�
				check_value += value_array[i];
			}
		}//end for
		//��û�÷�����������ʧ��ʱ����У��
		if(check_value == value_array[SIZE - 1])
		{
			//����ʪ������ 10 ����������ÿһλ
			humi_value = value_array[0] * 10+value_array[1];
			temp_value = value_array[2] * 10+value_array[3];
			DHT11_OUT_MODE;
			dht11_out = 1; 	
			printf("humi_value=%d  temp_value=%d\n",humi_value,temp_value);
			return OK; //��ȷ�Ķ��� dht11 ��������� 
		}
		else
		{
			//У�����ݳ��� 
			return ERROR;
		}
	} 
}