#include <xc.h>
#include "keypad.h"
#include "timer.h"
#include "lcd.h"

/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */

#define ROW_1 LATDbits.LATD12
#define ROW_2 LATDbits.LATD6
#define ROW_3 LATDbits.LATD3
#define ROW_4 LATDbits.LATD9

#define COL_1 PORTGbits.RG0
#define COL_2 PORTGbits.RG13
#define COL_3 PORTFbits.RF1

/* Pins used for the key pad
 *                      J11
 * COL_1      RG13      Pin 4
 * COL_2      RG0       Pin 6
 * COL_3      RF1       Pin 8
 * ROW_1      RD12      Pin 10
 * ROW_2      RD6       Pin 12
 * ROW_3      RD3       Pin 18
 * ROW_4      RD1       Pin 20
 */
void initKeypad(void){
    
    //Initialize Column Tristates
    TRISGbits.TRISG13 = 1;
    TRISGbits.TRISG0 = 1;
    TRISFbits.TRISF1 = 1;
    
    //Turn on CN for port E
    CNCONGbits.ON = 1;
    CNCONFbits.ON = 1;
    
    
    //Enable CN Interrupt for each pin
    CNENGbits.CNIEG13 = 1;
    CNENGbits.CNIEG0 = 1;
    CNENFbits.CNIEF1 = 1;
    
    
    IFS1bits.CNGIF = 0;
    IEC1bits.CNGIE = 1;
    
    IFS1bits.CNFIF = 0;
    IEC1bits.CNFIE = 1;
    
    IPC8bits.CNIP = 7;
    
    //Initialize Row Tristates
    TRISDbits.TRISD12 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD3 = 0;
    TRISDbits.TRISD9 = 0;
    
    //Initialize ODC for row pins
    ODCDbits.ODCD12 = 1;
    ODCDbits.ODCD6 = 1;
    ODCDbits.ODCD3 = 1;
    ODCDbits.ODCD9 = 1;
    
    //ROW_1 = 0; ROW_2 = 1; ROW_3 = 1; ROW_4 = 1;
}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed. The ascii character c programmatically is just 'c'
 */
char scanKeypad(void){
    
    char key = -1;
    
    int pressed = 0;
    
    //Scan Row 1
    ROW_1 = 0; ROW_2 = 1; ROW_3 = 1; ROW_4 = 1;
    
    if(COL_1 == 0){
        key = '1';
        pressed++;
    }
    if(COL_2 == 0){
        key = '2';
        pressed++;
    }
    if(COL_3 == 0){
        key = '3';
        pressed++;
    }
    if(pressed > 1){
        return 'e';
    }
    else if( pressed == 1) {
        return key;
    }
    
    //Scan Row 2
    ROW_1 = 1; ROW_2 = 0; ROW_3 = 1; ROW_4 = 1;
    
    if(COL_1 == 0){
        key = '4';
        pressed++;
    }
    if(COL_2 == 0){
        key = '5';
        pressed++;
    }
    if(COL_3 == 0){
        key = '6';
        pressed++;
    }
    if(pressed > 1){
        return 'e';
    }
    else if( pressed == 1) {
        return key;
    }
    
    //Scan Row 3
    ROW_1 = 1; ROW_2 = 1; ROW_3 = 0; ROW_4 = 1;
    
    if(COL_1 == 0){
        key = '7';
        pressed++;
    }
    if(COL_2 == 0){
        key = '8';
        pressed++;
    }
    if(COL_3 == 0){
        key = '9';
        pressed++;
    }
    if(pressed > 1){
        return 'e';
    }
    else if( pressed == 1) {
        return key;
    }
    
    //Scan Row 4
    ROW_1 = 1; ROW_2 = 1; ROW_3 = 1; ROW_4 = 0;
    
    if(COL_1 == 0){
        key = '*';
        pressed++;
    }
    if(COL_2 == 0){
        key = '0';
        pressed++;
    }
    if(COL_3 == 0){
        writeCMD(0x01);
    }
    if(pressed > 1){
        return 'e';
    }
    
    return key;
    
}