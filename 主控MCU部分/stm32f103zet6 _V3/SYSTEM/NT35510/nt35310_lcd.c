#include "nt35310_lcd.h"


//LCD�Ļ�����ɫ�ͱ���ɫ	   
u16 POINT_COLOR=0x0000;	//������ɫ
u16 BACK_COLOR=0xFFFF;  //����ɫ 


	
 
#define NT35310_LCD_REG *(u16*)(0x60000000)
#define NT35310_LCD_DAT *(u16*)(0x60200000) //0110 0000 0010 0000 0000 0000 0000 0000

/*
NT35310_LCD_REG=0x12345; //LCD����Ϊ���͵�������
NT35310_LCD_DAT=0x12345; //LCD����Ϊ���͵�������

FSMC��ַ��:  FSMC_A0~FSMC_A15  0x0000
FSMC������:  FSMC_D0~FSMC_D15  �Ͼͻ���ֳ�0x12345������ݡ�
*/


void NT35310_LCD_Init(void)
{
    /*1. ��ʱ��*/
    RCC->AHBENR|=1<<8;  //����FSMCʱ��
    RCC->APB2ENR|=1<<3; //PB
    RCC->APB2ENR|=1<<5; //PD
    RCC->APB2ENR|=1<<6; //PE
  

	  /*2. ��ʼ��LCD������*/
    GPIOB->CRL&=0xFFFFFFF0;		//����LED
    GPIOB->CRL|=0x00000003;  
    
		GPIOD->CRL&=0x0F00FFFF;
    GPIOD->CRL|=0xB0BB0000;
		
		GPIOE->CRL&=0xFFF0FFFF;
    GPIOE->CRL|=0x000B0000;		
		
		/*. ��ʼ��������*/
		GPIOD->CRL&=0xFFFFFF00;
    GPIOD->CRL|=0x000000BB;		
		
		GPIOD->CRH&=0x00FFF000;
    GPIOD->CRH|=0xBB000BBB;

		GPIOE->CRL&=0x0FFFFFFF;
    GPIOE->CRL|=0xB0000000;
		
		GPIOE->CRH&=0x00000000;
    GPIOE->CRH|=0xBBBBBBBB;



    /*4. ����FSMC���ļĴ���*/
    FSMC_Bank1->BTCR[0]=0; //BCR
    FSMC_Bank1->BTCR[1]=0; //BTR

    FSMC_Bank1->BTCR[0]|=1<<12; //дʹ��
    FSMC_Bank1->BTCR[0]|=1<<4;  //16λ���
    
    FSMC_Bank1->BTCR[1]|=0x1<<8; //�������ݱ��ֵ�ʱ��
                                 //16��HCLKʱ������
    FSMC_Bank1->BTCR[0]|=1<<0;   //����FSMC��1
    
    DelayMs(120); //�ȴ�LCD����λ�ɹ�
    
    /*4. ��ʼ��LCD������оƬ*/
    NT35310_LCD_WriteReg(0xED);
    NT35310_LCD_WriteData(0x01);
    NT35310_LCD_WriteData(0xFE);
    NT35310_LCD_WriteReg(0xEE);
    NT35310_LCD_WriteData(0xDE);
    NT35310_LCD_WriteData(0x21);
    NT35310_LCD_WriteReg(0xF1);
    NT35310_LCD_WriteData(0x01);
    NT35310_LCD_WriteReg(0xDF);
    NT35310_LCD_WriteData(0x10);
   
    //VCOMvoltage//
    NT35310_LCD_WriteReg(0xC4);
    NT35310_LCD_WriteData(0x8F); //5f
    NT35310_LCD_WriteReg(0xC6);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xE2);
    NT35310_LCD_WriteData(0xE2);
    NT35310_LCD_WriteData(0xE2);
    NT35310_LCD_WriteReg(0xBF);
    NT35310_LCD_WriteData(0xAA);
    NT35310_LCD_WriteReg(0xB0);
    NT35310_LCD_WriteData(0x0D);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x0D);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x11);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x19);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x21);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x2D);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x3D);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x5D);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x5D);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xB1);
    NT35310_LCD_WriteData(0x80);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x8B);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x96);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xB2);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x02);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x03);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xB3);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xB4);
    NT35310_LCD_WriteData(0x8B);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x96);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xA1);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xB5);
    NT35310_LCD_WriteData(0x02);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x03);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x04);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xB6);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xB7);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x3F);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x5E);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x64);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x8C);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xAC);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xDC);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x70);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x90);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xEB);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xDC);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xB8);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xBA);
    NT35310_LCD_WriteData(0x24);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xC1);
    NT35310_LCD_WriteData(0x20);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x54);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xFF);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xC2);
    NT35310_LCD_WriteData(0x0A);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x04);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xC3);
    NT35310_LCD_WriteData(0x3C);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x3A);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x39);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x37);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x3C);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x36);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x32);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x2F);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x2C);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x29);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x26);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x24);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x24);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x23);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x3C);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x36);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x32);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x2F);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x2C);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x29);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x26);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x24);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x24);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x23);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xC4);
    NT35310_LCD_WriteData(0x62);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x05);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x84);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xF0);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x18);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xA4);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x18);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x50);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x0C);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x17);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x95);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xF3);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xE6);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xC5);
    NT35310_LCD_WriteData(0x32);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x44);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x65);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x76);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x88);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xC6);
    NT35310_LCD_WriteData(0x20);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x17);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x01);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xC7);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xC8);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xC9);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xE0);
    NT35310_LCD_WriteData(0x16);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x1C);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x21);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x36);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x46);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x52);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x64);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x7A);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x8B);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x99);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xA8);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xB9);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xC4);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xCA);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xD2);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xD9);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xE0);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xF3);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xE1);
    NT35310_LCD_WriteData(0x16);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x1C);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x22);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x36);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x45);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x52);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x64);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x7A);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x8B);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x99);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xA8);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xB9);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xC4);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xCA);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xD2);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xD8);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xE0);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xF3);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xE2);
    NT35310_LCD_WriteData(0x05);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x0B);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x1B);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x34);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x44);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x4F);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x61);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x79);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x88);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x97);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xA6);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xB7);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xC2);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xC7);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xD1);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xD6);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xDD);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xF3);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xE3);
    NT35310_LCD_WriteData(0x05);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xA);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x1C);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x33);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x44);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x50);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x62);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x78);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x88);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x97);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xA6);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xB7);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xC2);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xC7);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xD1);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xD5);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xDD);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xF3);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xE4);
    NT35310_LCD_WriteData(0x01);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x01);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x02);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x2A);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x3C);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x4B);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x5D);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x74);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x84);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x93);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xA2);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xB3);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xBE);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xC4);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xCD);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xD3);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xDD);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xF3);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xE5);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x02);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x29);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x3C);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x4B);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x5D);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x74);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x84);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x93);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xA2);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xB3);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xBE);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xC4);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xCD);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xD3);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xDC);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xF3);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xE6);
    NT35310_LCD_WriteData(0x11);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x34);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x56);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x76);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x77);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x66);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x88);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x99);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xBB);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x99);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x66);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x55);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x55);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x45);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x43);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x44);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xE7);
    NT35310_LCD_WriteData(0x32);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x55);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x76);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x66);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x67);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x67);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x87);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x99);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xBB);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x99);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x77);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x44);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x56);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x23);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x33);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x45);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xE8);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x99);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x87);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x88);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x77);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x66);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x88);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xAA);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0xBB);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x99);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x66);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x55);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x55);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x44);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x44);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x55);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xE9);
    NT35310_LCD_WriteData(0xAA);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0x00);
    NT35310_LCD_WriteData(0xAA);
    NT35310_LCD_WriteReg(0xCF);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xF0);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x50);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xF3);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0xF9);
    NT35310_LCD_WriteData(0x06);
    NT35310_LCD_WriteData(0x10);
    NT35310_LCD_WriteData(0x29);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0x3A);
    NT35310_LCD_WriteData(0x55);
    NT35310_LCD_WriteReg(0x11);
    DelayMs(100);
    NT35310_LCD_WriteReg(0x29);
    NT35310_LCD_WriteReg(0x35);
    NT35310_LCD_WriteData(0x00);
    NT35310_LCD_WriteReg(0x51);
    NT35310_LCD_WriteData(0xFF);
    NT35310_LCD_WriteReg(0x53);
    NT35310_LCD_WriteData(0x2C);
    NT35310_LCD_WriteReg(0x55);
    NT35310_LCD_WriteData(0x82);
    NT35310_LCD_WriteReg(0x2c);
    
    LCD_BL=1; //����LCD������
}


/*
��������: д����
*/
void NT35310_LCD_WriteData(u16 data)
{
    NT35310_LCD_DAT=data; //ֱ��д����
}

/*
��������: д����
*/
void NT35310_LCD_WriteReg(u16 Reg)
{
   NT35310_LCD_REG=Reg; //ֱ��д����
}

/*
��������: ������
*/
u16 NT35310_LCD_ReadData(void)
{
    u16 data;
    data=NT35310_LCD_DAT; //��������
    return data;
}


/*
��������:  ���ù���λ��
*/
void NT35310_LCD_SetCursor(u16 x,u16 y)
{
    NT35310_LCD_WriteReg(0x2A); //����X����
    NT35310_LCD_WriteData(x>>8);  //д��X�ĸ�λ
    NT35310_LCD_WriteData(x&0xFF); //д��X�ĵ�λ
  
    NT35310_LCD_WriteReg(0x2B);    //����Y����
    NT35310_LCD_WriteData(y>>8);   //д��Y�ĸ�λ
    NT35310_LCD_WriteData(y&0xFF); //д��Y�ĵ�λ
}

/*
��������:  ���㺯��
*/
void NT35310_LCD_DrawPoint(u16 x,u16 y,u16 c)
{
    NT35310_LCD_SetCursor(x,y); //���ù���λ��
    
    NT35310_LCD_WriteReg(0x2C); //��ʾдGRAM  ������ɫ����
    NT35310_LCD_WriteData(c);   //д����ɫ
}

/*
��������:  ���㺯��
*/
u16 NT35310_LCD_ReadPoint(u16 x,u16 y)
{
    u16 data1,data2;
    u16 c=0;  //������յ���ɫֵ
    u8 r,g,b;
    NT35310_LCD_SetCursor(x,y); //���ù���λ��
    NT35310_LCD_WriteReg(0x2E); //��ʾ��GRAM  ������ɫ����
    
    NT35310_LCD_ReadData();     //��ȡ��һ�ε���Ч����
    data1=NT35310_LCD_ReadData(); //��ȡR1 G1
    data2=NT35310_LCD_ReadData(); //��ȡB1 R2
    
    r=data1>>8&0xFF; //R����
    g=data1&0xFF;    //G����
    b=data2>>8&0xFF; //B����
    
    //�����ɫ
    c=((r>>3)<<11)|((g>>2)<<5)|(b>>3);
    //RGB565
    return c;
}

/*
��������:  ��������
*/
void NT35310_LCD_Clear(u16 c)
{
   u32 i;
   NT35310_LCD_SetCursor(0,0); //���ù���λ�� 
   NT35310_LCD_WriteReg(0x2C); //��ʾдGRAM  ������ɫ����  
  
   for(i=0;i<320*480;i++)
   {
      NT35310_LCD_WriteData(c); 
   }
}



/*
��������: ��ָ��λ����ʾ����
��������: x�е���ʼλ��(0~127)
				  yҳ����ʼλ��(0~7)
					size��ʾ������
					font��ʾҪ��ʾ�ĺ���
˵��: ��Ҫ��֤�������ߴ��������8�ı�����
*/
void NT35310_LCD_ShowChineseFont(u32 x,u32 y,u32 size,u8 *font)
{
		u32 i,j,x0=x;
		u8 tmp;
    u8 L,H;
    u32 Addr;
    u32 font_size=size*size/8; //�õ����ֽڵ����ֽڴ�С
    u8 FontData[128];         //�����Դ��32*32�ߴ����������
  
    /*1. ����ú������ֿ���ĵ�ַƫ����*/
    L=*(font+1); //���ֽ�
    H=*font;     //���ֽ�
  
    if(L<0x7f)L=L-0x40;
    else L=L-0x41;
    H=H-0x81;
    Addr=(190*H+L)*font_size; //�õ���ǰ�������ֿ����ƫ����
    
    /*2. ��ȡ�ú��ֵĵ�����*/
    switch(size)
    {
      case 16:
//        W25Q64_ReadData(4096+Addr,font_size,FontData);
        break;
      case 24:
        break;
    };
 
    /*3. ��LCD������ʾ����*/
		for(i=0;i<font_size;i++)
		{
				tmp=FontData[i];
				for(j=0;j<8;j++)
				{
						if(tmp&0x80)NT35310_LCD_DrawPoint(x,y,0); //������ɫ
						else NT35310_LCD_DrawPoint(x,y,WHITE);    //������ɫ
						x++;
						tmp<<=1; //�����ж���һλ
				}
				if(x-x0==size)
				{
						y++;  //����������
						x=x0; //�������λ
				}
		}
}



/*
��������: ��LCD����ʾһ���ַ�
��������:
        size�� ��ʾASCII���ַ��߶�
*/
void NT35310_LCD_ShowChar(u32 x,u32 y,u32 size,u8 c)
{
    u32 i,j;
	  u8 tmp;
	  u32 y0=y;
    u8 ASCII_Font[64]; //��Ŷ�ȡ������
    u32 font_size=(size/8)*(size/2);
    u32 Addr=(c-' ')*font_size; //�õ�ASCII��ģƫ����
  
   /*1. ��W25Q64��ȡ��ASCII����ģ*/
    switch(size)
    {
    case 16:
//         W25Q64_ReadData(4096+383040+383040+Addr,font_size,ASCII_Font);
          break;
    case 24:
        //tmp=ASCII_12_24[c-' '][i];
        break;
    }
    
    /*2. ��ʾASCII���ַ�*/    
    for(i=0;i<font_size;i++)
    {
        tmp=ASCII_Font[i];
        for(j=0;j<8;j++)
        {
            if(tmp&0x80)NT35310_LCD_DrawPoint(x,y,0); //������ɫ
						else NT35310_LCD_DrawPoint(x,y,WHITE);    //������ɫ
            y++;
            tmp<<=1; //�����ж���һλ
        }
        if(y-y0==size)
        {
            x++;  //����������
            y=y0; //�������λ
        }
    }
}



/*
��������:  ��ָ��λ����ʾһ���ַ���
*/
void NT35310_LCD_ShowString(u32 x,u32 y,u32 size,u8 *font)
{
    while(*font!='\0')
    {
       if(*font>0x80)  //��ǰ�ַ�����������
       {
           if(x>=319) //�ж�һ���Ƿ񳬳�
           {
               y+=size;
               x=0;
           }
           NT35310_LCD_ShowChineseFont(x,y,size,font);
           font+=2;
           x+=size;
       }
       else //��ǰ�ַ���ASCII��
       {
          if((x+size/2)>319)  //�ж�һ���Ƿ񳬳�
          {
               y+=size;
               x=0;
          }
          NT35310_LCD_ShowChar(x,y,size,*font); //��ʾһ��ASCII�ַ�
          font+=1; 
          x+=size/2;
       }
    }
}



//����Ļ�Ͼ�����ʾ�ַ���
void NT35310_LCD_Show_Mid(u32 x,u32 y,u32 size,u8 *font)
{
	u16 strlenth=0;
	strlenth=strlen((const char*)font);
	strlenth*=size/2;
	if(strlenth>320)
	{
		NT35310_LCD_ShowString(x,y,size,font);
	}
	else
	{
		strlenth=(320-strlenth)/2;
	  NT35310_LCD_ShowString(strlenth+x,y,size,font);
	}
}


//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				NT35310_LCD_ShowChar(x+(size/2)*t,y,16,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	NT35310_LCD_ShowChar(x+(size/2)*t,y,16,temp+'0'); 
	}
} 





/*
��������: ��ָ��λ����ʾһ��ͼƬ
*/
void NT35310_LCD_ShowImage(u16 x,u16 y,u16 w,u16 h,u8 *p)
{
    u32 i,j;
    u16 color;
    for(i=0;i<h;i++)
    {
        NT35310_LCD_SetCursor(x,y+i); //���ù���λ��
        NT35310_LCD_WriteReg(0x2C); //��ʾдGRAM  ������ɫ����
        //дһ�е�����
        for(j=0;j<w;j++)
        {
            color=*p<<8|*(p+1); //���16λ����ɫ
            NT35310_LCD_WriteData(color); //д����ɫ
            p+=2;
        }
    }
}

/*
�������ܣ���ֱ��
��    ����x1,y1:�������
					x2,y2:�յ����� 
*/
void LcdDrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		NT35310_LCD_DrawPoint(uRow,uCol,color);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

/*
�������ܣ�������	
��    ����(x1,y1),(x2,y2):���εĶԽ�����
*/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	LcdDrawLine(x1,y1,x2,y1,color);
	LcdDrawLine(x1,y1,x1,y2,color);
	LcdDrawLine(x1,y2,x2,y2,color);
	LcdDrawLine(x2,y1,x2,y2,color);
}


/*
�������ܣ�������ɫ���
��    ����(sx,sy),(ex,ey):���ζԽ�����
					color:Ҫ������ɫ
*/
void LcdFill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0;
	xlen=ex-sx+1;	 
	for(i=sy;i<=ey;i++)
	{
		NT35310_LCD_SetCursor(sx,i);      				//���ù��λ�� 
		NT35310_LCD_WriteReg(0x2C);     			//��ʼд��GRAM	  
		for(j=0;j<xlen;j++)NT35310_LCD_WriteData(color);	    
	}	 
}


/*
�������ܣ���ָ��λ�û�һ��ָ����С��Բ
��    ����
		(x,y):���ĵ�
		r    :�뾶
*/
void NT35310_DrawCircle(u16 x0,u16 y0,u8 r,u16 c)
{ 
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		NT35310_LCD_DrawPoint(x0+a,y0-b,c);             //5
 		NT35310_LCD_DrawPoint(x0+b,y0-a,c);             //0           
		NT35310_LCD_DrawPoint(x0+b,y0+a,c);             //4               
		NT35310_LCD_DrawPoint(x0+a,y0+b,c);             //6 
		NT35310_LCD_DrawPoint(x0-a,y0+b,c);             //1       
 		NT35310_LCD_DrawPoint(x0-b,y0+a,c);             
		NT35310_LCD_DrawPoint(x0-a,y0-b,c);             //2             
		NT35310_LCD_DrawPoint(x0-b,y0-a,c);             //7     	         
		a++;  
		if(di<0)di +=4*a+6;	//Bresenham��Բ�㷨   
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
}

