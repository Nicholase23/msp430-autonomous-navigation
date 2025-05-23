//------------------------------------------------------------------------------
//
//  Description: This file contains the Display Process Routine
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

void Display_Process(void);

extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;

void Display_Process(void){
  if(update_display){
    update_display = 0;
    if(display_changed){
      display_changed = 0;
      Display_Update(0,0,0,0);
    }
  }
}
