#ifndef NT35310_LCD_H
#define NT35310_LCD_H
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
//#include "w25q64.h"
#include "usart.h"
#include "font.h"
#include "string.h"

//16位的颜色值
#define WHITE         	 0xFFFF //白色
#define BLACK         	 0x0000	//黑色  
#define BLUE         	   0x001F //蓝色 
#define RED           	 0xF800 //红色
#define YELLOW        	 0xFFE0 //黄色
#define BROWN 			     0XBC40 //棕色
#define BRRED 			     0XFC07 //棕红色
#define GRAY  			     0X8430 //灰色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			     0XC618 //浅灰色,一般用作窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

//LCD的画笔颜色和背景色	   
extern u16  POINT_COLOR;//默认红色    
extern u16  BACK_COLOR; //背景颜色.默认为白色

//LCD的背光
#define  LCD_BL PBout(0)

//函数声明
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
