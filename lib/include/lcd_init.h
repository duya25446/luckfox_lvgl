#ifndef __LCD_INIT_H
#define __LCD_INIT_H
#include "main.h"
#include "lib_gpio.h"
#include "lib_spi.h"

#define USE_HORIZONTAL 3  


#define LCD_W 240
#define LCD_H 240



//-----------------LCD�˿ڶ���---------------- 

// #define LCD_SCLK_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET)//SCL=SCLK
// #define LCD_SCLK_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET)

// #define LCD_MOSI_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET)//SDA=MOSI
// #define LCD_MOSI_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET)

#define LCD_RES_Clr()  gpio_output_write(55,0)//RES 55
#define LCD_RES_Set()  gpio_output_write(55,1)

#define LCD_DC_Clr()   gpio_output_write(54,0) //DC 54
#define LCD_DC_Set()   gpio_output_write(54,1)

#define LCD_CS_Clr()   gpio_output_write(34,0) //CS 34
#define LCD_CS_Set()   gpio_output_write(34,1)

#define LCD_BLK_Clr()  gpio_output_write(4,0) //BLK 4
#define LCD_BLK_Set()  gpio_output_write(4,1)


void LCD_GPIO_Init(void);
void LCD_Writ_Bus(unsigned short dat) ;
void LCD_WR_DATA8(unsigned char dat);
void LCD_WR_DATA(unsigned short dat);
void LCD_WR_REG(unsigned char dat);
void LCD_Address_Set(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2);
void LCD_Init(void);

int hspi0;


#endif




