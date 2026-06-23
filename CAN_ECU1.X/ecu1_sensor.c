/*
 * File:   ecu1_sensor.c
 * Author: Raj
 *
 * Created on 1 April, 2026, 11:55 AM
 */


#include"main.h"

uint16_t get_rpm(unsigned int value)
{
    //Implement the rpm function
    
    uint16_t rpm = 0;
    rpm = ((read_adc(value) / 10.23) * 60);
    
    return rpm;
    
}

//uint16_t get_engine_temp()
//{
//    //Implement the engine temperature function
//}

IndicatorStatus process_indicator()
{
    //Implement the indicator function
    static IndicatorStatus current_status = e_ind_off;

    unsigned char key = read_digital_keypad(EDGE);
    
    if(key == SWITCH1)
    {
        
        current_status = e_ind_left;
    }
    else if(key == SWITCH2)
    {
        
        current_status = e_ind_right;
    }
    else if(key == SWITCH3)
    {
        
        current_status = e_ind_hazard;
    }
    else if(key == SWITCH4)
    {
        
        current_status = e_ind_off;
    }
    
    
    return current_status;
}
