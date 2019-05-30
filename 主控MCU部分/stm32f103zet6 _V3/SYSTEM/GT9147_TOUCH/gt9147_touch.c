#include "gt9147_touch.h"
const u16 GT9147_TPX_TBL[5]={GT_TP1_REG,GT_TP2_REG,GT_TP3_REG,GT_TP4_REG,GT_TP5_REG};

_m_tp_dev tp_dev=
{
	TP_Init,
	TP_Scan,
	0,
	0,	  	 		
	0,
	0,	  	 		
};					
//默认为touchtype=0的数据.
u8 CMD_RDX=0XD0;
u8 CMD_RDY=0X90;

//电容触摸芯片IIC接口初始化
void CT_IIC_Init(void)
{					     
 	RCC->APB2ENR|=1<<3;		//先使能外设IO PORTB时钟   	
    RCC->APB2ENR|=1<<7;		//先使能外设IO PORTF时钟   	
	
	GPIOB->CRL&=0XFFFFFF0F;	//PB1 推挽输出
	GPIOB->CRL|=0X00000030;	 
	
	GPIOF->CRH&=0XFFFFFF0F;	//PF9 推挽输出
	GPIOF->CRH|=0X00000030;	
	
	GPIOB->ODR|=1<<1;	    //PB1 输出高	 
	GPIOF->ODR|=1<<9;	    //PF9 输出高	 
}
//控制I2C速度的延时
void CT_Delay(void)
{
	DelayUs(5);
} 

//产生IIC起始信号
void CT_IIC_Start(void)
{
	CT_SDA_OUT();     //sda线输出
	CT_IIC_SDA=1;	  	  
	CT_IIC_SCL=1;
	DelayUs(30);
 	CT_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	CT_Delay();
	CT_IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void CT_IIC_Stop(void)
{
	CT_SDA_OUT();//sda线输出
	CT_IIC_SCL=1;
	DelayUs(30);
	CT_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
	CT_Delay();
	CT_IIC_SDA=1;//发送I2C总线结束信号  
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 CT_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	CT_SDA_IN();      //SDA设置为输入  
	CT_IIC_SDA=1;	   
	CT_IIC_SCL=1;
	CT_Delay();
	while(CT_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			CT_IIC_Stop();
			return 1;
		} 
		CT_Delay();
	}
	CT_IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void CT_IIC_Ack(void)
{
	CT_IIC_SCL=0;
	CT_SDA_OUT();
	CT_Delay();
	CT_IIC_SDA=0;
	CT_Delay();
	CT_IIC_SCL=1;
	CT_Delay();
	CT_IIC_SCL=0;
}
//不产生ACK应答		    
void CT_IIC_NAck(void)
{
	CT_IIC_SCL=0;
	CT_SDA_OUT();
	CT_Delay();
	CT_IIC_SDA=1;
	CT_Delay();
	CT_IIC_SCL=1;
	CT_Delay();
	CT_IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void CT_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	CT_SDA_OUT(); 	    
    CT_IIC_SCL=0;//拉低时钟开始数据传输
	CT_Delay();
	for(t=0;t<8;t++)
    {              
        CT_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	      
		CT_IIC_SCL=1; 
		CT_Delay();
		CT_IIC_SCL=0;	
		CT_Delay();
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 CT_IIC_Read_Byte(unsigned char ack)
{
	u8 i,receive=0;
 	CT_SDA_IN();//SDA设置为输入
	DelayUs(30);
	for(i=0;i<8;i++ )
	{ 
		CT_IIC_SCL=0; 	    	   
		CT_Delay();
		CT_IIC_SCL=1;	 
		receive<<=1;
		if(CT_READ_SDA)receive++;   
	}	  				 
	if (!ack)CT_IIC_NAck();//发送nACK
	else CT_IIC_Ack(); //发送ACK   
 	return receive;
}


//从GT9147读出一次数据
//reg:起始寄存器地址
//buf:数据缓缓存区
//len:读数据长度			  
void GT9147_RD_Reg(u16 reg,u8 *buf,u8 len)
{
	u8 i; 
 	CT_IIC_Start();	
 	CT_IIC_Send_Byte(GT_CMD_WR);   //发送写命令 	 
	CT_IIC_Wait_Ack();
 	CT_IIC_Send_Byte(reg>>8);   	//发送高8位地址
	CT_IIC_Wait_Ack(); 	 										  		   
 	CT_IIC_Send_Byte(reg&0XFF);   	//发送低8位地址
	CT_IIC_Wait_Ack();  
 	CT_IIC_Start();  	 	   
	CT_IIC_Send_Byte(GT_CMD_RD);   //发送读命令		   
	CT_IIC_Wait_Ack();	   
	for(i=0;i<len;i++)
	{	   
    	buf[i]=CT_IIC_Read_Byte(i==(len-1)?0:1); //发数据	  
	} 
    CT_IIC_Stop();//产生一个停止条件    
} 

//向GT9147写入一次数据
//reg:起始寄存器地址
//buf:数据缓缓存区
//len:写数据长度
//返回值:0,成功;1,失败.
u8 GT9147_WR_Reg(u16 reg,u8 *buf,u8 len)
{
	u8 i;
	u8 ret=0;
	CT_IIC_Start();	
 	CT_IIC_Send_Byte(GT_CMD_WR);   	//发送写命令 	 
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg>>8);   	//发送高8位地址
	CT_IIC_Wait_Ack(); 	 										  		   
	CT_IIC_Send_Byte(reg&0XFF);   	//发送低8位地址
	CT_IIC_Wait_Ack();  
	for(i=0;i<len;i++)
	{	   
    	CT_IIC_Send_Byte(buf[i]);  	//发数据
		ret=CT_IIC_Wait_Ack();
		if(ret)break;  
	}
    CT_IIC_Stop();					//产生一个停止条件	    
	return ret; 
}
//GT9147配置参数表
//第一个字节为版本号(0X60),必须保证新的版本号大于等于GT9147内部
//flash原有版本号,才会更新配置.
const u8 GT9147_CFG_TBL[]=
{ 
	0X60,0XE0,0X01,0X20,0X03,0X05,0X35,0X00,0X02,0X08,
	0X1E,0X08,0X50,0X3C,0X0F,0X05,0X00,0X00,0XFF,0X67,
	0X50,0X00,0X00,0X18,0X1A,0X1E,0X14,0X89,0X28,0X0A,
	0X30,0X2E,0XBB,0X0A,0X03,0X00,0X00,0X02,0X33,0X1D,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X32,0X00,0X00,
	0X2A,0X1C,0X5A,0X94,0XC5,0X02,0X07,0X00,0X00,0X00,
	0XB5,0X1F,0X00,0X90,0X28,0X00,0X77,0X32,0X00,0X62,
	0X3F,0X00,0X52,0X50,0X00,0X52,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,
	0X0F,0X03,0X06,0X10,0X42,0XF8,0X0F,0X14,0X00,0X00,
	0X00,0X00,0X1A,0X18,0X16,0X14,0X12,0X10,0X0E,0X0C,
	0X0A,0X08,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X29,0X28,0X24,0X22,0X20,0X1F,0X1E,0X1D,
	0X0E,0X0C,0X0A,0X08,0X06,0X05,0X04,0X02,0X00,0XFF,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
	0XFF,0XFF,0XFF,0XFF,
};  
//发送GT9147配置参数
//mode:0,参数不保存到flash
//     1,参数保存到flash
u8 GT9147_Send_Cfg(u8 mode)
{
	u8 buf[2];
	u8 i=0;
	buf[0]=0;
	buf[1]=mode;	//是否写入到GT9147 FLASH?  即是否掉电保存
	for(i=0;i<sizeof(GT9147_CFG_TBL);i++)buf[0]+=GT9147_CFG_TBL[i];//计算校验和
    buf[0]=(~buf[0])+1;
	GT9147_WR_Reg(GT_CFGS_REG,(u8*)GT9147_CFG_TBL,sizeof(GT9147_CFG_TBL));//发送寄存器配置
	GT9147_WR_Reg(GT_CHECK_REG,buf,2);//写入校验和,和配置更新标记
	return 0;
} 

//触摸屏初始化  		    
//返回值:0,没有进行校准
//       1,进行过校准

//初始化GT9147触摸屏
//返回值:0,初始化成功;1,初始化失败 
u8 GT9147_Init(void)
{
	u8 temp[5];  							 
 	RCC->APB2ENR|=1<<7;		//先使能外设IO PORTF时钟 							 
	GPIOF->CRH&=0XFFFF00FF;	
	GPIOF->CRH|=0X00003800;	//PF10 输入 PF11推挽输出   
	GPIOF->ODR|=3<<10;	   	//PF10/11 上拉/输出1 
	CT_IIC_Init();      	//初始化电容屏的I2C总线  
	GT_RST=0;				//复位
	DelayMs(10);
 	GT_RST=1;				//释放复位 
	DelayMs(10);
	GPIOF->CRH&=0XFFFFF0FF;	//清除原来设置
	GPIOF->CRH|=0X00000800;	//PF10 下拉输入	 
	GPIOF->ODR&=~(1<<10);	//PF10 下拉
 	DelayMs(100);  
	GT9147_RD_Reg(GT_PID_REG,temp,4);	//读取产品ID
	temp[4]=0;
	printf("CTP ID:%s\r\n",temp);		//打印ID
	if(strcmp((char*)temp,"9147")==0)	//ID==9147
	{
		temp[0]=0X02;			
		GT9147_WR_Reg(GT_CTRL_REG,temp,1);//软复位GT9147
 		GT9147_RD_Reg(GT_CFGS_REG,temp,1);//读取GT_CFGS_REG寄存器
		if(temp[0]<0X60)//默认版本比较低,需要更新flash配置
		{
			printf("Default Ver:%d\r\n",temp[0]);
			GT9147_Send_Cfg(1);//更新并保存配置
		}
		DelayMs(10);
		temp[0]=0X00;	 
		GT9147_WR_Reg(GT_CTRL_REG,temp,1);	//结束复位   	
		return 0;
	} 
	return 1;
}

//扫描触摸屏(采用查询方式)
//mode:0,正常扫描.
//返回值:当前触屏状态.
//0,触屏无触摸;1,触屏有触摸
u8 GT9147_Scan(u8 mode)
{
	u8 buf[4];
	u8 i=0;
	u8 res=0;
	u8 temp;
	u8 tempsta;
 	static u8 t=0;//控制查询间隔,从而降低CPU占用率   
	t++;
	if((t%10)==0||t<10)//空闲时,每进入10次CTP_Scan函数才检测1次,从而节省CPU使用率
	{
		GT9147_RD_Reg(GT_GSTID_REG,&mode,1);	//读取触摸点的状态  
 		if(mode&0X80&&((mode&0XF)<6))
		{
			temp=0;
			GT9147_WR_Reg(GT_GSTID_REG,&temp,1);//清标志 		
		}		
		if((mode&0XF)&&((mode&0XF)<6))
		{
			temp=0XFF<<(mode&0XF);		//将点的个数转换为1的位数,匹配tp_dev.sta定义 
			tempsta=tp_dev.sta;			//保存当前的tp_dev.sta值
			tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES; 
			tp_dev.x[4]=tp_dev.x[0];	//保存触点0的数据
			tp_dev.y[4]=tp_dev.y[0];
			for(i=0;i<5;i++)
			{
				if(tp_dev.sta&(1<<i))	//触摸有效?
				{
					GT9147_RD_Reg(GT9147_TPX_TBL[i],buf,4);	//读取XY坐标值
					if(tp_dev.touchtype&0X01)//横屏
					{
						tp_dev.y[i]=((u16)buf[1]<<8)+buf[0];
						tp_dev.x[i]=800-(((u16)buf[3]<<8)+buf[2]);
					}else
					{
						tp_dev.x[i]=((u16)buf[1]<<8)+buf[0];
						tp_dev.y[i]=((u16)buf[3]<<8)+buf[2];
					}  
					//printf("x[%d]:%d,y[%d]:%d\r\n",i,tp_dev.x[i],i,tp_dev.y[i]);
				}			
			} 
			res=1;
			if(tp_dev.x[0]>lcddev.width||tp_dev.y[0]>lcddev.height)//非法数据(坐标超出了)
			{ 
				if((mode&0XF)>1)		//有其他点有数据,则复第二个触点的数据到第一个触点.
				{
					tp_dev.x[0]=tp_dev.x[1];
					tp_dev.y[0]=tp_dev.y[1];
					t=0;				//触发一次,则会最少连续监测10次,从而提高命中率
				}else					//非法数据,则忽略此次数据(还原原来的)  
				{
					tp_dev.x[0]=tp_dev.x[4];
					tp_dev.y[0]=tp_dev.y[4];
					mode=0X80;		
					tp_dev.sta=tempsta;	//恢复tp_dev.sta
				}
			}else t=0;					//触发一次,则会最少连续监测10次,从而提高命中率
		}
	}
	if((mode&0X8F)==0X80)//无触摸点按下
	{ 
		if(tp_dev.sta&TP_PRES_DOWN)	//之前是被按下的
		{
			tp_dev.sta&=~(1<<7);	//标记按键松开
		}else						//之前就没有被按下
		{ 
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
			tp_dev.sta&=0XE0;	//清除点有效标记	
		}	 
	} 	
	if(t>240)t=10;//重新从10开始计数
	return res;
}
 

u8 TP_Init(void)
{	
	GT9147_Init();
	tp_dev.scan=GT9147_Scan;
	tp_dev.touchtype|=0X80;			//电容屏 
	tp_dev.touchtype|=lcddev.dir&0X01;//横屏还是竖屏 
	return 0;
}



//SPI写数据
//向触摸屏IC写入1byte数据    
//num:要写入的数据
void TP_Write_Byte(u8 num)    
{  
	u8 count=0;   
	for(count=0;count<8;count++)  
	{ 	  
		if(num&0x80)TDIN=1;  
		else TDIN=0;   
		num<<=1;    
		TCLK=0; 
		DelayUs(1);
		TCLK=1;		//上升沿有效	        
	}		 			    
} 		 
//SPI读数据 
//从触摸屏IC读取adc值
//CMD:指令
//返回值:读到的数据	   
u16 TP_Read_AD(u8 CMD)	  
{ 	 
	u8 count=0; 	  
	u16 Num=0; 
	TCLK=0;		//先拉低时钟 	 
	TDIN=0; 	//拉低数据线
	TCS=0; 		//选中触摸屏IC
	TP_Write_Byte(CMD);//发送命令字
	DelayUs(6);//ADS7846的转换时间最长为6us
	TCLK=0; 	     	    
	DelayUs(1);    	   
	TCLK=1;		//给1个时钟，清除BUSY
	DelayUs(1);    
	TCLK=0; 	     	    
	for(count=0;count<16;count++)//读出16位数据,只有高12位有效 
	{ 				  
		Num<<=1; 	 
		TCLK=0;	//下降沿有效  	    	   
		DelayUs(1);    
 		TCLK=1;
 		if(DOUT)Num++; 		 
	}  	
	Num>>=4;   	//只有高12位有效.
	TCS=1;		//释放片选	 
	return(Num);   
}
//读取一个坐标值(x或者y)
//连续读取READ_TIMES次数据,对这些数据升序排列,
//然后去掉最低和最高LOST_VAL个数,取平均值 
//xy:指令（CMD_RDX/CMD_RDY）
//返回值:读到的数据
#define READ_TIMES 5 	//读取次数
#define LOST_VAL 1	  	//丢弃值
u16 TP_Read_XOY(u8 xy)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum=0;
	u16 temp;
	for(i=0;i<READ_TIMES;i++)buf[i]=TP_Read_AD(xy);		 		    
	for(i=0;i<READ_TIMES-1; i++)//排序
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//升序排列
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
} 


//读取x,y坐标
//最小值不能少于100.
//x,y:读取到的坐标值
//返回值:0,失败;1,成功。
u8 TP_Read_XY(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=TP_Read_XOY(CMD_RDX);
	ytemp=TP_Read_XOY(CMD_RDY);	  												   
	//if(xtemp<100||ytemp<100)return 0;//读数失败
	*x=xtemp;
	*y=ytemp;
	return 1;//读数成功
}

//连续2次读取触摸屏IC,且这两次的偏差不能超过
//ERR_RANGE,满足条件,则认为读数正确,否则读数错误.	   
//该函数能大大提高准确度
//x,y:读取到的坐标值
//返回值:0,失败;1,成功。
#define ERR_RANGE 50 //误差范围 
u8 TP_Read_XY2(u16 *x,u16 *y) 
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;    
    flag=TP_Read_XY(&x1,&y1);   
    if(flag==0)return(0);
    flag=TP_Read_XY(&x2,&y2);	   
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//前后两次采样在+-50内
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }else return 0;	  
}  

//////////////////////////////////////////////////////////////////////////////////		  
//触摸按键扫描
//tp:0,屏幕坐标;1,物理坐标(校准等特殊场合用)
//返回值:当前触屏状态.
//0,触屏无触摸;1,触屏有触摸
u8 TP_Scan(u8 tp)
{			   
	if(PEN==0)//有按键按下
	{
		TP_Read_XY2(&tp_dev.x[0],&tp_dev.y[0]);//读取物理坐标
		printf("tp_dev.x[0]=%d   tp_dev.y[0]=%d\n",tp_dev.x[0],tp_dev.y[0]);
		if((tp_dev.sta&TP_PRES_DOWN)==0)//之前没有被按下
		{		 
			tp_dev.sta=TP_PRES_DOWN|TP_CATH_PRES;//按键按下  
			tp_dev.x[4]=tp_dev.x[0];//记录第一次按下时的坐标
			tp_dev.y[4]=tp_dev.y[0];  	   			 
		}			   
	}else
	{
		if(tp_dev.sta&TP_PRES_DOWN)//之前是被按下的
		{
			tp_dev.sta&=~(1<<7);//标记按键松开	
		}else//之前就没有被按下
		{
			tp_dev.x[4]=0;
			tp_dev.y[4]=0;
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
		}	    
	}
	return tp_dev.sta&TP_PRES_DOWN;//返回当前的触屏状态
}	  
//////////////////////////////////////////////////////////////////////////	 

