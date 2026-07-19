#include <xc.h>
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"
#include "main.h"
#include "matrix_keypad.h"
#include "external_eeprom.h"

void menu(void)
{
    CLEAR_DISP_SCREEN;
    unsigned int i=0;
    unsigned int menu_index = 0;
//    char menu[][15] = {"View Log","Download Log","Set Time","Clear Log"};
    while(1)
    {
        unsigned char key = read_switches(STATE_CHANGE);
//        clcd_print("=>View Log",LINE1(0));
//        clcd_print("  Download Log",LINE2(0));
        if(key == MK_SW1)
        {
            if(menu_index < 3)
            {
                menu_index++;
            }
//            clcd_print("  View Log",LINE1(0));
//            clcd_print("=>Download Log",LINE2(0));
        }
        else if(key == MK_SW2)
        {
            if(menu_index > 0)
            {
                menu_index--;
            }
        }
        else if(key == MK_SW11)
        {
            if(menu_index == 0)
            {
                view_log();
                CLEAR_DISP_SCREEN;
            }
            else if(menu_index == 1)
            {
                download_log();
                CLEAR_DISP_SCREEN;
            }
            else if(menu_index == 2)
            {
                set_log();
                CLEAR_DISP_SCREEN;
            }
            else if(menu_index == 3)
            {
                clear_log();
                CLEAR_DISP_SCREEN;
            }
        }
        else if(key == MK_SW12)
        {
            return;
        }
        
        if(menu_index == 0)
        {
            clcd_print("=>View Log",LINE1(0));
            clcd_print("  Download Log",LINE2(0));
        }
        else if(menu_index == 1)
        {
            clcd_print("  View Log      ",LINE1(0));
            clcd_print("=>Download Log  ",LINE2(0));
        }
        else if(menu_index == 2)
        {
            clcd_print("  Download Log  ",LINE1(0));
            clcd_print("=>Set Log       ",LINE2(0));
        }
        else if(menu_index == 3)
        {
            clcd_print("  Set Log       ",LINE1(0));
            clcd_print("=>Clear Log     ",LINE2(0));
        }
    }
}
