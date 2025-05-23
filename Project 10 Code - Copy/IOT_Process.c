/*
 * IOT_Process.c
 *
 * File to process commands received by IOT module
 *
 *  Created on: Dec 8, 2023
 *      Author: Nicholas Edwards
 */

#include  "msp430.h"
#include  <string.h>
#include  "include\functions.h"
#include  "Include\LCD.h"
#include  "include\ports.h"
#include  "macros.h"

extern volatile unsigned int iot_rx_wr;
extern unsigned int iot_rx_rd, line, character;

extern volatile char IOT_Ring_Rx[SMALL_RING_SIZE], IOT_Data[4][32];

extern void Process_Command(void);

void IOT_Process(void);

void IOT_Process(void) {

    int i;

    if(iot_rx_wr != iot_rx_rd){

        IOT_Data[line][character] = IOT_Ring_Rx[iot_rx_rd++];

        IOT_Ring_Rx[iot_rx_rd - 1] = 0;

        if(IOT_Data[line][character] == '\n') {
            Process_Command();

            character = 0;
            line++;

            for (i = 0; i < sizeof(IOT_Data[line]); i++) {
                IOT_Data[line][i] = 0;
            }

            if(line >= 4) {
                line = 0;
            }
        }

        character++;
    }

    if(iot_rx_rd >= sizeof(IOT_Ring_Rx)){
        iot_rx_rd = BEGINNING;
    }
}
