#include "lcd_init.h"
//#include "delay.h"


unsigned char tag = 1;

void LCD_GPIO_Init(void)
{
	gpio_export(55);
	gpio_export(54);
	gpio_export(34);
	gpio_export(4);
	gpio_output_init(55);
	gpio_output_init(54);
	gpio_output_init(34);
	gpio_output_init(4);
	hspi0 = spi_init(SPI0,SPI_MODE_3,8);
	LCD_CS_Clr();
}

/******************************************************************************
      ����˵����LCD��������д�뺯��
      ������ݣ�dat  Ҫд��Ĵ�������
      ����ֵ��  ��
******************************************************************************/
void LCD_Writ_Bus(unsigned short dat) 
{	
	//unsigned char i;
	//LCD_CS_Clr();
	spi_transfer(hspi0,(unsigned char *)&dat,NULL,1);
  //while(tag);
//	for(i=0;i<8;i++)
//	{			  
//		LCD_SCLK_Clr();
//		if(dat&0x80)
//		{
//		   LCD_MOSI_Set();
//		}
//		else
//		{
//		   LCD_MOSI_Clr();
//		}
//		LCD_SCLK_Set();
//		dat<<=1;
//	}	
  //LCD_CS_Set();
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA8(unsigned char dat)
{
	LCD_Writ_Bus((unsigned short)dat);
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA(unsigned short dat)
{
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_REG(unsigned char dat)
{
	LCD_DC_Clr();//д����
	LCD_Writ_Bus(dat);
	LCD_DC_Set();//д����
}


/******************************************************************************
      ����˵����������ʼ�ͽ�����ַ
      ������ݣ�x1,x2 �����е���ʼ�ͽ�����ַ
                y1,y2 �����е���ʼ�ͽ�����ַ
      ����ֵ��  ��
******************************************************************************/
void LCD_Address_Set(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2)
{
	if(USE_HORIZONTAL==0)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==1)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1+80);
		LCD_WR_DATA(y2+80);
		LCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==2)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
	else
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1+80);
		LCD_WR_DATA(x2+80);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
}

void LCD_Init(void)
{
	LCD_GPIO_Init();
	//LCD_CS_Clr();
	LCD_RES_Clr();
	//delay_ms(100);
  	usleep(1000);
	LCD_RES_Set();
	//delay_ms(100);
	usleep(1000);
	LCD_BLK_Set();
  //delay_ms(100);
	usleep(1000);
	//************* Start Initial Sequence **********//
	LCD_WR_REG(0x11); //Sleep out 
	//delay_ms(120);              //Delay 120ms 
  	usleep(1000);
	//************* Start Initial Sequence **********// 
	LCD_WR_REG(0x36);
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
	else LCD_WR_DATA8(0xA0);

	LCD_WR_REG(0x3A);     
	LCD_WR_DATA8(0x05);   

	LCD_WR_REG(0xB2);     
	LCD_WR_DATA8(0x1F);   
	LCD_WR_DATA8(0x1F);   
	LCD_WR_DATA8(0x00);   
	LCD_WR_DATA8(0x33);   
	LCD_WR_DATA8(0x33);   

	LCD_WR_REG(0xB7);     
	LCD_WR_DATA8(0x35);   

	LCD_WR_REG(0xBB);     
	LCD_WR_DATA8(0x20);   //2b

	LCD_WR_REG(0xC0);     
	LCD_WR_DATA8(0x2C);   

	LCD_WR_REG(0xC2);     
	LCD_WR_DATA8(0x01);   

	LCD_WR_REG(0xC3);     
	LCD_WR_DATA8(0x01);   

	LCD_WR_REG(0xC4);     
	LCD_WR_DATA8(0x18);   //VDV, 0x20:0v

	LCD_WR_REG(0xC6);     
	LCD_WR_DATA8(0x13);   //0x13:60Hz   

	LCD_WR_REG(0xD0);     
	LCD_WR_DATA8(0xA4);   
	LCD_WR_DATA8(0xA1);   

	LCD_WR_REG(0xD6);     
	LCD_WR_DATA8(0xA1);   //sleep in��gate���ΪGND

	LCD_WR_REG(0xE0);     
	LCD_WR_DATA8(0xF0);   
	LCD_WR_DATA8(0x04);   
	LCD_WR_DATA8(0x07);   
	LCD_WR_DATA8(0x04);   
	LCD_WR_DATA8(0x04);   
	LCD_WR_DATA8(0x04);   
	LCD_WR_DATA8(0x25);   
	LCD_WR_DATA8(0x33);   
	LCD_WR_DATA8(0x3C);   
	LCD_WR_DATA8(0x36);   
	LCD_WR_DATA8(0x14);   
	LCD_WR_DATA8(0x12);   
	LCD_WR_DATA8(0x29);   
	LCD_WR_DATA8(0x30);   

	LCD_WR_REG(0xE1);     
	LCD_WR_DATA8(0xF0);   
	LCD_WR_DATA8(0x02);   
	LCD_WR_DATA8(0x04);   
	LCD_WR_DATA8(0x05);   
	LCD_WR_DATA8(0x05);   
	LCD_WR_DATA8(0x21);   
	LCD_WR_DATA8(0x25);   
	LCD_WR_DATA8(0x32);   
	LCD_WR_DATA8(0x3B);   
	LCD_WR_DATA8(0x38);   
	LCD_WR_DATA8(0x12);   
	LCD_WR_DATA8(0x14);   
	LCD_WR_DATA8(0x27);   
	LCD_WR_DATA8(0x31);   

	LCD_WR_REG(0xE4);     
	LCD_WR_DATA8(0x1D);   //ʹ��240��gate  (N+1)*8
	LCD_WR_DATA8(0x00);   //�趨gate���λ��
	LCD_WR_DATA8(0x00);   //��gateû������ʱ��bit4(TMG)��Ϊ0

	LCD_WR_REG(0x21);     

	LCD_WR_REG(0x29); 
} 







