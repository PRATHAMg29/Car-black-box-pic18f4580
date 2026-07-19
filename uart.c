#include <xc.h>
#include "uart.h"
#include "clcd.h"
#include "main.h"

void init_uart(void)
{
    //TxSTA
    TXEN = 1;   //enable transmit.
    TX9 = 0;    //disable parity.
    SYNC = 0;   //enable asynchronous mode.
    BRGH = 1;   //high baud rate.
    
    //RCTSA
    SPEN = 1;   //enabling serial port
    RX9 = 0;    //disable parity
    CREN = 1;   //enable receiver
    
    //BAUDCON
    BRG16 = 0;  //8-bit BAUD rate register.
    WUE = 0;    //no wakeup
    ABDEN = 0;  //disable auto baud detect.
    
    TRISC6 = 0;
    TRISC7 = 1;
    
    SPBRG = 129;    //to achieve 9600 baud rate
}

void char_transmit_uart(unsigned char ch)
{
    while(!TXIF);
    TXREG = ch;
}

void str_transmit_uart(unsigned char *str)
{
    while(*str != '\0')
    {
        char_transmit_uart(*str);
        str++;
    }
}

unsigned char uart_receive(void)
{
    while(!RCIF);
    
    return RCREG;
}