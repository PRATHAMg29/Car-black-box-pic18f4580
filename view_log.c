#include <xc.h>
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"
#include "main.h"
#include "matrix_keypad.h"
#include "external_eeprom.h"

void view_log(void)
{
    CLEAR_DISP_SCREEN;
    unsigned int i=0;
    unsigned int view_index = 0;
    unsigned char address;
    unsigned char time[11],speed[4],gear,event;
    while(1)
    {
        if(log_count == 0)
        {
            clcd_print("   No log to    ",LINE1(0));
            clcd_print("   Display      ",LINE2(0));
            unsigned char key = read_switches(STATE_CHANGE);
            if(key == MK_SW12)
            {
                return;
            }
        }
        else
        {
            address = view_index * 16;
            for(i = 0; i < 8; i++)
            {
                time[i] = read_external_eeprom(address++);
            }
            time[i] = '\0';
            event = read_external_eeprom(address++);
            gear = read_external_eeprom(address++);

            speed[0] = read_external_eeprom(address++);
            speed[1] = read_external_eeprom(address++);
            speed[2] = read_external_eeprom(address++);
            speed[3] = '\0';

            clcd_print("Log:",LINE1(0));
            unsigned char index = view_index + 1;
            if(index < 10)
            {
                clcd_putch(index + '0', LINE1(4));
                clcd_putch(' ', LINE1(5));
            }
            else
            {
                clcd_putch('1', LINE1(4));
                clcd_putch('0', LINE1(5));
            }
//            clcd_putch(index,LINE1(4));
//            clcd_putch(' ',LINE1(5));
            if(event == 'G')
            {
                clcd_print("GEARchange",LINE1(6));
            }
            else if(event == 'C')
            {
                clcd_print("Collision ",LINE1(6));
            }
            clcd_putch(' ',LINE2(10));
            clcd_putch(' ',LINE2(12));
            clcd_print(time,LINE2(0));
            if(ampm == 'p')
            {
                clcd_print("PM",LINE2(8));
            }
            else if(ampm == 'a')
            {
                clcd_print("AM",LINE2(8));
            }
            clcd_putch(gear,LINE2(11));
            clcd_print(speed,LINE2(13));

            unsigned char key = read_switches(STATE_CHANGE);
            if(key == MK_SW1 && view_index < log_count-1)
            {
                view_index++;
            }
            else if(key == MK_SW2 && view_index > 0)
            {
                view_index--;
            }
            else if(key == MK_SW12)
            {
                return;
            }
        }
    }
}
