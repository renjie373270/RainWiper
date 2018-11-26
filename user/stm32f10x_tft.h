#ifndef STM32F10X_TFT_H
#define STM32F10X_TFT_H

#include "stm32f10x.h"

#define red              0xf800
#define yellow           0xffe0
#define green			 0x07e0
#define cyan			 0x07ff
#define blue			 0x001f
#define purple			 0xf81f
#define black			 0x0000
#define white			 0xffff
#define gray			 0x7bef

void LCD_Init(void);
void LCD_WR_REG(unsigned int index);
void LCD_WR_CMD(unsigned int index,unsigned int val);
void LCD_WR_Data(unsigned int val);	
unsigned int LCD_RD_data(void);
void delayms(uint32_t x);
uint16_t RGB(u8 R,u8 G,u8 B);
void FSMC_LCD_Init(void);
void LCD_ClearScreen(uint16_t color) ;
void TFT_Init(uint16_t color);
void LCD_Point(uint16_t x,uint16_t y,uint16_t color);
unsigned char find_Font(uint8_t size,const char *p);
void LCD_WriteFont(uint16_t x,uint16_t y,uint16_t size,uint16_t color,const  char *p);
void LCD_WriteFontString(uint16_t x,uint16_t y,uint16_t color,const  char *p);
void LCD_DisplayFont(uint16_t color,const char *p);
unsigned char find_Asc(const char *p);
void LCD_WriteChar(uint16_t x,uint16_t y,uint16_t color,const char *p);
void LCD_WriteCharString(uint16_t x,uint16_t y,uint16_t color,const char *p);
void LCD_DisplayAsc(uint16_t color,const char *p);
void LCD_DisplayString(uint16_t x,uint16_t y,uint16_t color,const char *p);
void test(void);

#endif
