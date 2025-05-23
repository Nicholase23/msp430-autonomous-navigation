/*
 * interrupt_ports.c
 *
 *  Created on: Oct 6, 2023
 *      Author: Nicholas Edwards
 *
 *  This file controls the interrupts that are triggered by the press of the switches
 */

#include  "msp430.h"
#include  <string.h>
#include  "include\functions.h"
#include  "Include\LCD.h"
#include  "include\ports.h"
#include  "macros.h"

extern void HEXtoBCD(int), adc_line(char, char), USCI_A0_transmit(void), WiFi_Setup(void);

volatile char allowedToStart = 0;

unsigned short int press_counter = 0;

#pragma vector=PORT4_VECTOR
// Create an Interrupt Service Routine Function with "__interrupt"
__interrupt void switchP4_interrupt(void) {
    // Check if Switch 1 caused the interrupt

    if (P4IFG & SW1) {
        // Clear the interrupt flag for SW1
        P4IFG &= ~SW1;
        LCD_BACKLITE_DIMING = PERCENT_100; // P6.0 Right Forward PWM duty cycle
    }

    // Use a Timer Value to control the de-bounce.
}

#pragma vector=PORT2_VECTOR
// Create an Interrupt Service Routine Function with "__interrupt"
__interrupt void switchP2_interrupt(void) {
    // Check if Switch 2 caused the interrupt
    if (P2IFG & SW2) {
        // Clear the interrupt flag for SW2
        P2IFG &= ~SW2;
        LCD_BACKLITE_DIMING = PERCENT_100; // P6.0 Right Forward PWM duty cycle

        press_counter++;
        WiFi_Setup();
    }

    // Use a Timer Value to control the debounce
}
