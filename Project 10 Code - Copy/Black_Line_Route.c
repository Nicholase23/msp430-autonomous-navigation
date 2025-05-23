/*
 * Black_Line_Route.c
 *
 * File for guiding the car to follow the Black Line
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

extern unsigned short int firstTimeInCase, nextStep, mvmt, timer, ADC_Left_Detect, ADC_Right_Detect;
extern volatile char IOT_Data[4][32];

extern void Magic_Smoke(void);

void Black_Line_Route(void);

void Black_Line_Route(void) {

    if ((firstTimeInCase == TRUE)) {
        Magic_Smoke(); //Prevent FOWARD and REVERSE on same wheel at same time

        RIGHT_FORWARD_SPEED = 16985; // P6.1 Right Forward PWM duty cycle
        RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM duty cycle
        LEFT_FORWARD_SPEED = 9900; // P6.3 Left Forward PWM duty cycle
        LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.4 Left Reverse PWM duty cycle

        strcpy(display_line[3], "  MOVING  "); //Display that car is moving

        if ((ADC_Left_Detect < 450) && (ADC_Left_Detect < 450) && (timer++ >= 30000)) {
            firstTimeInCase = FALSE; //Turn off flag to bar future readings of this case

            RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Right Forward PWM duty cycle
            LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.3 Left Forward PWM duty cycle

            if (timer++ >= 30000) {
                timer = 0;
                nextStep = TRUE;
            }
        }
    }

    if (nextStep == TRUE) {

        switch (mvmt) {

        case DELAY:

            strcpy(display_line[3], " DETECTED ");

            if (timer++ >= 30000) {
                timer = 0;
            }
            break;

        case TURN:
            LEFT_FORWARD_SPEED = LSLOWER; // P6.1 Right Forward PWM duty cycle
            RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.3 Left Forward PWM duty cycle
            RIGHT_REVERSE_SPEED = RSLOWEST; // P6.3 Left Forward PWM duty cycle

            timer++;

            strcpy(display_line[3], "   TURN   ");

            //When turning, it will leave black line before returning to it; so, if it detects BLACK for both detectors, then we know it should stop.
            if (/*(ADC_Right_Detect >= black_line) && (ADC_Left_Detect >= black_line) ||*/ (timer >= 18000)) {
                RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Right Forward PWM duty cycle
                RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM duty cycle
                LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.3 Left Forward PWM duty cycle
                LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.4 Left Reverse PWM duty cycle

                timer = 0;
                mvmt = FOLLOW;
            }
            break;

        case FOLLOW:

            strcpy(display_line[3], "  FOLLOW  "); //Display that car is moving

            if (ADC_Left_Detect < 575/*black_line*/) {
                RIGHT_FORWARD_SPEED = 7500; //RSLOWEST;//LSLOWER;//RSLOWEST; // P6.1 Right Forward PWM duty cycle
                LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.3 Left Forward PWM duty cycle
            }

            else if (ADC_Right_Detect < 575/*black_line*/) {
                RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Right Forward PWM duty cycle
                LEFT_FORWARD_SPEED = 7500; //LSLOWEST;//LSLOWEST;//LSLOW;//LSLOWEST; // P6.3 Left Forward PWM duty cycle

                timer++;

                if (timer >= 10000) {
                    RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Right Forward PWM duty cycle
                    LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.3 Left Forward PWM duty cycle

                    timer = 0;
                }
            }

            else if (ADC_Left_Detect >= 575/*black_line*/ && ADC_Right_Detect >= 575/*black_line*/) {
                RIGHT_FORWARD_SPEED = 7450; // P6.1 Right Forward PWM duty cycle
                LEFT_FORWARD_SPEED = 7450; // P6.3 Left Forward PWM duty cycle

                timer++;

                if (timer >= 10000) {
                    RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Right Forward PWM duty cycle
                    LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.3 Left Forward PWM duty cycle

                    timer = 0;
                }
            }

            break;

        default: break;
        }
    }
}

