#include <xc.h>
#include "adc.h"
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"
#include "main.h"
#include "matrix_keypad.h"
#include "external_eeprom.h"

unsigned int log_count = 0;

void store_eeprom(unsigned char event, unsigned char gear, unsigned int speed, unsigned char time[])
{
    static unsigned char eeprom_address = 0x00;
    if(log_count == 0)
    {
        eeprom_address = 0x00;
    }
    unsigned char speed_str[4];
    unsigned char address = eeprom_address;
    unsigned char i;
    speed_str[0] = (speed / 100) + '0';
    speed_str[1] = ((speed / 10) % 10) + '0';
    speed_str[2] = (speed % 10) + '0';
    speed_str[3] = '\0';
    for(i = 0; i < 8; i++)
    {
        write_external_eeprom(address++, time[i]);
    }
    
    write_external_eeprom(address++, event);
    write_external_eeprom(address++, gear);

    write_external_eeprom(address++, speed_str[0]);
    write_external_eeprom(address++, speed_str[1]);
    write_external_eeprom(address++, speed_str[2]);

//    write_external_eeprom(address++, 0x00);
//    write_external_eeprom(address++, 0x00);

    eeprom_address += 16;
    if(log_count < 10)
    {
        log_count++;
    }
}

