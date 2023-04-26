#include<reg51.h>
#include "lcd.h"
#include "delay.h"
#define dataport P0       
sbit rs= dataport^0;    
sbit rw= dataport^1;      
sbit en= dataport^2;      

#define LCDMaxLines 2
#define LCDMaxChars 16
#define LineOne 0x80
#define LineTwo 0xc0 
#define BlankSpace ' '
//Khoi dong LCD
void LCD_Init()
{
	// xem them trong tap lenh LCD1602
    delay_us(5000);
   lcd_WriteCmd(0x20);  // chon che do 4 bit
   lcd_WriteCmd(0x28);  // chon su dung 2 dong
   lcd_WriteCmd(0x0C);  // display ON cursor OFF blink OFF
   lcd_WriteCmd(0x01);  // clear the LCD
   //lcd_WriteCmd(0x80);  // move the Cursor to First line First Position
 
}
// lcd Write command function
//cac buoc gui command
//Buoc 1: Keo RW RS xuong 0
//Buoc 2: Keo en len 1 de chot du lieu
//Buoc 3: Keo en xuong 0 
void lcd_WriteCmd( char a)
{
   dataport=(a & 0xf0);        //Gui 4 bit cao truoc
   rs=0;                      
   rw=0;                 
 	 en=1;                 
   delay_us(1);
   en=0;
   delay_us(1);                  
   dataport=((a<<4) & 0xf0);   // gui 4 bit thap sau
   rs=0;                    
   rw=0;                    
   en=1;                      
   delay_us(1);
   en=0;
   delay_us(1);
}
 // lcd writedata function
//cac buoc de gui data
// tuong tu nhu gui command nhung RS kich len 1 thay vi 0 o command
void lcd_Writedata( char a)
{
   dataport=(a & 0xf0);        
     rs=1;                      
     rw=0;                      
     en=1;                      
    delay_us(1);
     en=0;
   delay_us(1);                
   dataport=((a <<4) & 0xf0);  
     rs=1;                    
     rw=0;                     
     en=1;                      
    delay_us(1);
     en=0;
   delay_us(1);
}

 
 //lcd gotolinetwo fuction
void lcd_Line_posnY()
{
   lcd_WriteCmd(LineTwo);   // move the Cursor to Second line First Position
}
void lcd_Line_posnX()
{
   lcd_WriteCmd(LineOne);   // move the Cursor to First line First Position
}
 
 
 
//lcd go to X(first row), Y(second row) line
void lcd_curser_posn(char row, char col)
{
   char pos;
 
    if(row<LCDMaxLines)
      {
         pos= LineOne | (row << 6);
                                    
 
        if(col<LCDMaxChars)
           pos= pos+col;            
                                    
 
         lcd_WriteCmd(pos);        
       }
}
 

//lcd display string function
void lcd_DisplayString(char *string_ptr)
{
   while(*string_ptr)
    lcd_Writedata(*string_ptr++);
}

 
//lcd display rtc time function
void lcd_DisplayRtcTime(char hour,char min,char sec)
{
    lcd_Writedata(((hour>>4) & 0x0f) + 0x30);
    lcd_Writedata((hour & 0x0f) + 0x30);
    lcd_Writedata(':');
 
    lcd_Writedata(((min>>4) & 0x0f) + 0x30);
    lcd_Writedata((min & 0x0f) + 0x30);
    lcd_Writedata(':');
 
    lcd_Writedata(((sec>>4) & 0x0f) + 0x30);
    lcd_Writedata((sec & 0x0f) + 0x30);
 
 }
 
 
 // lcd display rtc date function
void lcd_DisplayRtcDate(char day,char month,char year)
 {
     lcd_Writedata(((day>>4) & 0x0f) + 0x30);
     lcd_Writedata((day & 0x0f) + 0x30);
     lcd_Writedata('/');
 
     lcd_Writedata(((month>>4) & 0x0f) + 0x30);
     lcd_Writedata((month & 0x0f) + 0x30);
     lcd_Writedata('/');
 
     lcd_Writedata(((year>>4) & 0x0f) + 0x30);
     lcd_Writedata((year & 0x0f) + 0x30);
 
 }
 
 

 void lcd_Clear()
{
    lcd_WriteCmd(0x01);
}
 