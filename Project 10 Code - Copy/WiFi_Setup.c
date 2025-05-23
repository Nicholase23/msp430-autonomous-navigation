/*
 * WiFi_Setup.c
 *
 * File to configure WiFi settings for IOT module to receive commands
 *
 *  Created on: Dec 5, 2023
 *      Author: Nicholas Edwards
 */

#include "msp430.h"
#include <string.h>
#include "include\functions.h"
#include "Include\LCD.h"
#include "include\ports.h"
#include "macros.h"

extern unsigned short int press_counter;
extern volatile char iot_TX_buf[30];
extern char display_line[4][11];
extern volatile char IOT_Data[4][32];
extern unsigned int direct_iot; // Only used it Interrupt

unsigned short int ipFLag = 0;

char SYSSTORE[20] = {"AT+SYSSTORE=0\r\n"};
char CIPMUX[20] = {"AT+CIPMUX=1\r\n"};           // Configure multi connections
char CIPSERVER[25] = {"AT+CIPSERVER=1,8040\r\n"};    // Configure port
char CIFSR[25] = {"AT+CIFSR\r\n"};

void WiFi_Setup(void) {

    int j;

    if (press_counter == 1) {

        for(j = 0; j < 30; j++){
            iot_TX_buf[j] = SYSSTORE[j];
        }

        direct_iot = 1;
        UCA0IE |= UCTXIE;
    }

    if (press_counter == 2) {

        for(j = 0; j < 30; j++){
            iot_TX_buf[j] = CIPMUX[j];
        }

        direct_iot = 1;
        UCA0IE |= UCTXIE;
    }

    if (press_counter == 3) {

        for(j = 0; j < 30; j++){
            iot_TX_buf[j] = CIPSERVER[j];
        }

        direct_iot = 1;
        UCA0IE |= UCTXIE;
    }

    if (press_counter == 4) {
        for(j = 0; j < 30; j++){
            iot_TX_buf[j] = CIFSR[j];
        }

        ipFLag++;

        direct_iot = 1;
        UCA0IE |= UCTXIE;
    }
}
