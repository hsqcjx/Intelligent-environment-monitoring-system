#ifndef NT35310_LCD_H
#define NT35310_LCD_H
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
//#include "w25q64.h"
#include "usart.h"
#include "font.h"
#include "string.h"

//16λ����ɫֵ
#define WHITE         	 0xFFFF //��ɫ
#define BLACK         	 0x0000	//��ɫ  
#define BLUE         	   0x001F //��ɫ 
#define RED           	 0xF800 //��ɫ
#define YELLOW        	 0xFFE0 //��ɫ
#define BROWN 			     0XBC40 //��ɫ
#define BRRED 			     0XFC07 //�غ�ɫ
#define GRAY  			     0X8430 //��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			     0XC618 //ǳ��ɫ,һ���������屳��ɫ
#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

//LCD�Ļ�����ɫ�ͱ���ɫ	   
extern u16  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern u16  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

//LCD�ı���
#define  LCD_BL PBout(0)

//��������
void NT35310_LCD_Init(void);
void NT35310_LCD_WriteData(u16 data);
void NT35310_LCD_WriteReg(u16 Reg);
void NT35310_LCD_Clear(u16 c);
void NT35310_LCD_DrawPoint(u16 x,u16 y,u16 c);
void NT35310_LCD_ShowChineseFont(u32 x,u32 y,u32 size,u8 *font);
void NT35310_LCD_ShowString(u32 x,u32 y,u32 size,u8 *font);
void NT35310_LCD_Show_Mid(u32 x,u32 y,u32 size,u8 *font);
void NT35310_LCD_ShowImage(u16 x,u16 y,u16 w,u16 h,u8 *p);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
void LcdDrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
void LcdFill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);
void NT35310_DrawCircle(u16 x0,u16 y0,u8 r,u16 c);
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);
u16 NT35310_LCD_ReadData(void);
u16 NT35310_LCD_ReadPoint(u16 x,u16 y);   
u32 LCD_Pow(u8 m,u8 n);

#endif
