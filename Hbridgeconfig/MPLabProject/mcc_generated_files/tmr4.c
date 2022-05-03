/**
  TMR4 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr4.c

  @Summary
    This is the generated driver implementation file for the TMR4 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for TMR4.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.80.0
        Device            :  PIC16LF1708
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.30
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr4.h"
#include "dac.h"

/**
  Section: Global Variables Definitions
*/

void (*TMR4_InterruptHandler)(void);

/**
  Section: TMR4 APIs
*/

void TMR4_Initialize(void)
{
    // Set TMR4 to the options selected in the User Interface

    // PR4 4; 
    PR4 = 0x04;

    // TMR4 0; 
    TMR4 = 0x00;

    // Clearing IF flag before enabling the interrupt.
    PIR2bits.TMR4IF = 0;

    // Enabling TMR4 interrupt.
    PIE2bits.TMR4IE = 1;

    // Set Default Interrupt Handler
    TMR4_SetInterruptHandler(TMR4_DefaultInterruptHandler);

    // T4CKPS 1:16; T4OUTPS 1:3; TMR4ON on; 
    T4CON = 0x16;
}

void TMR4_StartTimer(void)
{
    // Start the Timer by writing to TMRxON bit
    T4CONbits.TMR4ON = 1;
}

void TMR4_StopTimer(void)
{
    // Stop the Timer by writing to TMRxON bit
    T4CONbits.TMR4ON = 0;
}

uint8_t TMR4_ReadTimer(void)
{
    uint8_t readVal;

    readVal = TMR4;

    return readVal;
}

void TMR4_WriteTimer(uint8_t timerVal)
{
    // Write to the Timer4 register
    TMR4 = timerVal;
}

void TMR4_LoadPeriodRegister(uint8_t periodVal)
{
   PR4 = periodVal;
}

void TMR4_ISR(void)
{

    // clear the TMR4 interrupt flag
    PIR2bits.TMR4IF = 0;

    if(TMR4_InterruptHandler)
    {
        TMR4_InterruptHandler();
    }
}


void TMR4_SetInterruptHandler(void (* InterruptHandler)(void)){
    TMR4_InterruptHandler = InterruptHandler; //
}

// state variable for toggling current square wave
uint8_t currentIsOn = 1;

// this is the DAC value for when the current is on; defined in main.c
extern uint16_t dac_value;

extern uint8_t dc_frequency_flag;
uint8_t oneHzCounter;
uint8_t latch;

void TMR4_DefaultInterruptHandler(void){
    currentIsOn = 0;
  // add your TMR4 interrupt custom code
  // or set custom function using TMR4_SetInterruptHandler()

    if (dc_frequency_flag) { // if frequency is set to 0
        DAC_SetOutput(255); // current will always be set to 0 no matter what
    }else{
  // toggle current output state to create square wave
  if (currentIsOn){ // if current is firing (which it never will hmm)
   // currentIsOn = 0; // turn it off and set current to 0
    DAC_SetOutput(255);
    // can streamline this
    // don't be in a rush
    
  } else {
       if (PR4 == 255) { //only will get here when set to 1 hz
            if (oneHzCounter == 81) { // don't know if this is correct oop (probably is but double check)
                DAC_SetOutput(dac_value);
                oneHzCounter = 0;
            }
            oneHzCounter++;
        } else {
    //currentIsOn = 1;
    
    DAC_SetOutput(dac_value);
    if (latch) {
        LATCbits.LATC7 = 0;
        LATCbits.LATC1 = 1;
        latch = 0;
    } else {
        LATCbits.LATC1 = 1;
        LATCbits.LATC7 = 0;
        latch = 1;
    }
  }
  
  
  
  TMR1 = 65518;
  //PIE1bits.TMR1IE = 1;
  //T1CONbits.TMR1ON = 1;
  //LATBbits.LATB6 = 1;
  //LATCbits.LATC0 = 1;
  //LATCbits.LATC1 = 1;
  //LATCbits.LATC7 = 1;
    }
 // TMR0 = 0x38;
//  INTCONbits.TMR0IE = 1;
    }
}
 // TMR0 = 0x38;
//  INTCONbits.TMR0IE = 1;


/*  End of File
*/
// ohmigod I am so depressed. why am i so so depressed. goddamit. also i want bridget really
// badly. kind of accidentally making her my hope for a normal life. although I don't think
// that I deserve her to be frank. she really is the real deal. I need to name some flaws about her.
// so that I don't get too too attached. 
// 1. she does get stressed out/frustrated relatively easily, although she handles it well
// 2. she (and me) tend to make snap judgements about people. willing to cahnge them though.
// 3. she seems to take a very methodical approach to relationships.
// 4. the fact that she doesn't seem to think that she led me on is a red flag.
// 5. she took samika and jesse coming on to her kinda scary seriously
// 6. her athleticism and religion, while both hot, could be an issue if I don't make a change.
// this is going to be bad, none of those are really flaws they are just personality traits that are
// only not great because of me not her oop.