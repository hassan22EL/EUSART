
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef  _EUSART_H
#define _EUSART_H
#ifndef __XC8
#warning Header file pic16f877a.h included directly. Use #include <xc.h> instead.
#endif 
#define  sbits  sbits 
extern volatile unsigned char sbits @ 0x003;

typedef union {

    struct {
        unsigned sync : 1;
        unsigned clock : 1;
    };
} Sbits_t;
extern volatile Sbits_t Sbits @ 0x003;
void EUSART_Buad_Rate(char Buad_Rate);
void EUSART_INIT();
void EUSART_Write(unsigned char data);
char EUSART_TX_Empty();
void EUSART_Write_Text(char *text);
char EUSART_Data_Ready();
char EUSART_Read();
void EUSART_Read_Text(char *Output, unsigned int length);
#endif	/*_EUSART_H */
