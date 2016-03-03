// ******************************************************************************************* //
//
// File:         lab1p2.c
// Date:         12-30-2014
// Authors:      Garrett Vanhoy
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt.h"
#include "switch.h"
#include "keypad.h"

#define CLR 0x01

#define RUN_LED LATDbits.LATD2
#define STP_LED LATDbits.LATD0
#define RUN TRISDbits.TRISD2
#define STP TRISDbits.TRISD0

#define SWT_T TRISDbits.TRISD5
#define SWT PORTDbits.RD5

#define RST_T TRISDbits.TRISD6
#define RST PORTDbits.RD6

#define ROW_1 LATDbits.LATD12
#define ROW_2 LATDbits.LATD6
#define ROW_3 LATDbits.LATD3
#define ROW_4 LATDbits.LATD9

#define COL_1 PORTGbits.RG0
#define COL_2 PORTGbits.RG13
#define COL_3 PORTFbits.RF1

volatile int wait = 0;


// ******************************************************************************************* //

typedef enum RS_enum {
    write, newLine
}status;

volatile int q = 0;
volatile int d = 0;
volatile int line = 0;
volatile int v = 0;
volatile char k = '1';

volatile status state = write;
volatile status next = newLine;

int main(void)
{
    enableInterrupts();
    
    
    
    SYSTEMConfigPerformance(10000000);
    STP = 0;
    RUN = 0;

    LATDbits.LATD0 = 1;
    initTimer2();
    initLCD();
    initSW();
    delayMs(1000);
    LATDbits.LATD0 = 0;
    
     TRISDbits.TRISD0 = 0;
    
    initKeypad();

    writeCMD(CLR);
    
    //printCharLCD('I');
    
    ROW_1 = 0; ROW_2 = 0; ROW_3 = 0; ROW_4 = 0;
            
    while(1)
    {       
        
       
//        switch(state){
//            case write:
//                next = newLine;
//                
//                break;
//                
//            case newLine:
//                next = write;
//                break;
//            default:
//                state = write;
//        }
    }
    
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt( void ){
    IFS1bits.CNGIF = 0;    //Reset change notification flag
    IFS1bits.CNFIF = 0;
    LATDbits.LATD0 = 1;
    CNCONGbits.ON = 0;
    CNCONFbits.ON = 0;
    delayMs(25);
    CNCONGbits.ON = 1;
    CNCONFbits.ON = 1;
    LATDbits.LATD0 = 0;
    
    if(COL_1 == 0 | COL_2 == 0 | COL_3 == 0){
        
        
        if(line == 16){
            moveCursorLCD(0,2);
        }
        if(line == 32){
            moveCursorLCD(0,1);
            line = 0;
            k = '2';
        }
        printCharLCD(k);
        line++;
        
    }
    
    
    
   
}
