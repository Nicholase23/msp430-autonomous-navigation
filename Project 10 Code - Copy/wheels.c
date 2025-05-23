/*
 * Nicholas Edwards
 * Created by: Dec 8, 2023
 *
 * This is the File to control the motion of the wheels - Forward, Stopping, and Magic Smoke
 */

#include  "msp430.h"
#include  <string.h>
#include  "include\functions.h"
#include  "Include\LCD.h"
#include  "include\ports.h"
#include  "macros.h"

void Forward(void), Stop(void), Magic_Smoke(void);

void Forward(void) { //Function to drive the Wheels forward
    P6OUT &= ~L_REVERSE; // Set Port pin Low [Wheel Off]
    P6OUT &= ~R_REVERSE; // Set Port pin Low [Wheel Off]
    P6OUT |= L_FORWARD; // Set Port pin High [Wheel On]
    P6OUT |= R_FORWARD; // Set Port pin High [Wheel On]
}

void Stop(void) { //Function to Stop all wheels
    P6OUT &= ~L_FORWARD; // Set Port pin Low [Wheel Off]
    P6OUT &= ~R_FORWARD; // Set Port pin Low [Wheel Off]
    P6OUT &= ~L_REVERSE; // Set Port pin Low [Wheel Off]
    P6OUT &= ~R_REVERSE; // Set Port pin Low [Wheel Off]
}

void Magic_Smoke(void){ //Function to Stop the Wheels from trying to go forward and backward at the same time
    if (((P6IN & L_FORWARD)) && ((P6IN & L_REVERSE)))
        {
        P6OUT &= ~L_FORWARD; // Set Port pin Low [Wheel Off]
        P6OUT &= ~R_FORWARD; // Set Port pin Low [Wheel Off]
        P6OUT &= ~L_REVERSE; // Set Port pin Low [Wheel Off]
        P6OUT &= ~R_REVERSE; // Set Port pin Low [Wheel Off]
        P1OUT |= RED_LED;  // Change State of LED 4
        P6OUT &= ~GRN_LED; // Change State of LED 5
        }

    if (((P6IN & R_FORWARD)) && ((P6IN & R_REVERSE)))
        {
        P6OUT &= ~L_FORWARD; // Set Port pin Low [Wheel Off]
        P6OUT &= ~R_FORWARD; // Set Port pin Low [Wheel Off]
        P6OUT &= ~L_REVERSE; // Set Port pin Low [Wheel Off]
        P6OUT &= ~R_REVERSE; // Set Port pin Low [Wheel Off]
        P1OUT |= RED_LED;  // Change State of LED 4
        P6OUT &= ~GRN_LED; // Change State of LED 5
        }
}
