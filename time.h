#ifndef TIME_H
#define TIME_H

#include<xc.h>
#include "adc.h"
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"
#include "main.h"
#include "matrix_keypad.h"

void display_time(void);
static void get_time(void);

#endif
