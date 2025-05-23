/*
 * USCI_A0_transmit.c
 *
 * Created on: Nov 2, 2023
 * Author: Nicholas Edwards
 */

#include "msp430.h"
#include <string.h>
#include "include\functions.h"
#include "Include\LCD.h"
#include "include\ports.h"
#include "macros.h"

void USCI_A0_transmit(void);

extern char process_buffer[25]; // Size for appropriate Command Length
extern char pb_index; // Index for process_buffer

// Transmit Function for USCI_A0
void USCI_A0_transmit(void) {
    // Contents must be in process_buffer
    // End of Transmission is identified by NULL character in process_buffer
    // process_buffer includes Carriage Return and Line Feed

    pb_index = 0; // Set Array index to the first location

    UCA0IE |= UCTXIE; // Enable TX interrupt
}
