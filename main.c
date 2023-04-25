#include <reg51.h> 
#include "lcd.h"  	 
#include "ds1307.h" 
#include "i2c.h"
#include "delay.h"
#include "Keypad4x4.h"
#include <string.h>
#include <stdio.h>
volatile int Mode = 0; //thay doi len 1 de debug
volatile int loop = 1;
volatile int loop2 = 1;
volatile int SingleTimeInput=0; // change to debug
volatile int Hour = 0;// change to debug
volatile int Min = 0;// change to debug
volatile int Sec = 0;// change to debug
int *OperandPointer = &Hour;
char Convert(int in)
{
	return (in % 10) + ((in / 10) % 10) * 16 + ((in / 100) % 10) * 16 * 16;
}
void ModeWatchTime(unsigned char sec,unsigned char min,unsigned char hour,unsigned char day,unsigned char month,unsigned char year)
{
			lcd_Line_posnX();
			lcd_DisplayString(" Time:");
	    lcd_Line_posnY();
      lcd_DisplayString(" Date:");
	    //delay_ms(1000);
			ds1307_GetTime(&hour,&min,&sec);        
			lcd_curser_posn(0,6); 		 
			lcd_DisplayRtcTime(hour,min,sec);
			ds1307_GetDate(&day,&month,&year);        
			lcd_curser_posn(1,6);
			lcd_DisplayRtcDate(day,month,year);
			delay_ms(1000);
}
void ModeSetTime(unsigned char *button)
{
		
		if(loop2 == 1)
		{
			lcd_Clear();
			loop2--;
		}
		if(loop == 1)
		{
			lcd_Line_posnX();
			lcd_DisplayString(" Set Your Time: ");
			lcd_Line_posnY();
		  loop--;
		}
		*button = get_key();
		if(*button>0)
		{
			SingleTimeInput++;
			//lan nhap thu 1
			if(SingleTimeInput==1)
			{
				show_button(*button);

				if((*button != 4)&&(*button !=8)&&(*button != 12)&&(*button != 16)&&(*button != 15)&&(*button != 13))
				{
					num_generator(*button,OperandPointer);
				}
			}
			//lan nhap thu 2
			if(SingleTimeInput==2)
			{
				show_button(*button);

				if((*button != 4)&&(*button !=8)&&(*button != 12)&&(*button != 16)&&(*button != 15)&&(*button != 13))
				{
					num_generator(*button,OperandPointer);
				}
			}
			//lan nhap thu 3
			if(SingleTimeInput==3)
			{
				show_button(*button);
				if((*button == 12))
				{
					OperandPointer = &Min;
				}
				if((*button != 4)&&(*button !=8)&&(*button != 12)&&(*button != 16)&&(*button != 15)&&(*button != 13))
				{
					num_generator(*button,OperandPointer);

				}
			}
			//lan nhap thu 4
			if(SingleTimeInput==4)
			{
				show_button(*button);

				if((*button != 4)&&(*button !=8)&&(*button != 12)&&(*button != 16)&&(*button != 15)&&(*button != 13))
				{
					num_generator(*button,OperandPointer);
				}
			}
			//lan nhap thu 5
			if(SingleTimeInput==5)
			{
				show_button(*button);
				if((*button != 4)&&(*button !=8)&&(*button != 12)&&(*button != 16)&&(*button != 15)&&(*button != 13))
				{
					num_generator(*button,OperandPointer);
				}
			}
			//lan nhap thu 6
			if(SingleTimeInput==6)
			{
				show_button(*button);
				if((*button == 12))
				{
					OperandPointer = &Sec;
				}
				if((*button != 4)&&(*button !=8)&&(*button != 12)&&(*button != 16)&&(*button != 15)&&(*button != 13))
				{
					num_generator(*button,OperandPointer);
				}
			}
			//lan nhap thu 7
			if(SingleTimeInput==7)
			{
				show_button(*button);
				if((*button != 4)&&(*button !=8)&&(*button != 12)&&(*button != 16)&&(*button != 15)&&(*button != 13))
				{
					num_generator(*button,OperandPointer);
				}
			}
			//lan nhap thu 8
			if(SingleTimeInput==8)
			{
				show_button(*button);

				if((*button != 4)&&(*button !=8)&&(*button != 12)&&(*button != 16)&&(*button != 15)&&(*button != 13))
				{
					num_generator(*button,OperandPointer);
					//TimeInput++;
				}
			}
			if(SingleTimeInput==9)
			{

				if(*button ==13)
				{
					SingleTimeInput=0;
					loop = 1;
					loop2 =1;
					ds1307_SetTime(Convert(Hour),Convert(Min),Convert(Sec)); 
					lcd_Clear();
					Mode = 0;
				}
			}			

		*button = 0;
		delay_ms(200);
		}
		
}

/* main program */
void main() 
{
		
    unsigned char sec,min,hour,day,month,year;

		unsigned char button;
		EA  = 1;		//cho phep ngat toan cuc
		EX0 = 1;    //chon ngat ngoai INT1
		IT0 = 1;    //chon ngat canh xuong
    lcd_Init();
    ds1307_Init();

    while(1)
    {
			if(Mode ==0)
			{
				ModeWatchTime(sec,min,hour,day,month,year);
			}
			if(Mode == 1)
			{
				ModeSetTime(&button);
			}
			if(Mode > 1)
			{
				Mode = 0;
			}
    }
}
void ISR_EX0 (void) interrupt 0
{
	Mode++;
} 
