/*
 * eUSCI_A0_ISR.c
 *
 * File for the A0 and A1 Interrupt service routine
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

// Global variables
volatile unsigned int charCount;
extern volatile unsigned int usb_rx_ring_wr;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
char process_buffer[25]; // Size for appropriate Command Length
char pb_index; // Index for process_buffer

volatile char IOT_Ring_Rx[SMALL_RING_SIZE], iot_TX_buf[30], USB_Ring_Rx[SMALL_RING_SIZE];
volatile unsigned int iot_rx_wr, iot_tx, usb_rx_wr;


// Globals
// Serial
volatile unsigned int iot_rx_wr = 0;
unsigned int iot_rx_rd; // Only used in Main
unsigned int direct_iot = 0; // Only used it Interrupt

volatile unsigned int usb_rx_wr;
unsigned int usb_rx_rd; // Only used in Main
unsigned int direct_usb; // Only used it Interrupt

char iot_receive;

#pragma vector = EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){ //This interrupt is the interrupt relating to serial communication port UCA0
    //------------------------------------------------------------------------------
    // Interrupt name: eUSCI_A0_ISR
    // Description: This interrupt transmits and receives through UCA0
    //------------------------------------------------------------------------------
    char iot_receive;
    // int temp_char;
    // int i;
    switch(__even_in_range(UCA0IV,0x08)){
    case 0: break; //Vector 0 - no interrupt
    case 2:{ // Vector 2 – Rx0IFG
        iot_receive = UCA0RXBUF;
        IOT_Ring_Rx[iot_rx_wr++] = iot_receive; // Add to Ring Buffer
        if(iot_rx_wr >= sizeof(IOT_Ring_Rx)){
            iot_rx_wr = BEGINNING;
        }
        // UCA1IE |= UCTXIE;
        UCA1TXBUF = iot_receive;
    }break;
    case 4:{ // Vector 4 – Tx0IFG

        UCA0TXBUF = iot_TX_buf[iot_tx];
        iot_TX_buf[iot_tx++] = 0;
        if(iot_TX_buf[iot_tx] == 0x00) {
            UCA0IE &= ~UCTXIE;
            iot_tx = 0;
        }

    }break;

    default: break;
    }
}//------------------------------------------------------------------------------

#pragma vector = EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){ //This interrupt is the interrupt relating to serial communication port UCA1
    //------------------------------------------------------------------------------
    // Interrupt name: eUSCI_A1_ISR
    // Description: This interrupt transmits and receives through UCA1
    //------------------------------------------------------------------------------
    char usb_value;
    switch(__even_in_range(UCA1IV,0x08)){
    case 0: break; //Vector 0 - no interrupt
    case 2:{ // Vector 2 - Rx1IFG
        usb_value = UCA1RXBUF;
        USB_Ring_Rx[usb_rx_wr++] = usb_value; // Add to Ring Buffer
        if(usb_rx_wr >= sizeof(USB_Ring_Rx)){
            usb_rx_wr = BEGINNING;
        }
        UCA0TXBUF = usb_value;
        // UCA0IE |= UCTXIE;
    }break;
    case 4:{ // Vector 4 - TX1IFG
        UCA1TXBUF = IOT_Ring_Rx[direct_iot++];
        // IOT_Ring_Rx[direct_iot++]= 0;
        if(direct_iot >= sizeof(IOT_Ring_Rx)){
            direct_iot = BEGINNING;
        }
        if(iot_rx_wr == direct_iot){
            UCA1IE &= ~UCTXIE;
        }
    }break;
    default:
        break;
    }
    //------------------------------------------------------------------------------
}
