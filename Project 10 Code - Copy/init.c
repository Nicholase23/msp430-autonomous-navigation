//------------------------------------------------------------------------------
//
//  Description: This file contains the Initialization functions for the System
//
//  Nicholas Edwards
//  Sep 2023
//  Built with Code Composer Version: CCS12.4.0.00007_win64
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  <string.h>
#include  "include\functions.h"
#include  "Include\LCD.h"
#include  "include\ports.h"
#include  "macros.h"

void Init_Conditions(void);

extern char display_line[4][11];
extern char *display[4];
extern volatile unsigned char update_display;
volatile unsigned int DAC_data;

void Init_Conditions(void){
//------------------------------------------------------------------------------

  int i;
  for(i=0;i<11;i++){
    display_line[0][i] = RESET_STATE;
    display_line[1][i] = RESET_STATE;
    display_line[2][i] = RESET_STATE;
    display_line[3][i] = RESET_STATE;
  }
  display_line[0][10] = 0;
  display_line[1][10] = 0;
  display_line[2][10] = 0;
  display_line[3][10] = 0;

  display[0] = &display_line[0][0];
  display[1] = &display_line[1][0];
  display[2] = &display_line[2][0];
  display[3] = &display_line[3][0];
  update_display = 0;


// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}

void Init_DAC(void) {
    DAC_data = 4000; // Value between 0x000 and 0x0FFF
    SAC3DAT = DAC_data; // Initial DAC data
    SAC3DAC = DACSREF_1; // Select internal Vref as DAC reference
    SAC3DAC = DACLSEL_0; // DAC latch loads when DACDAT is written

    // Uncomment the following line if you want to generate an interrupt
    // SAC3DAC |= DACIE;

    SAC3DAC |= DACEN; // Enable DAC
    SAC3OA = NMUXEN; // SAC3 Negative input MUX control
    SAC3OA |= PMUXEN; // SAC3 Positive input MUX control
    SAC3OA |= PSEL_1; // 12-bit reference DAC source selected
    SAC3OA |= NSEL_1; // Select negative pin input
    SAC3OA |= OAPM; // Select low speed and low power mode
    SAC3PGA |= MSEL_1; // Set OA as buffer mode
    SAC3OA |= SACEN; // Enable SAC3
    SAC3OA |= OAEN; // Enable OA

    // Additional configurations or operations can be added here if needed.
}
