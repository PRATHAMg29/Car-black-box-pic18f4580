#include <xc.h>
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"
#include "main.h"
#include "matrix_keypad.h"
#include "external_eeprom.h"
#include "uart.h"

void download_log(void)
{
    CLEAR_DISP_SCREEN;
    unsigned int i=0;
    unsigned int view_index = 0;
    unsigned char address;
    unsigned char time[11],speed[4],gear,event;
    unsigned char flag = 0;
    while(1)
    {
        if(log_count == 0)
        {
            if(flag == 0)
            {
                str_transmit_uart("No log  to display.\n\r");
                flag = 1;
            }
            clcd_print("   No log to    ",LINE1(0));
            clcd_print("   Download      ",LINE2(0));
            unsigned char key = read_switches(STATE_CHANGE);
            if(key == MK_SW12)
            {
                return;
            }
        }
        else
        {
            break;
        }
    }
    
    str_transmit_uart("\r\n");
    str_transmit_uart("=========================================\r\n");
    str_transmit_uart("          CAR BLACK BOX\r\n");
    str_transmit_uart("=========================================\r\n");
    str_transmit_uart("No  Event      Time       Gear  Speed\r\n");
    str_transmit_uart("-----------------------------------------\r\n");
    
    for(view_index = 0;view_index < log_count;view_index++)
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

//        str_transmit_uart("Log : ");
        unsigned char index = view_index + '1';
        char_transmit_uart(index);
        str_transmit_uart("   ");
//            clcd_putch(' ',LINE1(5));
        if(event == 'G')
        {
            str_transmit_uart("GEAR       ");
        }
        else if(event == 'C')
        {
            str_transmit_uart("COLLISION  ");
        }
//            clcd_putch(' ',LINE2(10));
//            clcd_putch(' ',LINE2(12));
        str_transmit_uart(time);
        str_transmit_uart("    ");
        
        char_transmit_uart(gear);
        str_transmit_uart("     ");
        
        str_transmit_uart(speed);
        str_transmit_uart("\r\n");

        
    }
    str_transmit_uart("-----------------------------------------\r\n");
    str_transmit_uart("End of Log\r\n");
    CLEAR_DISP_SCREEN;
    clcd_print(" DOWNLOAD DONE  ", LINE1(0));
    clcd_print("  SW12->EXIT    ", LINE2(0));

    while(1)
    {
        unsigned char key = read_switches(STATE_CHANGE);
        if(key == MK_SW12)
        {
            return;
        }
    }
}
