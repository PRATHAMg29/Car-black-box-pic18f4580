/*
 * File:   main.c
 * Author: prath
 *
 * Created on 4 July, 2026, 9:07 AM
 */
#include<xc.h>
#include "adc.h"
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"
#include "main.h"
#include "matrix_keypad.h"
#include "time.h"
#include "external_eeprom.h"

unsigned char clock_reg[3];
unsigned char calender_reg[4];
unsigned char time[9];
unsigned char date[11];
unsigned char ampm;

void init_config(void)
{
	init_clcd();
	init_i2c();
	init_ds1307();
    init_adc();
    init_uart();
//	clcd_print("  DS1307  TEST  ", LINE1(0));
}

void main(void) 
{
    
//    CLEAR_DISP_SCREEN;
    init_config();
    clcd_print("Hello",LINE1(0));
    init_matrix_keypad();
    unsigned char gear[] = {'N','1','2','3','4','5','R'};
    unsigned char speed_str[4];
    unsigned int speed = 0;
    unsigned char gear_change = 0,collision = 0;
    unsigned int i=0;
    while(1)
    {
        unsigned char key = read_switches(STATE_CHANGE);
        if(key == MK_SW1 && i<6)
        {
            i++;
            gear_change = 1;
//            store_eeprom(gear[i],speed,time);
        }
        else if(key == MK_SW2 && i>0)
        {
            i--;
            gear_change = 1;
//            store_eeprom(gear[i],speed,time);
        }
        else if(key == MK_SW3)
        {
//            store_eeprom(gear[i],speed,time);
            collision = 1;
        }
        else if(key == MK_SW11)
        {
            menu();
        }
        
        
        if(gear[i] == 'N')
        {
            speed=0;
        }
        else if(gear[i] == 'R')
        {
            speed = 10;
        }
        else
        {
            unsigned short adc_value = read_adc(CHANNEL4);
            speed = adc_value / 10.23;
        }
        clcd_putch('G',LINE1(4));
        clcd_putch(gear[i],LINE2(4));
        clcd_putch(' ',LINE1(3));
        clcd_putch(' ',LINE2(3));
        clcd_putch(' ',LINE1(5));
        clcd_putch(' ',LINE2(5));
        clcd_putch(' ',LINE1(6));
        clcd_putch(' ',LINE1(7));
        clcd_putch(' ',LINE1(8));
        clcd_print("SPD",LINE1(0));
        speed_str[0] = (speed / 100) + '0';
        speed_str[1] = ((speed / 10) % 10) + '0';
        speed_str[2] = (speed % 10) + '0';
        speed_str[3] = '\0';
        clcd_print(speed_str,LINE2(0));
        clcd_print("TIME   ",LINE1(9));
        get_time();
		display_time();
        if(gear_change == 1)
        {
            gear_change = 0;
            store_eeprom('G',gear[i],speed,time);
        }
        if(collision == 1)
        {
            collision = 0;
            store_eeprom('C',gear[i],speed,time);
        }
    }
}


void display_time(void)
{
	clcd_print(time, LINE2(6));

	if (clock_reg[0] & 0x40)
	{
		if (clock_reg[0] & 0x20)
		{
			clcd_print("PM", LINE2(14));
            ampm = 'p';
		}
		else
		{
			clcd_print("AM", LINE2(14));
            ampm = 'a';
		}
	}
}

static void get_time(void)
{
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

	if (clock_reg[0] & 0x40)
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
}