/*
 * File:   main.c
 * Author: Raj
 *
 * Created on 3 April, 2026, 3:44 PM
 */


#include <xc.h>
#include"main.h"


static void init_leds() {
    TRISB0 = TRISB7 = 0; // Set RB2 as output, RB3 as input, remaining as output
    RB0 = RB7 = 0;
    
}

static void init_config(void) {
    // Initialize
    init_clcd();
    init_can();
    init_leds();
}

void main(void) {
    // Initialize peripherals
    init_config();
    
    CLEAR_DISP_SCREEN;
    
    clcd_print("RPM  IND SPD GEA", LINE1(0));
    /* ECU1 main loop */
    while (1) {
        // Read CAN Bus data and handle it
        process_canbus_data();
    }

    return;
}
