/*
 * HEXtoBCD.c
 *
 *  File to Convert a Hex number to a BCD for display on an LCD or monitor
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

extern void HEXtoBCD(int);

char adc_char[4];

//-----------------------------------------------------------------
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//-----------------------------------------------------------------
void HEXtoBCD(int hex_value) {
    int value, i;
    value = 0;

    for (i = 0; i < 4; i++) {
        adc_char[i] = '0';
    }

    while (hex_value > 999) {
        hex_value = hex_value - 1000;
        value = value + 1;
        adc_char[0] = 0x30 + value;
    }

    value = 0;

    while (hex_value > 99) {
        hex_value = hex_value - 100;
        value = value + 1;
        adc_char[1] = 0x30 + value;
    }

    value = 0;

    while (hex_value > 9) {
        hex_value = hex_value - 10;
        value = value + 1;
        adc_char[2] = 0x30 + value;
    }

    adc_char[3] = 0x30 + hex_value;
}

