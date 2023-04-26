#include<reg51.h>
#include "delay.h"
#include "i2c.h"
 
sbit SCL=P1^1;      //SCL Connected to P0.0
sbit SDA=P1^0;      //SDA Connected to P0.1
 
 
void i2c_Clock(void)
{
    delay_us(50);
    SCL = 1;        
 
    delay_us(50);        
    SCL = 0;        
}
 
// khi start I2C phai hoan thanh het 1 chu ky
void i2c_Start()
{
		SDA=1;
		SCL=1;
		delay_us(50);
		SDA=0;
		delay_us(50);
		SCL=0;
}

 
void i2c_Stop(void)
{	
		SDA=0;                 // Stop processing //
		SCL=1;                 //clock is 1//
		delay_us(50);
		SDA=1;                 //Stopped//
		delay_us(50);
		SCL=0;                 //clock signal is 0//
}
// gui tung bit 1 
void i2c_Write(unsigned char dat)
{
    unsigned char i;
    for(i=0;i<8;i++)         
     {
        SDA = dat & 0x80;    
        i2c_Clock();         
        dat = dat<<1;
      }
        SDA = 1;                 
}

unsigned char i2c_Read(void)
{
    unsigned char i, dat=0x00;
 
    SDA=1;   // gui bit R/W len 1 => mode Read            
    for(i=0;i<8;i++)       
    {
       delay_us(50);
       SCL = 1;           
       delay_us(50);
 
       dat = dat<<1;       
       dat = dat | SDA;    
 
       SCL = 0;            
    }
   return dat;             
}

void i2c_Ack()
{
    SDA = 0;        
    i2c_Clock();    
    SDA = 1;        
}

void i2c_NoAck()
{
    SDA = 1;        
   i2c_Clock();     
    SCL = 1;     
}
