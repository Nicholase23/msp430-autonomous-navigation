/*
 * Init_Serial_UCA0.c
 *
 *  File to initialize serial port for A0 and A1
 *
 * Created on: Nov. 2, 2023
 * Author: Nicholas Edwards
 */

#include "msp430.h"
#include <string.h>
#include "include\functions.h"
#include "Include\LCD.h"
#include "include\ports.h"
#include "macros.h"

// Function to initialize Serial Communication on UCA0
void Init_Serial_UCA0(void), Init_Serial_UCA1(void);

volatile unsigned int usb_rx_ring_wr, usb_rx_ring_rd, usb_tx_ring_wr, usb_tx_ring_rd;
volatile char USB_Char_Rx[SMALL_RING_SIZE], USB_Char_Tx[LARGE_RING_SIZE];

// Initialize Serial Communication on UCA0
void Init_Serial_UCA0(void) {
    //------------------------------------------------------------------------------
    // TX error (%) RX error (%)
    // BRCLK   Baudrate UCOS16 UCBRx UCFx UCSx  neg    pos   neg    pos
    // 8000000 4800     1      104   2    0xD6  -0.08  0.04  -0.10  0.14
    // 8000000 9600     1      52    1    0x49  -0.08  0.04  -0.10  0.14
    // 8000000 19200    1      26    0    0xB6  -0.08  0.16  -0.28  0.20
    // 8000000 57600    1      8     10   0xF7  -0.32  0.32  -1.00  0.36
    // 8000000 115200   1      4     5    0x55  -0.80  0.64  -1.12  1.76
    // 8000000 460800   0      17    0    0x4A  -2.72  2.56  -3.76  7.28
    //------------------------------------------------------------------------------
    // Configure eUSCI_A0 for UART mode
    UCA0CTLW0 = 0;
    UCA0CTLW0 |= UCSWRST ; // Put eUSCI in reset
    UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
    UCA0CTLW0 &= ~UCMSB; // MSB, LSB select
    UCA0CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
    UCA0CTLW0 &= ~UCPEN; // No Parity
    UCA0CTLW0 &= ~UCSYNC;
    UCA0CTLW0 &= ~UC7BIT;
    UCA0CTLW0 |= UCMODE_0;

    unsigned int i;

    // Initialize USB Rx Buffer
    for (i = 0; i < SMALL_RING_SIZE; i++) {
        USB_Char_Rx[i] = 0x00;
    }

    usb_rx_ring_wr = BEGINNING;
    usb_rx_ring_rd = BEGINNING;

    // Initialize USB Tx Buffer (may not use this)
    for (i = 0; i < LARGE_RING_SIZE; i++) {
        USB_Char_Tx[i] = 0x00;
    }
    usb_tx_ring_wr = BEGINNING;
    usb_tx_ring_rd = BEGINNING;

    // Configure UART 0
    UCA0CTLW0 = 0;              // Use word register
    UCA0CTLW0 |= UCSWRST;       // Set Software reset enable
    UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK

    // UART Configuration Settings
    // BRCLK   Baudrate UCOS16 UCBRx UCFx UCSx neg   pos  neg   pos
    // 8000000 115200   1      4     5    0x55 -0.80 0.64 -1.12 1.76

    // Set UCAxMCTLW using the following formula
    // UCAxMCTLW = UCSx + UCFx + UCOS16

    UCA0BRW = 4 ; // 115,200 baud
    UCA0MCTLW = 0x5551 ;

    UCA0CTLW0 &= ~UCSWRST;  // Clear Software reset enable
    UCA0IE |= UCRXIE;       // Enable RX interrupt
}

// Initialize Serial Communication on UCA1
void Init_Serial_UCA1(void) {
    //------------------------------------------------------------------------------
    // TX error (%) RX error (%)
    // BRCLK   Baudrate UCOS16 UCBRx UCFx UCSx  neg    pos   neg    pos
    // 8000000 4800     1      104   2    0xD6  -0.08  0.04  -0.10  0.14
    // 8000000 9600     1      52    1    0x49  -0.08  0.04  -0.10  0.14
    // 8000000 19200    1      26    0    0xB6  -0.08  0.16  -0.28  0.20
    // 8000000 57600    1      8     10   0xF7  -0.32  0.32  -1.00  0.36
    // 8000000 115200   1      4     5    0x55  -0.80  0.64  -1.12  1.76
    // 8000000 460800   0      17    0    0x4A  -2.72  2.56  -3.76  7.28
    //------------------------------------------------------------------------------
    // Configure eUSCI_A1 for UART mode
    UCA1CTLW0 = 0;
    UCA1CTLW0 |= UCSWRST ; // Put eUSCI in reset
    UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
    UCA1CTLW0 &= ~UCMSB; // MSB, LSB select
    UCA1CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
    UCA1CTLW0 &= ~UCPEN; // No Parity
    UCA1CTLW0 &= ~UCSYNC;
    UCA1CTLW0 &= ~UC7BIT;
    UCA1CTLW0 |= UCMODE_0;

    unsigned int i;

    // Initialize USB Rx Buffer
    for (i = 0; i < SMALL_RING_SIZE; i++) {
        USB_Char_Rx[i] = 0x00;
    }

    usb_rx_ring_wr = BEGINNING;
    usb_rx_ring_rd = BEGINNING;

    // Initialize USB Tx Buffer (may not use this)
    for (i = 0; i < LARGE_RING_SIZE; i++) {
        USB_Char_Tx[i] = 0x00;
    }
    usb_tx_ring_wr = BEGINNING;
    usb_tx_ring_rd = BEGINNING;

    // Configure UART 1
    UCA1CTLW0 = 0;              // Use word register
    UCA1CTLW0 |= UCSWRST;       // Set Software reset enable
    UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK

    // UART Configuration Settings
    // BRCLK   Baudrate UCOS16 UCBRx UCFx UCSx neg   pos  neg   pos
    // 8000000 115200   1      4     5    0x55 -0.80 0.64 -1.12 1.76

    // Set UCAxMCTLW using the following formula
    // UCAxMCTLW = UCSx + UCFx + UCOS16

    UCA1BRW = 4 ; // 115,200 baud
    UCA1MCTLW = 0x5551 ;

    UCA1CTLW0 &= ~UCSWRST;  // Clear Software reset enable
    UCA1IE |= UCRXIE;       // Enable RX interrupt
}
