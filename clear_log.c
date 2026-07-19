#include <xc.h>
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"
#include "main.h"
#include "matrix_keypad.h"
#include "external_eeprom.h"

void clear_log(void)
{
    CLEAR_DISP_SCREEN;
    while(1)
    {
        unsigned char key = read_switches(STATE_CHANGE);
        if(key == MK_SW12)
        {
            return;
        }
        clcd_print("  Log cleared   ",LINE1(0));
        clcd_print("  Successfully  ",LINE2(0));
        log_count = 0;
    }
}