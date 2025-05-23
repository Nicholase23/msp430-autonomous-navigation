/*
 * Check_Movement.c
 *
 *
 * File for checking if the car is still in motion after receiving the commands and stopping it from going any longer
 *  Created on: Dec 8, 2023
 *      Author: Nicholas Edwards
 */

#include  "msp430.h"
#include  <string.h>
#include  "include\functions.h"
#include  "Include\LCD.h"
#include  "include\ports.h"
#include  "macros.h"

extern unsigned short int count2;
extern long int k;

void Check_Movement(void);

void Check_Movement(void) {
    if (count2++ >= k) {
        RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Right Forward PWM duty cycle
        RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM duty cycle
        LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.3 Left Forward PWM duty cycle
        LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.4 Left Reverse PWM duty cycle

        count2 = 0;
    }
}
