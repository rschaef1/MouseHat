/**
  TMR0 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr1.c

  @Summary
    This is the generated driver implementation file for the TMR0 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for TMR0.
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
#include "tmr1.h"
#include "C:\Users\r.schaefer\Downloads\pic-ir-rx-master\pic-ir-rx-master\MouseBrains8.X\mcc_generated_files\dac.h"

/**
  Section: Global Variables Definitions
*/

volatile uint16_t timer1ReloadVal;
void (*TMR1_InterruptHandler)(void);
/**
  Section: TMR1 APIs
*/

void TMR1_Initialize(void)
{
    // Set TMR1 to the options selected in the User Interface
	
    // PSA assigned; PS 1:64; TMRSE Increment_hi_lo; mask the nWPUEN and INTEDG bits
    //OPTION_REG = (uint8_t)((OPTION_REG & 0xC0) | (0xD5 & 0x3F)); 
	
    // TMR0 0; 
    TMR1 = 65528;
	
    // Load the TMR value to reload variable
    timer1ReloadVal= 65528;

    // Clear Interrupt flag before enabling the interrupt
    PIR1bits.TMR1IF = 0;

    // disable TMR0 interrupt
    PIE1bits.TMR1IE = 1;
    
    T1CONbits.TMR1ON = 0;

    // Set Default Interrupt Handler
    TMR1_SetInterruptHandler(TMR1_DefaultInterruptHandler);
}

uint8_t TMR1_ReadTimer(void)
{
    uint8_t readVal;

    readVal = TMR0;

    return readVal;
}

void TMR1_WriteTimer(uint8_t timerVal)
{
    // Write to the Timer0 register
    TMR1 = timerVal;
}

void TMR1_Reload(void)
{
    // Write to the Timer0 register
    TMR1 = timer1ReloadVal;
}

void TMR1_ISR(void)
{

    // Clear the TMR0 interrupt flag
    PIR1bits.TMR1IF = 0;

    TMR1 = timer1ReloadVal;

    if(TMR1_InterruptHandler)
    {
        TMR1_InterruptHandler();
    }

    // add your TMR0 interrupt custom code
}


void TMR1_SetInterruptHandler(void (* InterruptHandler)(void)){
    TMR1_InterruptHandler = InterruptHandler;
}

uint8_t toggle = 1;
void TMR1_DefaultInterruptHandler(void){
    // add your TMR1 interrupt custom code
      
    T1CONbits.TMR1ON = 0;// or set custom function using TMR0_SetInterruptHandler()
    DAC_SetOutput(255); // turn off current after register overflows
    LATCbits.LATC7 = 0;
    LATCbits.LATC1 = 0;
    // INTCONbits.TMR0IE = 0; // disable the interrupt
    // if (toggle) {
    // DAC_SetOutput(255);
    // LATBbits.LATB6 = 1;
    // LATCbits.LATC0 = 1;
    // LATCbits.LATC1 = 0;
    // LATCbits.LATC7 = 0;
    // toggle = 0;
    // TMR1 = 64000;
    // T1CONbits.TMR1ON = 1;
   //  }
  /*   } else {
       T1CONbits.TMR1ON = 0;
       LATBbits.LATB6 = 0;
       LATCbits.LATC0 = 0;
       LATCbits.LATC1 = 1;
       LATCbits.LATC7 = 1;
       toggle = 1;
       // TMR1 = 60000;
    }*/
    //INTCONbits.GIE = 0;
   // SLEEP();
     //   WDTCON = 0b00001001;
     //   SLEEP();
      //  WDTCON = 0b00000000;
      //  PR4 = 2;
        //SLEEP();
}

/**
  End of File
*/