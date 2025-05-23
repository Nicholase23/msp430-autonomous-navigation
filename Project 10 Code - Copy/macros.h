/*
 * macros.h
 *
 *  Created on: Sep 15, 2023
 *      Author: Nicholas Edwards
 */

#ifndef MACROS_H_
#define MACROS_H_

#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1
#define TEST_PROBE           (0x01) // 0 TEST PROBE
#define TRUE                 (0x01) //

#define DELAY                  (1)
#define TURN                   (2)
#define PAUSE                  (3)
#define FOLLOW                 (4)
#define DONE                   (5)

// STATES ======================================================================
#define NONE ('N')
#define STRAIGHT ('L')
#define CIRCLE ('C')
#define FIGURE8 ('F')
#define TRIANGLE ('T')
#define WAIT ('W')
#define START ('S')
#define RUN ('R')
#define RUN2 ('Q')
#define END ('E')
#define WAITING2START (100)

  // Global Variables
volatile char slow_input_down;
extern char display_line[4][11];
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;
extern char state;
extern unsigned int travel_distance;
extern unsigned int wheel_count_time;
extern unsigned int right_count_time;
extern unsigned int left_count_time;

unsigned int wheel_move;
char forward;

unsigned int Last_Time_Sequence; // a variable to identify Time_Sequence has changed
unsigned int cycle_time; // is a new time base used to control making shapes
unsigned int time_change; // is an identifier that a change has occurred

unsigned int left_motor_count;
unsigned int right_motor_count;
unsigned int segment_count;

#define NOT_OKAY ('N')
#define OKAY ('O')
#define PRESSED ('P')
#define RELEASED ('R')

#define TB0CCR0_INTERVAL (30000)
#define TB0CCR1_INTERVAL (30000)
#define TB0CCR2_INTERVAL (30000)

#define PWM_PERIOD (TB3CCR0)
#define LCD_BACKLITE_DIMING (TB3CCR1)
#define RIGHT_FORWARD_SPEED (TB3CCR2)
#define RIGHT_REVERSE_SPEED (TB3CCR3)
#define LEFT_FORWARD_SPEED  (TB3CCR4)
#define LEFT_REVERSE_SPEED  (TB3CCR5)

#define RSLOW       (20500)
#define RSLOWER     (13000)
#define RSLOWEST    (7100)
#define LSLOW       (20875)
#define LSLOWER     (13375)
#define LSLOWEST    (7475)
#define FAST        (50000)
#define PERCENT_100 (50000)
#define PERCENT_80  (45000)

#define FBCOUNT     (39000)
#define LRCOUNT     (13000)

#define TIMER_THRESHOLD (50000)
#define COUNT_THRESHOLD (30000)

#define RESET_REGISTER (0)

// #defines
#define BEGINNING (0)
#define SMALL_RING_SIZE (16)
#define LARGE_RING_SIZE (32)

#endif /* MACROS_H_ */
