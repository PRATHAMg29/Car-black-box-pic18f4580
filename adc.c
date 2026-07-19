/*
 * File:   adc.c
 * Author: prath
 *
 * Created on 4 June, 2026, 4:11 PM
 */


#include <xc.h>
#include "adc.h"

void init_adc()
{
    ADON = 0;   //DISABLE THE ADC FOR configuration.
    
//    PCFG0 = 0;
//    PCFG1 = 0;
//    PCFG2 = 0;
//    PCFG3 = 0;  //selecting all the channels as analog
    
    VCFG0 = 0;  //for Vdd(5V). this is Vref.
    VCFG1 = 0;  //for Vss(GND). 
    
    ADCS0 = 0;  //for clock conversion(FOCS/32).
    ADCS1 = 1;  //frequency = 625KHz. So 1Tad = 1.6us.
    ADCS2 = 0;  
    
    ACQT0 = 0;
    ACQT1 = 1;  //Time = 6.4us -> for 4Tad.
    ACQT2 = 0;  //to select acquisition time as 4Tad.
    
    ADFM = 1;   //for result right justification.
    
    ADON = 1;   //ENABLE THE ADC module.
}

unsigned short read_adc(unsigned char channel)
{
    ADCON0 = (ADCON0 & 0xC3) | (channel << 2);
    GO = 1;
    while(GO);
    return (ADRESH << 8) | ADRESL;
}