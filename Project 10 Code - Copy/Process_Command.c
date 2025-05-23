/*
 * Process_Command.c
 *
 * File to trigger certain commands given what was displayed from IOT_Process
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

extern unsigned short int timerFlag, count2, padNumber, escapeFlag;
extern unsigned int line;
extern long int k;
extern int nextStep;

extern volatile unsigned char display_changed, update_display;
extern volatile char allowedToStart, IOT_Data[4][32];
extern char charCheck, commands;

void Process_Command(void), Magic_Smoke(void);

void Process_Command(void) {

    int j;

    for (j = 0; j < sizeof(IOT_Data[line]); j++) {

        charCheck = IOT_Data[line][j];

        switch (charCheck) {
        case '^':
            commands = IOT_Data[line][j + 1];
            char commands2 = IOT_Data[line][j + 2];

            timerFlag = 1;

            switch (commands) {
            case 'F':
                Magic_Smoke();                     // Prevent Wheel blow up
                k = FBCOUNT;

                strcpy(display_line[3], " FORWARD  ");

                if (count2++ < k) {
                    RIGHT_FORWARD_SPEED = RSLOW;    // P6.1 Right Forward PWM duty cycle
                    RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM duty cycle
                    LEFT_FORWARD_SPEED = LSLOW;     // P6.3 Left Forward PWM duty cycle
                    LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.4 Left Reverse PWM duty cycle
                }
                break;

            case 'B':
                Magic_Smoke();                     // Prevent Wheel blow up
                k = FBCOUNT;

                strcpy(display_line[3], " BACKWARD ");

                if (count2++ < k) {
                    RIGHT_FORWARD_SPEED = WHEEL_OFF;    // P6.1 Right Forward PWM duty cycle
                    RIGHT_REVERSE_SPEED = RSLOW; // P6.2 Right Reverse PWM duty cycle
                    LEFT_FORWARD_SPEED = WHEEL_OFF;     // P6.3 Left Forward PWM duty cycle
                    LEFT_REVERSE_SPEED = LSLOW; // P6.4 Left Reverse PWM duty cycle
                }

                break;

            case 'R':
                Magic_Smoke();                     // Prevent Wheel blow up
                k = LRCOUNT;

                strcpy(display_line[3], "   RIGHT  ");

                if (count2++ < k) {
                    RIGHT_FORWARD_SPEED = WHEEL_OFF;    // P6.1 Right Forward PWM duty cycle
                    RIGHT_REVERSE_SPEED = RSLOW; // P6.2 Right Reverse PWM duty cycle
                    LEFT_FORWARD_SPEED = LSLOW;     // P6.3 Left Forward PWM duty cycle
                    LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.4 Left Reverse PWM duty cycle
                }

                break;

            case 'L':
                Magic_Smoke();                     // Prevent Wheel blow up
                k = LRCOUNT;

                strcpy(display_line[3], "   LEFT   ");

                if (count2++ < k) {
                    RIGHT_FORWARD_SPEED = RSLOW;    // P6.1 Right Forward PWM duty cycle
                    RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM duty cycle
                    LEFT_FORWARD_SPEED = WHEEL_OFF;     // P6.3 Left Forward PWM duty cycle
                    LEFT_REVERSE_SPEED = LSLOW; // P6.4 Left Reverse PWM duty cycle
                }

                break;

            case 'G':
                Magic_Smoke();                     // Prevent Wheel blow up

                strcpy(display_line[3], "  ROUTE   ");

                allowedToStart = 1;

                break;

            case 'E':
                Magic_Smoke();                     // Prevent Wheel blow up

                strcpy(display_line[3], "  ESCAPE  ");

                nextStep = FALSE;
                escapeFlag = TRUE;


                break;

            case 'S':
                Magic_Smoke();                     // Prevent Wheel blow up

                padNumber++;

                RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Right Forward PWM duty cycle
                RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM duty cycle
                LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.3 Left Forward PWM duty cycle
                LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.4 Left Reverse PWM duty cycle

                strcpy(display_line[1], "Arrived   ");
                display_line[1][9] = padNumber;

                display_changed = TRUE;
                update_display = 1;

                break;

            case '1':
                strcpy(display_line[1], "Arrived  1");

                break;

            case '2':
                strcpy(display_line[1], "Arrived  2");

                break;

            case '3':
                strcpy(display_line[1], "Arrived  3");

                break;

            case '4':
                strcpy(display_line[1], "Arrived  4");

                break;

            case '5':
                strcpy(display_line[1], "Arrived  5");

                break;

            case '6':
                strcpy(display_line[1], "Arrived  6");

                break;

            case '7':
                strcpy(display_line[1], "Arrived  7");

                break;

            case '8':
                strcpy(display_line[1], "Arrived  8");

                break;

            } break;

            case '\r': break;

            case '\n': break;

            default: break;
        }
    }
}


