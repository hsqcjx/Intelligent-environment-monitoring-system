#ifndef GT9147_TOUCH_H
#define GT9147_TOUCH_H
#include "stm32f10x.h"
#include <stdio.h>
#include "sys.h"
#include "delay.h"
#include "string.h"
#include "nt35310_lcd.h" 	 
//#include "lcd.h" 
#include "stdlib.h"
#include "math.h"

//IO��������
#define CT_SDA_IN()  {GPIOF->CRH&=0XFFFFFF0F;GPIOF->CRH|=8<<4;}
#define CT_SDA_OUT() {GPIOF->CRH&=0XFFFFFF0F;GPIOF->CRH|=3<<4;}

//IO��������	 
#define CT_IIC_SCL    PBout(1) 			//SCL     
#define CT_IIC_SDA    PFout(9) 			//SDA	 
#define CT_READ_SDA   PFin(9)  			//����SDA 

//IO��������	   
#define GT_RST    		PFout(11)	//GT9147��λ����
#define GT_INT    		PFin(10)	//GT9147�ж�����	

//I2C��д����	
#define GT_CMD_WR 		0X28     	//д����
#define GT_CMD_RD 		0X29		//������
  
//GT9147 ���ּĴ������� 
#define GT_CTRL_REG 	0X8040   	//GT9147���ƼĴ���
#define GT_CFGS_REG 	0X8047   	//GT9147������ʼ��ַ�Ĵ���
#define GT_CHECK_REG 	0X80FF   	//GT9147У��ͼĴ���
#define GT_PID_REG 		0X8140   	//GT9147��ƷID�Ĵ���

#define GT_GSTID_REG 	0X814E   	//GT9147��ǰ��⵽�Ĵ������
#define GT_TP1_REG 		0X8150  	//��һ�����������ݵ�ַ
#define GT_TP2_REG 		0X8158		//�ڶ������������ݵ�ַ
#define GT_TP3_REG 		0X8160		//���������������ݵ�ַ
#define GT_TP4_REG 		0X8168		//���ĸ����������ݵ�ַ
#define GT_TP5_REG 		0X8170		//��������������ݵ�ַ  


//����/������оƬ��������	   
#define PEN  		PFin(10)  	//PF10 INT
#define DOUT 		PBin(2)   	//PB2  MISO
#define TDIN 		PFout(9)  	//PF9  MOSI
#define TCLK 		PBout(1)  	//PB1  SCLK
#define TCS  		PFout(11)  	//PF11  CS 

#define TP_PRES_DOWN 0x80  		//����������	  
#define TP_CATH_PRES 0x40  		//�а��������� 
#define CT_MAX_TOUCH  5    		//������֧�ֵĵ���,�̶�Ϊ5��

//������������
typedef struct 
{
	u8 (*init)(void);			//��ʼ��������������
	u8 (*scan)(u8);				//ɨ�败����.0,��Ļɨ��;1,��������;	 
	u16 x[CT_MAX_TOUCH]; 		//��ǰ����
	u16 y[CT_MAX_TOUCH];		//�����������5������,����������x[0],y[0]����:�˴�ɨ��ʱ,����������,��
								//x[4],y[4]�洢��һ�ΰ���ʱ������. 
	u8  sta;					//�ʵ�״̬ 
								//b7:����1/�ɿ�0; 
	                            //b6:0,û�а�������;1,�а�������. 
								//b5:����
								//b4~b0:���ݴ��������µĵ���(0,��ʾδ����,1��ʾ����)
  
//�����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
//b0:0,����(�ʺ�����ΪX����,����ΪY�����TP)
//   1,����(�ʺ�����ΪY����,����ΪX�����TP) 
//b1~6:����.
//b7:0,������
//   1,������ 
	u8 touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;	 	//������������touch.c���涨��


u8 TP_Scan(u8 tp);								//ɨ��
u8 TP_Init(void);								//��ʼ��

u8 GT9147_Init(void);
u8 GT9147_WR_Reg(u16 reg,u8 *buf,u8 len);
void GT9147_RD_Reg(u16 reg,u8 *buf,u8 len);
u8 GT9147_Send_Cfg(u8 mode);
u8 GT9147_Scan(u8 mode); 
#endif
