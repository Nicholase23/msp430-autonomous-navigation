/*
 * ports.c
 *
 * File to configure all ports.
 *
 *  Created on: Sep 15, 2023
 *      Author: Nicholas Edwards
 */

#include  <string.h>
#include  "msp430.h"
#include  "include/functions.h"
#include "include/LCD.h"
#include  "include/ports.h"
#include "macros.h"

void Init_Ports(void){
 Init_Port1();
 Init_Port2();
 Init_Port3();
 Init_Port4();
 Init_Port5();
 Init_Port6();


}
void Init_Port1(void){ // Configure Port 1
//------------------------------------------------------------------------------
 P1OUT = 0x00; // P2 set Low
 P1DIR = 0x00; // Set P2 direction to output


 P1SEL0 &= ~RED_LED; // SLOW_CLK GPIO operation
 P1SEL1 &= ~RED_LED; // SLOW_CLK GPIO operation
 P1OUT &= ~RED_LED; // Initial Value = Low / Off
 P1DIR |= RED_LED; // Direction = output

 P1SEL0 |= A1_SEEED ; // LFXOUT Clock operation
 P1SEL1 |= A1_SEEED ; // LFXOUT Clock operation

 P1SEL0 |= V_DETECT_L; // LFXOUT Clock operation
 P1SEL1 |= V_DETECT_L; // LFXOUT Clock operation

 P1SEL0 |= V_DETECT_R;
 P1SEL1 |= V_DETECT_R;

 P1SEL0 |= A4_SEEED;
 P1SEL1 |= A4_SEEED;

 P1SEL0 |= V_THUMB;
 P1SEL1 |= V_THUMB;

 P1SEL0  |= UCA0RXD;
 P1SEL1  &= ~UCA0RXD;

 P1SEL0 |= UCA0TXD;
 P1SEL1 &= ~UCA0TXD;
}


void Init_Port2(void){ // Configure Port 2
//------------------------------------------------------------------------------
 P2OUT = 0x00; // P2 set Low
 P2DIR = 0x00; // Set P2 direction to output

 P2SEL0 &= ~RESET_LCD; // SLOW_CLK GPIO operation
 P2SEL1 &= ~RESET_LCD; // SLOW_CLK GPIO operation
 P2OUT &= ~RESET_LCD; // Initial Value = Low / Off
 P2DIR |= RESET_LCD; // Direction = output

 P2SEL0 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
 P2SEL1 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
 P2OUT &= ~CHECK_BAT; // Initial Value = Low / Off
 P2DIR |= CHECK_BAT; // Direction = output

 P2SEL0 &= ~IR_LED; // P2_2 GPIO operation
 P2SEL1 &= ~IR_LED; // P2_2 GPIO operation
 P2OUT |= IR_LED; // Initial Value = Low / Off
 P2DIR |= IR_LED; // Direction = input

 P2SEL0 &= ~SW2; // SW2 Operation
 P2SEL1 &= ~SW2; // SW2 Operation
 P2OUT |= SW2; // Configure pullup resistor
 P2DIR &= ~SW2; // Direction = input
 P2REN |= SW2; // Enable pullup resistor
 P2IES |= SW2; //Enables interrupt
 P2IFG &= ~SW2; //Clears interrupt
 P2IE |= SW2;   //Enables interrupt

 P2SEL0 &= ~IOT_RUN_RED; // IOT_RUN_CPU GPIO operation
 P2SEL1 &= ~IOT_RUN_RED; // IOT_RUN_CPU GPIO operation
 P2OUT &= ~IOT_RUN_RED; // Initial Value = Low / Off
 P2DIR |= IOT_RUN_RED; // Direction = input

 P2SEL0 &= ~DAC_ENB; // DAC_ENB GPIO operation
 P2SEL1 &= ~DAC_ENB; // DAC_ENB GPIO operation
 P2OUT |= DAC_ENB; // Initial Value = High
 P2DIR |= DAC_ENB; // Direction = output

 P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
 P2SEL1 |= LFXOUT; // LFXOUT Clock operation

 P2SEL0 &= ~LFXIN; // LFXIN Clock operation
 P2SEL1 |= LFXIN; // LFXIN Clock operation
 //------------------------------------------------------------------------------
}


void Init_Port3(void){ // Configure PORT 3

 P3OUT = 0x00; // P2 set Low
 P3DIR = 0x00; // Set P2 direction to output

 P3SEL0 &= ~TEST_PROBE; // SLOW_CLK GPIO operation
 P3SEL1 &= ~TEST_PROBE; // SLOW_CLK GPIO operation
 P3OUT &= ~TEST_PROBE; // Initial Value = Low / Off
 P3DIR |= TEST_PROBE; // Direction = output

 P3SEL0 |= OA2O;
 P3SEL1 |= OA2O;

 P3SEL0 |= OA2N;
 P3SEL1 |= OA2N;

 P3SEL0 |= OA2P;
 P3SEL1 |= OA2P;

 P3SEL0 &= ~SMCLK_OUT;
 P3SEL1 &= ~SMCLK_OUT;
 P3OUT &= ~SMCLK_OUT;
 P3DIR |= SMCLK_OUT;

 P3SEL0 |= DAC_CNTL;
 P3SEL1 |= DAC_CNTL;

 P3SEL0 |= IOT_LINK_GRN;
 P3SEL1 |= IOT_LINK_GRN;
 P3OUT  &= ~IOT_LINK_GRN;
 P3DIR  |= IOT_LINK_GRN;

 P3SEL0 |= IOT_EN;
 P3SEL1 |= IOT_EN;
 P3OUT  &= ~IOT_EN;
 P3DIR  |= IOT_EN;


}


void Init_Port4(void){ // Configure PORT 4
//------------------------------------------------------------------------------
 P4OUT = 0x00; // P4 set Low
 P4DIR = 0x00; // Set P4 direction to output

 P4SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
 P4SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
 P4OUT |= RESET_LCD; // Initial Value = Low / Off
 P4DIR |= RESET_LCD; // Direction = output

 P4SEL0 &= ~SW1; // SW2 Operation
 P4SEL1 &= ~SW1; // SW2 Operation
 P4OUT |= SW1; // Configure pull-up resistor
 P4DIR &= ~SW1; // Direction = input
 P4REN |= SW1; // Enable pull-up resistor
 P4IES |= SW1; //Enables interrupt
 P4IFG &= ~SW1; //Clears interrupt
 P4IE |= SW1;   //Enables interrupt

 P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
 P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation

 P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
 P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation

 P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
 P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
 P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]
 P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output

 P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
 P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation

 P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
 P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation

 P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
 P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation
 //------------------------------------------------------------------------------
}


void Init_Port5(void){ // Configure PORT 5

 P5SEL0 |= V_BAT;
 P5SEL1 |= V_BAT;

 P5SEL0 |= V_5_0;
 P5SEL1 |= V_5_0;

 P5SEL0 |= V_DAC;
 P5SEL1 |= V_DAC;

 P5SEL0 |= V_3_3;
 P5SEL1 |= V_3_3;

 P5SEL0 &= ~IOT_BOOT;
 P5SEL1 &= ~IOT_BOOT;
 P5OUT |= IOT_BOOT; // Initial Value = Low / Off
 P5DIR |= IOT_BOOT; // Direction = output


}


void Init_Port6(void){ // Configure PORT 6

 P6SEL0 |= LCD_BACKLITE;
 P6SEL1 &= ~LCD_BACKLITE;
 P6OUT &= ~LCD_BACKLITE; // Initial Value = Low / Off
 P6DIR |= LCD_BACKLITE; // Direction = output

 P6SEL0 |= R_FORWARD;
 P6SEL1 &= ~R_FORWARD;
 //P6OUT &= ~R_FORWARD; // Initial Value = Low / Off
 P6DIR |= R_FORWARD; // Direction = output

 P6SEL0 |=  R_REVERSE;
 P6SEL1 &= ~R_REVERSE;
 //P6OUT &= ~R_REVERSE; // Initial Value = Low / Off
 P6DIR |= R_REVERSE; // Direction = output

 P6SEL0 |=  L_FORWARD;
 P6SEL1 &= ~L_FORWARD;
 //P6OUT &= ~L_FORWARD; // Initial Value = Low / Off
 P6DIR |= L_FORWARD; // Direction = output

 P6SEL0 |=  L_REVERSE;
 P6SEL1 &= ~L_REVERSE;
 //P6OUT &= ~L_REVERSE; // Initial Value = Low / Off
 P6DIR |= L_REVERSE; // Direction = output

 P6SEL0 &= ~P6_5;
 P6SEL1 &= ~P6_5;
 P6OUT &= ~P6_5; // Initial Value = Low / Off
 P6DIR |= P6_5; // Direction = output

 P6SEL0 &= ~GRN_LED;
 P6SEL1 &= ~GRN_LED;
 P6OUT |= GRN_LED; // Initial Value = Low / Off
 P6DIR |= GRN_LED; // Direction = output


}
