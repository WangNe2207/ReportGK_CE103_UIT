
#include<reg51.h> 
#include "ds1307.h"
#include "i2c.h"
#include "delay.h"
  
/* Below given values are fixed and should not be changed.
    Refer Ds1307 DataSheet for more info*/
 
#define DS1307_ID 0xD0     // Address cua ds1307 l� 0x68 nhung phai dich phai 1 bit nen thanh 0xD0 vi ham I2C cua thu vien Hal yeu cau vay
#define SEC_ADDRESS   0x00 // address to access ds1307 SEC register
#define MIN_ADDRESS   0x01 // address to access ds1307 SEC register
#define HOUR_ADDRESS   0x02 // address to access ds1307 SEC register
#define DATE_ADDRESS  0x04 // address to access ds1307 DATE register
#define control       0x07 // address to access ds1307 CONTROL register
 
//ds1307 initilization
void ds1307_Init()
{
    i2c_Start();            // Start i2c communication
 
   ds1307_Write(DS1307_ID);   // gui dia chi cua DS1307
   ds1307_Write(control);    // truy cap vao thanh ghi control cua ds1307
 
    //ds1307_Write(0x00);        
 
    i2c_Stop();             // Stop Condition
 
 }
 void ds1307_Write(unsigned char dat)
{
    i2c_Write(dat);   
    i2c_Clock();
}

unsigned char ds1307_Read()
{
    unsigned char dat;
    dat = i2c_Read();   
    return(dat);
}
void ds1307_SetTime(int hh, int mm, int ss)
{
    i2c_Start();            // Start i2c communication
 
    ds1307_Write(DS1307_ID);    
    ds1307_Write(SEC_ADDRESS);
    ds1307_Write(ss);           
    ds1307_Write(mm);           
    ds1307_Write(hh);     
     
    i2c_Stop();             // Stop i2c communication after Setting the Time
}

void ds1307_SetDate(unsigned char dd, unsigned char mm, unsigned char yy)
{
    i2c_Start();            // Start i2c communication
 
    ds1307_Write(DS1307_ID);    
    ds1307_Write(DATE_ADDRESS);     
 
    ds1307_Write(dd);           
    ds1307_Write(mm);           
    ds1307_Write(yy);           
 
    i2c_Stop();             // Stop i2c communication after Setting the Date
}

void ds1307_GetTime(unsigned char *h_ptr,unsigned char *m_ptr,unsigned char *s_ptr)
{
   i2c_Start();           // Start i2c communication
 
   ds1307_Write(DS1307_ID);    
   ds1307_Write(SEC_ADDRESS);          

   i2c_Stop();            
 
   i2c_Start();               
   ds1307_Write(0xD1);         // truyen dia chi (xem phan data read trong datasheet)
                               
	
  *s_ptr = ds1307_Read();  i2c_Ack();     
  *m_ptr = ds1307_Read();  i2c_Ack();     
  *h_ptr = ds1307_Read();  i2c_NoAck();   
 
  i2c_Stop();               // stop i2c communication after reading the Time
 }
 
void ds1307_GetDate(unsigned char *d_ptr,unsigned char *m_ptr,unsigned char *y_ptr)
{
    i2c_Start();            // start i2c communication
 
    ds1307_Write(DS1307_ID);    
    ds1307_Write(DATE_ADDRESS);     
 
    i2c_Stop();             
 
 
   i2c_Start();             
   ds1307_Write(0xD1);          
                            
 
  *d_ptr = ds1307_Read(); i2c_Ack();     
  *m_ptr = ds1307_Read(); i2c_Ack();     
  *y_ptr = ds1307_Read(); i2c_NoAck();   
 
  i2c_Stop();         // stop i2c communication after reading the Time
 }
