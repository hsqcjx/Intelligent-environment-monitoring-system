#include "nt35310_lcd.h"


//LCD的画笔颜色和背景色	   
u16 POINT_COLOR=0x0000;	//画笔颜色
u16 BACK_COLOR=0xFFFF;  //背景色 


	
 
#define NT35310_LCD_REG *(u16*)(0x60000000)
#define NT35310_LCD_DAT *(u16*)(0x60200000) //0110 0000 0010 0000 0000 0000 0000 0000

/*
NT35310_LCD_REG=0x12345; //LCD会认为发送的是命令
NT35310_LCD_DAT=0x12345; //LCD会认为发送的是数据

FSMC地址线:  FSMC_A0~FSMC_A15  0x0000
FSMC数据线:  FSMC_D0~FSMC_D15  上就会呈现出0x12345这个数据。
*/


void NT35310_LCD_Init(void)
{
    /*1. 开时钟*/
    RCC->AHBENR|=1<<8;  //开启FSMC时钟
    RCC->APB2ENR|=1<<3; //PB
    RCC->APB2ENR|=1<<5; //PD
    RCC->APB2ENR|=1<<6; //PE
  

	  /*2. 初始化LCD控制线*/
    GPIOB->CRL&=0xFFFFFFF0;		//背光LED
    GPIOB->CRL|=0x00000003;  
    
		GPIOD->CRL&=0x0F00FFFF;
    GPIOD->CRL|=0xB0BB0000;
		
		GPIOE->CRL&=0xFFF0FFFF;
    GPIOE->CRL|=0x000B0000;		
		
		/*. 初始化数据线*/
		GPIOD->CRL&=0xFFFFFF00;
    GPIOD->CRL|=0x000000BB;		
		
		GPIOD->CRH&=0x00FFF000;
    GPIOD->CRH|=0xBB000BBB;

		GPIOE->CRL&=0x0FFFFFFF;
    GPIOE->CRL|=0xB0000000;
		
		GPIOE->CRH&=0x00000000;
    GPIOE->CRH|=0xBBBBBBBB;



    /*4. 配置FSMC核心寄存器*/
    FSMC_Bank1->BTCR[0]=0; //BCR
    FSMC_Bank1->BTCR[1]=0; //BTR

    FSMC_Bank1->BTCR[0]|=1<<12; //写使能
    FSMC_Bank1->BTCR[0]|=1<<4;  //16位宽度
    
    FSMC_Bank1->BTCR[1]|=0x1<<8; //配置数据保持的时间
                                 //16个HCLK时钟周期
    FSMC_Bank1->BTCR[0]|=1<<0;   //开启FSMC块1
    
    DelayMs(120); //等待LCD屏复位成功
    
    /*4. 初始化LCD的驱动芯片*/
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
    
    LCD_BL=1; //开启LCD屏背光
}


/*
函数功能: 写数据
*/
void NT35310_LCD_WriteData(u16 data)
{
    NT35310_LCD_DAT=data; //直接写数据
}

/*
函数功能: 写命令
*/
void NT35310_LCD_WriteReg(u16 Reg)
{
   NT35310_LCD_REG=Reg; //直接写命令
}

/*
函数功能: 读数据
*/
u16 NT35310_LCD_ReadData(void)
{
    u16 data;
    data=NT35310_LCD_DAT; //接收数据
    return data;
}


/*
函数功能:  设置光标的位置
*/
void NT35310_LCD_SetCursor(u16 x,u16 y)
{
    NT35310_LCD_WriteReg(0x2A); //设置X坐标
    NT35310_LCD_WriteData(x>>8);  //写入X的高位
    NT35310_LCD_WriteData(x&0xFF); //写入X的低位
  
    NT35310_LCD_WriteReg(0x2B);    //设置Y坐标
    NT35310_LCD_WriteData(y>>8);   //写入Y的高位
    NT35310_LCD_WriteData(y&0xFF); //写入Y的低位
}

/*
函数功能:  画点函数
*/
void NT35310_LCD_DrawPoint(u16 x,u16 y,u16 c)
{
    NT35310_LCD_SetCursor(x,y); //设置光标的位置
    
    NT35310_LCD_WriteReg(0x2C); //表示写GRAM  就是颜色数据
    NT35310_LCD_WriteData(c);   //写入颜色
}

/*
函数功能:  读点函数
*/
u16 NT35310_LCD_ReadPoint(u16 x,u16 y)
{
    u16 data1,data2;
    u16 c=0;  //存放最终的颜色值
    u8 r,g,b;
    NT35310_LCD_SetCursor(x,y); //设置光标的位置
    NT35310_LCD_WriteReg(0x2E); //表示读GRAM  就是颜色数据
    
    NT35310_LCD_ReadData();     //读取第一次的无效数据
    data1=NT35310_LCD_ReadData(); //读取R1 G1
    data2=NT35310_LCD_ReadData(); //读取B1 R2
    
    r=data1>>8&0xFF; //R分量
    g=data1&0xFF;    //G分量
    b=data2>>8&0xFF; //B分量
    
    //组合颜色
    c=((r>>3)<<11)|((g>>2)<<5)|(b>>3);
    //RGB565
    return c;
}

/*
函数功能:  清屏函数
*/
void NT35310_LCD_Clear(u16 c)
{
   u32 i;
   NT35310_LCD_SetCursor(0,0); //设置光标的位置 
   NT35310_LCD_WriteReg(0x2C); //表示写GRAM  就是颜色数据  
  
   for(i=0;i<320*480;i++)
   {
      NT35310_LCD_WriteData(c); 
   }
}



/*
函数功能: 在指定位置显示中文
函数参数: x列的起始位置(0~127)
				  y页的起始位置(0~7)
					size表示字体宽度
					font表示要显示的汉字
说明: 需要保证字体横向尺寸和纵向是8的倍数。
*/
void NT35310_LCD_ShowChineseFont(u32 x,u32 y,u32 size,u8 *font)
{
		u32 i,j,x0=x;
		u8 tmp;
    u8 L,H;
    u32 Addr;
    u32 font_size=size*size/8; //得到该字节的总字节大小
    u8 FontData[128];         //最大可以存放32*32尺寸字体点阵码
  
    /*1. 计算该汉字在字库里的地址偏移量*/
    L=*(font+1); //低字节
    H=*font;     //高字节
  
    if(L<0x7f)L=L-0x40;
    else L=L-0x41;
    H=H-0x81;
    Addr=(190*H+L)*font_size; //得到当前汉字在字库里的偏移量
    
    /*2. 读取该汉字的点阵码*/
    switch(size)
    {
      case 16:
//        W25Q64_ReadData(4096+Addr,font_size,FontData);
        break;
      case 24:
        break;
    };
 
    /*3. 在LCD屏上显示汉字*/
		for(i=0;i<font_size;i++)
		{
				tmp=FontData[i];
				for(j=0;j<8;j++)
				{
						if(tmp&0x80)NT35310_LCD_DrawPoint(x,y,0); //字体颜色
						else NT35310_LCD_DrawPoint(x,y,WHITE);    //背景颜色
						x++;
						tmp<<=1; //继续判断下一位
				}
				if(x-x0==size)
				{
						y++;  //纵坐标自增
						x=x0; //横坐标归位
				}
		}
}



/*
函数功能: 在LCD上显示一个字符
函数参数:
        size： 表示ASCII码字符高度
*/
void NT35310_LCD_ShowChar(u32 x,u32 y,u32 size,u8 c)
{
    u32 i,j;
	  u8 tmp;
	  u32 y0=y;
    u8 ASCII_Font[64]; //存放读取的数据
    u32 font_size=(size/8)*(size/2);
    u32 Addr=(c-' ')*font_size; //得到ASCII字模偏移量
  
   /*1. 从W25Q64里取出ASCII码字模*/
    switch(size)
    {
    case 16:
//         W25Q64_ReadData(4096+383040+383040+Addr,font_size,ASCII_Font);
          break;
    case 24:
        //tmp=ASCII_12_24[c-' '][i];
        break;
    }
    
    /*2. 显示ASCII码字符*/    
    for(i=0;i<font_size;i++)
    {
        tmp=ASCII_Font[i];
        for(j=0;j<8;j++)
        {
            if(tmp&0x80)NT35310_LCD_DrawPoint(x,y,0); //字体颜色
						else NT35310_LCD_DrawPoint(x,y,WHITE);    //背景颜色
            y++;
            tmp<<=1; //继续判断下一位
        }
        if(y-y0==size)
        {
            x++;  //横坐标自增
            y=y0; //纵坐标归位
        }
    }
}



/*
函数功能:  在指定位置显示一个字符串
*/
void NT35310_LCD_ShowString(u32 x,u32 y,u32 size,u8 *font)
{
    while(*font!='\0')
    {
       if(*font>0x80)  //当前字符串就是中文
       {
           if(x>=319) //判断一行是否超出
           {
               y+=size;
               x=0;
           }
           NT35310_LCD_ShowChineseFont(x,y,size,font);
           font+=2;
           x+=size;
       }
       else //当前字符是ASCII码
       {
          if((x+size/2)>319)  //判断一行是否超出
          {
               y+=size;
               x=0;
          }
          NT35310_LCD_ShowChar(x,y,size,*font); //显示一个ASCII字符
          font+=1; 
          x+=size/2;
       }
    }
}



//在屏幕上居中显示字符串
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


//m^n函数
//返回值:m^n次方.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//显示数字,高位为0,则不显示
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//color:颜色 
//num:数值(0~4294967295);	 
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
函数功能: 在指定位置显示一张图片
*/
void NT35310_LCD_ShowImage(u16 x,u16 y,u16 w,u16 h,u8 *p)
{
    u32 i,j;
    u16 color;
    for(i=0;i<h;i++)
    {
        NT35310_LCD_SetCursor(x,y+i); //设置光标的位置
        NT35310_LCD_WriteReg(0x2C); //表示写GRAM  就是颜色数据
        //写一行的数据
        for(j=0;j<w;j++)
        {
            color=*p<<8|*(p+1); //组合16位的颜色
            NT35310_LCD_WriteData(color); //写入颜色
            p+=2;
        }
    }
}

/*
函数功能：画直线
参    数：x1,y1:起点坐标
					x2,y2:终点坐标 
*/
void LcdDrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		NT35310_LCD_DrawPoint(uRow,uCol,color);//画点 
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
函数功能：画矩形	
参    数：(x1,y1),(x2,y2):矩形的对角坐标
*/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	LcdDrawLine(x1,y1,x2,y1,color);
	LcdDrawLine(x1,y1,x1,y2,color);
	LcdDrawLine(x1,y2,x2,y2,color);
	LcdDrawLine(x2,y1,x2,y2,color);
}


/*
函数功能：矩形颜色填充
参    数：(sx,sy),(ex,ey):矩形对角坐标
					color:要填充的颜色
*/
void LcdFill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0;
	xlen=ex-sx+1;	 
	for(i=sy;i<=ey;i++)
	{
		NT35310_LCD_SetCursor(sx,i);      				//设置光标位置 
		NT35310_LCD_WriteReg(0x2C);     			//开始写入GRAM	  
		for(j=0;j<xlen;j++)NT35310_LCD_WriteData(color);	    
	}	 
}


/*
函数功能：在指定位置画一个指定大小的圆
参    数：
		(x,y):中心点
		r    :半径
*/
void NT35310_DrawCircle(u16 x0,u16 y0,u8 r,u16 c)
{ 
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
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
		if(di<0)di +=4*a+6;	//Bresenham画圆算法   
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
}

