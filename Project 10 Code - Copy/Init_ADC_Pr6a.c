/*
 * Init_ADC_Pr6a.c
 *
 * File to initialize the ADC to collect values from the IR detectors.
 *
 *  Created on: Oct 13, 2023
 *      Author: Nicholas Edwards
 */

#include  <string.h>
#include  "msp430.h"
#include  "include/functions.h"
#include "include/LCD.h"
#include  "include/ports.h"
#include "macros.h"

void Init_ADC(void), HEXtoBCD(int), adc_line(char, char);

unsigned int ADC_Channel;

unsigned int ADC_Left_Detect, ADC_Right_Detect, ADC_ThumbWheel;

void Init_ADC(void) {
    // Reset and configure ADCCTL0 Register
    ADCCTL0 = 0;                // Reset
    ADCCTL0 |= ADCSHT_2;        // Sample-and-hold time: 16 ADC clocks
    ADCCTL0 |= ADCMSC;          // Multiple sample and conversion
    ADCCTL0 |= ADCON;           // Turn on the ADC

    // Configure ADCCTL1 Register
    ADCCTL1 = 0;                // Reset
    ADCCTL1 |= ADCSHS_0;        // Sample-and-hold source: ADCSC bit
    ADCCTL1 |= ADCSHP;          // Sample-and-hold pulse-mode
    ADCCTL1 &= ~ADCISSH;        // Invert signal sample-and-hold
    ADCCTL1 |= ADCDIV_0;        // ADC clock divider: Divide by 1
    ADCCTL1 |= ADCSSEL_0;       // ADC clock source: MODCLK
    ADCCTL1 |= ADCCONSEQ_0;     // Conversion sequence: Single-channel single-conversion

    // Configure ADCCTL2 Register
    ADCCTL2 = 0;                // Reset
    ADCCTL2 |= ADCPDIV0;        // ADC pre-divider: Pre-divide by 1
    ADCCTL2 |= ADCRES_2;        // ADC resolution: 12-bit (14 clock cycle conversion time)
    ADCCTL2 &= ~ADCDF;          // ADC data read-back format: Binary unsigned
    ADCCTL2 &= ~ADCSR;          // ADC sampling rate: Up to 200 ksps

    // Configure ADCMCTL0 Register
    ADCMCTL0 |= ADCSREF_0;      // Voltage reference: VR+ = AVCC and VR– = AVSS
    ADCMCTL0 |= ADCINCH_5;      // Input channel select: V_THUMB (0x20), Pin 5 A5

    ADCIE |= ADCIE0;            // Enable ADC conversion complete interrupt
    ADCCTL0 |= ADCENC;          // Enable ADC conversion
    ADCCTL0 |= ADCSC;           // Start ADC conversion
}

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void) {
    switch (__even_in_range(ADCIV, ADCIV_ADCIFG)) {
        case ADCIV_NONE:
            // No ADC interrupt occurred.
            break;
        case ADCIV_ADCOVIFG:
            // ADC memory overflow interrupt - when a conversion result is written to ADCMEM0
            // before its previous conversion result was read.
            break;
        case ADCIV_ADCTOVIFG:
            // ADC conversion-time overflow interrupt.
            break;
        case ADCIV_ADCHIIFG:
            // Window comparator high threshold interrupt.
            break;
        case ADCIV_ADCLOIFG:
            // Window comparator low threshold interrupt.
            break;
        case ADCIV_ADCINIFG:
            // Window comparator in-between threshold interrupt.
            break;
        case ADCIV_ADCIFG:
            // ADC conversion complete interrupt - ADCMEM0 memory register with the conversion result.
            // In this case, it's handling the result of Channel A5.
            ADCCTL0 &= ~ADCENC; // Disable ENC bit.
            switch (ADC_Channel++) {
                case 0x00: // Channel A2 Interrupt
                    ADC_Left_Detect = ADCMEM0; // Move result into Global Values
                    // Divide the ADC_Left_Detect result by 4
                    ADC_Left_Detect = ADC_Left_Detect >> 2;

                    // Convert the result to a BCD (Binary Coded Decimal) string

                    ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
                    ADCMCTL0 |= ADCINCH_3;   // Enable Next channel A3
                    break;
                case 0x01: // Channel A3 Interrupt
                    ADC_Right_Detect = ADCMEM0; // Move result into Global Values

                    // Divide the ADC_Left_Detect result by 4
                    ADC_Right_Detect = ADC_Right_Detect >> 2;

                    // Convert the result to a BCD (Binary Coded Decimal) string

                    ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A3

                    // Specify the next channel to enable (e.g., ADCINCH_X)
                    ADCMCTL0 |= ADCINCH_5; // Enable Next channel X
                    break;
                case 0x02: // Specify the channel for the third case
                    // Move the result into the appropriate global variable (e.g., ADC_XXXX)
                    ADC_ThumbWheel = ADCMEM0; // Move result into Global Values
                    ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A5
                    // Specify the next channel to enable (e.g., ADCINCH_X)
                    ADCMCTL0 |= ADCINCH_2; // Enable Next channel 2
                    ADC_Channel = 0;
                    break;
                default:
                    break;
            }
            //ADCCTL0 |= ADCENC; // Enable Conversions


        default:
            // Default case for un-handled interrupts.
            break;
    }
}
