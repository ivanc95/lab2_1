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
#define ROW_4 LATDbits.LATD1

#define COL_1 PORTGbits.RG0
#define COL_2 PORTGbits.RG13
#define COL_3 PORTFbits.RF1


// ******************************************************************************************* //

typedef enum RS_enum {
    run, stop, reset
}status;

volatile int q = 0;

volatile status state = stop;
volatile status next = run;

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
    
    
    
    initKeypad();

    writeCMD(CLR);
    
    printCharLCD('I');
    
    
            
    while(1)
    {       
    }
    
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt( void ){
    IFS1bits.CNGIF = 0;    //Reset change notification flag
    IFS1bits.CNFIF = 0;
    CNCONGbits.ON = 0;
    CNCONFbits.ON = 0;
    delayMs(25);
    CNCONGbits.ON = 1;
    CNCONFbits.ON = 1;
    
    char key = scanKeypad();
    
    if(q == 0){
        
        if(key != -1){
            printCharLCD(key);
        }
        
        q = 1;
    }
    else{
        q = 0;
    }
   
}
