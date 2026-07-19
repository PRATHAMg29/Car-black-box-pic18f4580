#include <xc.h>
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"
#include "main.h"
#include "matrix_keypad.h"
#include "external_eeprom.h"
#include "uart.h"

void set_log(void)
{
//    get_time();
    CLEAR_DISP_SCREEN;
    unsigned int blink_count = 0;
    unsigned char blink = 1;
    unsigned char hour,minute,second;
    hour = ((time[0] - '0') * 10) + (time[1] - '0');
    minute = ((time[3] - '0') * 10) + (time[4] - '0');
    second = ((time[6] - '0') * 10) + (time[7] - '0');
    clcd_print("   SET TIME     ",LINE1(0));
    unsigned char update_time[9];
    update_time[0] = (hour / 10) + '0';
    update_time[1] = (hour % 10) + '0';
    update_time[2] = ':';
    update_time[3] = (minute / 10) + '0';
    update_time[4] = (minute % 10) + '0';
    update_time[5] = ':';
    update_time[6] = (second / 10) + '0';
    update_time[7] = (second % 10) + '0';
    update_time[8] = '\0';
    clcd_print(update_time,LINE2(2));
    if(ampm == 'p')
    {
        clcd_print("PM",LINE2(10));
    }
    else if(ampm == 'a')
    {
        clcd_print("AM",LINE2(10));
    }
    unsigned char edit = 0;
    while(1)
    {
//        unsigned char flag = 0;
        if(++blink_count >= 400)
        {
            blink_count = 0;
            blink = !blink;
        }
        unsigned char key = read_switches(STATE_CHANGE);
        if(key == MK_SW1)
        {
            if(edit == 0)
            {
                if(hour < 12)
                {
                    hour++;
                }
//                else if(hour == 11 && ampm == 'p')
//                {
//                    hour++;
//                    ampm = 'a';
//                    flag = 1;
//                }
//                else if(hour == 11 && ampm == 'a')
//                {
//                    hour++;
//                    ampm = 'p';
//                    flag = 1;
//                }
//                
//                if(hour == 12 && flag == 0)
//                {
//                    hour = 1;
//                }
            }
            else if(edit == 1)
            {
                if(minute < 59)
                {
                    minute++;
                }
//                else if(minute == 59)
//                {
//                    minute = 0;
////                    hour++;
//                }
            }
            else if(edit == 2)
            {
                if(second < 59)
                {
                    second++;
                }
//                else if(second == 59)
//                {
//                    second = 0;
//                }
            }
            else if(edit == 3)
            {
                if(ampm == 'a')
                {
                    ampm = 'p';
                }
                else if(ampm == 'p')
                {
                    ampm = 'a';
                }
            }
        }
        else if(key == MK_SW2)
        {
            if(edit == 0)
            {
                if(hour > 1)
                {
                    hour--;
                }
//                else if(hour == 1)
//                {
//                    hour = 12;
//                }
//                else if(hour == 12 && ampm == 'a')
//                {
//                    hour--;
//                    ampm = 'p';
//                }
//                else if(hour == 12 && ampm == 'p')
//                {
//                    hour--;
//                    ampm = 'a';
//                }
//                if(hour == 1)
//                {
//                    hour = 12;
//                }
            }
            else if(edit == 1)
            {
                if(minute>0)
                {
                    minute--;
                }
            }
            else if(edit == 2)
            {
                if(second>0)
                {
                    second--;
                }
            }
            else if(edit == 3)
            {
                if(ampm == 'a')
                {
                    ampm = 'p';
                }
                else if(ampm == 'p')
                {
                    ampm = 'a';
                }
            }
        }
        else if(key == MK_SW11)
        {
            if(edit < 3)
            {
                edit++;
            }
            else
            {
                unsigned char sec_bcd, min_bcd, hour_bcd;
                /* Convert decimal to BCD */
                sec_bcd = ((second / 10) << 4) | (second % 10);
                min_bcd = ((minute / 10) << 4) | (minute % 10);
                hour_bcd = ((hour / 10) << 4) | (hour % 10);
                /* Set 12-hour mode */
                hour_bcd = hour_bcd | 0x40;
                /* Set PM bit if required */
                if(ampm == 'p')
                {
                    hour_bcd = hour_bcd | 0x20;
                }
                else
                {
                    hour_bcd = hour_bcd & ~0x20;
                }

                /* Stop clock */
                unsigned char temp = read_ds1307(SEC_ADDR);
                write_ds1307(SEC_ADDR, temp | 0x80);

                /* Write new time */
                write_ds1307(HOUR_ADDR, hour_bcd);
                write_ds1307(MIN_ADDR, min_bcd);
                write_ds1307(SEC_ADDR, sec_bcd);

                /* Start clock */
                write_ds1307(SEC_ADDR, sec_bcd & 0x7F);
                return;
            }
        }
        else if(key == MK_SW12)
        {
            return;
        }
        update_time[0] = (hour / 10) + '0';
        update_time[1] = (hour % 10) + '0';
        update_time[2] = ':';
        update_time[3] = (minute / 10) + '0';
        update_time[4] = (minute % 10) + '0';
        update_time[5] = ':';
        update_time[6] = (second / 10) + '0';
        update_time[7] = (second % 10) + '0';
        update_time[8] = '\0';
        
        if(edit == 0 && blink == 0)
        {
            update_time[0] = ' ';
            update_time[1] = ' ';
        }
        else if(edit == 1 && blink == 0)
        {
            update_time[3] = ' ';
            update_time[4] = ' ';
        }
        else if(edit == 2 && blink == 0)
        {
            update_time[6] = ' ';
            update_time[7] = ' ';
        }
        
        clcd_print(update_time,LINE2(2));
        if(edit == 3 && blink == 0)
        {
            clcd_print("  ", LINE2(10));
        }
        else
        {
            if(ampm == 'p')
                clcd_print("PM", LINE2(10));
            else if(ampm == 'a')
                clcd_print("AM", LINE2(10));
        }
    }
}