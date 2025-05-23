/*
 * Escape_Route.c
 *
 * File for commanding the car to break out of the Black Line Route
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

extern unsigned short int timer, count3, timerFlag, escapeFlag;
extern char display_line[4][11];

extern void Magic_Smoke(void);

void Escape_Route(void);

void Escape_Route(void) {

    if (timer <= TIMER_THRESHOLD) {
        Magic_Smoke();                     // Prevent Wheel blow up

        strcpy(display_line[3], " TURNOUT  "); //Display that car is moving

        RIGHT_FORWARD_SPEED = RSLOW; // P6.1 Right Forward PWM duty cycle
        LEFT_REVERSE_SPEED = LSLOW; // P6.3 Left Forward PWM duty cycle
        timer++;
    }

    else if (timer > TIMER_THRESHOLD && count3 < COUNT_THRESHOLD) {
        Magic_Smoke();                     // Prevent Wheel blow up

        strcpy(display_line[3], " PULLOUT  "); //Display that car is moving

        LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.4 Left Reverse PWM duty cycle
        RIGHT_FORWARD_SPEED = RSLOWEST; // P6.1 Right Forward PWM duty cycle
        LEFT_FORWARD_SPEED = LSLOWEST; // P6.3 Left Forward PWM duty cycle
        count3++;
        timer++;
    }

    else { //Come back to this...it works, but it keeps turning on the Red LED.//
        Magic_Smoke();                     // Prevent Wheel blow up

        RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Right Forward PWM duty cycle
        RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM duty cycle
        LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.3 Left Forward PWM duty cycle
        LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.4 Left Reverse PWM duty cycle

        strcpy(display_line[3], "  FINISH  "); //Display that car is moving

        timerFlag = FALSE;

        escapeFlag = FALSE;
    }
}
