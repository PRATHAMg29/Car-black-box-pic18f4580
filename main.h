#ifndef MAIN_H
#define MAIN_H

#include "adc.h"
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"
#include "main.h"
#include "matrix_keypad.h"
#include "external_eeprom.h"
#include "uart.h"

void init_ds1307(void);
void display_time(void);
static void get_time(void);
static void get_date(void);
void store_eeprom(unsigned char event,unsigned char gear,unsigned int speed,unsigned char time[]);
void menu(void);
void view_log(void);
void clear_log(void);
void download_log(void);
void set_log(void);

extern unsigned char time[9];
extern unsigned int log_count;
extern unsigned char ampm;

#endif