/*
 * interrupt_ports.c
 *
 *  Created on: Oct 6, 2023
 *      Author: Nicholas Edwards
 *
 *  This file controls the interrupts that are triggered by the timer
 */

#include  <string.h>
#include  "msp430.h"
#include  "include/functions.h"
#include "include/LCD.h"
#include  "include/ports.h"
#include "macros.h"

extern volatile unsigned int second;
volatile int count = 0;

void Init_Timer_B0(void), Init_Timer_B3(void), Magic_Smoke(void);
__interrupt void TIMER0_B1_ISR(void);
extern volatile unsigned char update_display;

volatile unsigned int second2 = 0;
extern unsigned short int timerFlag;
extern volatile unsigned int DAC_data;

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void)
{
    //------------------------------------------------------------------------------
    // TimerB0 0 Interrupt handler
    //----------------------------------------------------------------------------
    count++;
    //update_display = 1;
    ADCCTL0 |= ADCENC; // Enable ADC conversion
    ADCCTL0 |= ADCSC;  // Start next sample

    if (count >= 18)
    {
        second++;

        if (timerFlag == 1) {
            second2++;
        }

        count = 0;

        display_changed = TRUE;
        update_display = 1;
    }

    if (second == 3) {
        P3OUT |= IOT_EN;
        second++;
    }

    //ADCCTL0 |= ADCSC;  // Start next sample
    TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
    //TB0CCTL0 &= ~CCIFG;          // Clear Timer B0 CCR0 interrupt flag
    //----------------------------------------------------------------------------
}

#pragma vector = TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void)
{
    //----------------------------------------------------------------------------
    // TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
    //----------------------------------------------------------------------------
    switch (__even_in_range(TB0IV, 14))
    {
    case 0:
        break; // No interrupt
    case 2:    // CCR1 not used
        //
        TB0CCR1 += TB0CCR1_INTERVAL; // Add Offset to TBCCR1
        break;
    case 4: // CCR2 not used
        //
        TB0CCR2 += TB0CCR2_INTERVAL; // Add Offset to TBCCR2
        break;
    case 14:                    // overflow

//        DAC_data = DAC_data - 50;
//
//        SAC3DAT = DAC_data;       // Initial DAC data
//
//        if(DAC_data <= 1200){
//
//            DAC_data = 1200;
//
//            SAC3DAT = DAC_data;     // Initial DAC data
//
//            TB0CTL &= ~TBIE;        // Timer B0 overflow interrupt disable

//        }

        break;
    default:
        break;
    }
    //----------------------------------------------------------------------------
}
