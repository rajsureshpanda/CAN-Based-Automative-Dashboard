/*
 * File:   ecu2_sensor.c
 * Author: Raj
 *
 * Created on 2 April, 2026, 3:04 PM
 */


#include <xc.h>
#include"main.h"


uint16_t get_speed()
{
    // Implement the speed function
    unsigned int val = ((read_adc(CHANNEL4)) / 10.23);

    return val;
}

unsigned char get_gear_pos()
{
    // Implement the gear function
    static unsigned char inc = 0;

    unsigned char key = read_digital_keypad(EDGE);

    if(key == SWITCH1)
    {
        if(inc < 6)
            inc++;
    }
    else if(key == SWITCH2)
    {
        if(inc > 0)
            inc--;
    }

    return inc;
    
}
