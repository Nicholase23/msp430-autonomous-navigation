//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//  Nicholas Edwards
//  Oct 2023
//  Built with Code Composer Version: CCS12.4.0.00007_win64
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  <string.h>
#include  "include\functions.h"
#include  "Include\LCD.h"
#include  "include\ports.h"
#include  "macros.h"

// Function Prototypes
void main(void), Init_Conditions(void), Display_Process(void), Init_LEDs(void), Init_Ports(void), Init_Timers(void), IOT_Process(void), Magic_Smoke(void);
extern void Init_ADC(void), Init_Serial_UCA0(void), Init_Serial_UCA1(void), Init_DAC(void); // Initialize Serial Port for USB

extern void HEXtoBCD(int), adc_line(char, char), Black_Line_Route(void), Escape_Route(void), Process_Command(void), Check_Movement(void);

// Global Variables
volatile char slow_input_down;
volatile unsigned int second;

extern char display_line[4][11];
extern char *display[4];
extern unsigned char display_mode;

extern volatile unsigned char display_changed, update_display;
extern volatile unsigned int update_display_count2;

unsigned int test_value;
char chosen_direction, change;
volatile char event;

// Serial Communication Variables
extern unsigned int ADC_Left_Detect, ADC_Right_Detect;
extern volatile char allowedToStart;
extern char flag;

extern char iot_receive;

extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
char last_String[SMALL_RING_SIZE];
extern char process_buffer[25]; // Size for appropriate Command Length

extern volatile unsigned int iot_rx_wr, iot_tx, usb_rx_wr;

extern volatile char IOT_Ring_Rx[SMALL_RING_SIZE];
volatile char IOT_Data[4][32];
extern volatile char iot_TX_buf[SMALL_RING_SIZE];

extern volatile unsigned int iot_rx_wr;
extern unsigned int iot_rx_rd; // Only used in Main
extern unsigned int direct_iot; // Only used it Interrupt

extern volatile unsigned int usb_rx_wr;
extern unsigned int usb_rx_rd; // Only used in Main
extern unsigned int direct_usb; // Only used it Interrupt

extern int command1;
extern int cycle;

unsigned int line = 0;
unsigned int character = 0;
unsigned int nextline;

int newlineCheck = 0;
int done = 0;
char charCheck = 0x30;
char commands;

long int k = 0;

extern volatile unsigned int second2;
unsigned short int timerFlag = 0;

extern unsigned short int ipFLag;
unsigned short int quoteCounter = 0;
extern unsigned int white_line, black_line;

int firstTimeInCase = TRUE;
unsigned short int mvmt = DELAY; // Project 6 var for case statement
int nextStep = 0;
unsigned short int timer = 0;
unsigned short int count2 = 0;
unsigned short int count3 = 0;
unsigned short int count3Flag = 0;
unsigned short int escapeFlag = 0;
unsigned short int padNumber = 0;


//void main(void){
void main(void){
    event = '\0';
    //    WDTCTL = WDTPW | WDTHOLD;   // stop watch dog timer
    //    trigger = 0;

    //------------------------------------------------------------------------------
    // Main Program
    // This is the main routine for the program. Execution of code starts here.
    // The operating system is Back Ground Fore Ground.
    //
    //------------------------------------------------------------------------------
    PM5CTL0 &= ~LOCKLPM5;
    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings

    //Do not need to worry about ADC Detect Values on LCD.//

    Init_Ports();                        // Initialize Ports
    Init_Clocks();                       // Initialize Clock System
    Init_Conditions();                   // Initialize Variables and Initial Conditions
    Init_Timers();                       // Initialize Timers
    Init_LCD();                          // Initialize LCD
    Init_ADC();                          // Initialize ADC
    Init_Serial_UCA0();                  // Initialize Serial Port for UCA0
    Init_Serial_UCA1();                  // Initialize Serial Port for UCA1
    //Init_DAC();                        // Initialize DAC board

    //P2OUT &= ~RESET_LCD;
    // Place the contents of what you want on the display, in between the quotes
    // Limited to 10 characters per line
    strcpy(display_line[0], "          ");
    strcpy(display_line[1], "          ");
    strcpy(display_line[2], "          ");
    strcpy(display_line[3], "          ");

    HEXtoBCD(ADC_Left_Detect);
    HEXtoBCD(ADC_Right_Detect);

    LCD_BACKLITE_DIMING = 0; // P6.0 Right Forward PWM duty cycle

    RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Right Forward PWM duty cycle
    RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM duty cycle
    LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.3 Left Forward PWM duty cycle
    LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.4 Left Reverse PWM duty cycle

    //Display_Update(0,0,0,0);

    //wheel_move = 0;
    //forward = TRUE;
    //------------------------------------------------------------------------------
    // Beginning of the "While" Operating System
    //------------------------------------------------------------------------------

    while(ALWAYS) {                      // Can the Operating system run
        Display_Process();                 // Update Display
        Magic_Smoke();                     // Prevent Wheel blow up
        IOT_Process();                     //Process commands received by IOT
        Check_Movement();                  //Checks to see if the wheels are in motion or not.

        if (allowedToStart) {
            Black_Line_Route();            //Function for following the black line.
        }

        if (escapeFlag == TRUE) {
            Escape_Route();                //Function for leaving the black line and mat
        }
        P3OUT ^= TEST_PROBE;               // Change State of TEST_PROBE OFF
    }
}
