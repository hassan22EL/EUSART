/*
 * File:   EUSRAT.c
 * Author: Hassan
 *
 * Created on March 2, 2018, 8:19 PM
 */


#include <xc.h>

#include "EUSART.h"
#define _XTAL_FREQ 8000000 

void EUSART_Buad_Rate(char Buad_Rate) {
    int x;
    x = (_XTAL_FREQ - Buad_Rate * 64) / (64 * Buad_Rate);
    if (x > 255)//use high speed 
    {
        x = (_XTAL_FREQ - Buad_Rate * 16) / (16 * Buad_Rate);
        TXSTAbits.BRGH = 1;
    }
    if (x < 255) {
        if (TXSTAbits.SYNC == 0) //(Asynchronous) Baud Rate = FOSC/(64 (X + 1))
        {
            x = (_XTAL_FREQ - Buad_Rate * 64) / (64 * Buad_Rate);
            TXSTAbits.BRGH = 0;
            SPBRG = x;
        } else if (TXSTAbits.SYNC = 1) //(Synchronous) Baud Rate = FOSC/(4 (X + 1))
        {
            x = (_XTAL_FREQ - Buad_Rate * 4) / (4 * Buad_Rate);
            TXSTAbits.BRGH = 0;
            SPBRG = x;
        }
    }
}

void EUSART_INIT() {
    TXSTAbits.TXEN = 1; // Enable transmitter
    RCSTAbits.SPEN = 1; // Enable serial port
    switch (Sbits.sync) {
        case 0: //(Asynchronous)
            TXSTAbits.SYNC = 0;
            break;
        case 1: //(synchronous)
            TXSTAbits.SYNC = 1;
            switch (Sbits.clock) {
                case 0:
                    TXSTAbits.CSRC = 0; //Slave mode (clock from external source)
                    break;
                case 1:
                    TXSTAbits.CSRC = 1; //Master mode (clock generated internally from BRG)
                    break;
            }
            break;
    }
    RCSTAbits.CREN = 1; //1 = Enables continuous receive at (Asynchronous) and
    //1 = Enables continuous receive until enable bit CREN is cleared (CREN overrides SREN) at synchronous
    TRISCbits.TRISC7 = 1; // pin RX   Receiver
    TRISCbits.TRISC6 = 0; //  pin TX  Sender
}

void EUSART_Write(unsigned char data) {
    while (!TXSTAbits.TRMT);
    TXREG = data;
}
char EUSART_TX_Empty()
{
  return TXSTAbits.TRMT;
}
void EUSART_Write_Text(char *text)
{
  int i;
  for(i=0;text[i]!='\0';i++)
    EUSART_Write(text[i]);
}
char EUSART_Data_Ready()
{
  return PIR1bits.RCIF;
}
char EUSART_Read()
{
  while(!PIR1bits.RCIF);
  return RCREG;
}
void EUSART_Read_Text(char *Output, unsigned int length)
{
  for(int i=0;i<length;i++)
  Output[i] = EUSART_Read();
}