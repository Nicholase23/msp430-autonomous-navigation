/*
 * adc_line.c
 *
 * File for collecting ADC values and placing them onto the desired location in the array.
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

void adc_line(char, char);

extern char display_line[4][11], adc_char[4];

//-------------------------------------------------------------
// ADC Line insert
// Take the HEX to BCD value in the array adc_char and place it
// in the desired location on the desired line of the display.
// char line => Specifies the line 1 thru 4
// char location => Is the location 0 thru 9
//
//-------------------------------------------------------------
void adc_line(char line, char location) {
    int i;
    unsigned int real_line;
    real_line = line - 1;

    for (i = 0; i < 4; i++) {
        display_line[real_line][i + location] = adc_char[i];
    }
}
