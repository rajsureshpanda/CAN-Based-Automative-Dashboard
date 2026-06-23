/*
 * File:   message_handler.c
 * Author: Raj
 *
 * Created on 3 April, 2026, 3:45 PM
 */


#include <xc.h>
#include<string.h>
#include"main.h"

//volatile unsigned char led_state = LED_OFF, status = e_ind_off;


void handle_speed_data(uint8_t *data, uint8_t len)
{
    //Implement the speed function
    char speed_str[9];

    for(uint8_t i = 0; i < len; i++)
    {
        speed_str[i] = data[i];
    }

    speed_str[len] = '\0'; 
    clcd_print("    ", LINE2(9));
    clcd_print(speed_str, LINE2(9));
}

void handle_gear_data(uint8_t *data, uint8_t len) 
{
    //Implement the gear function
    char *gear[] = {"N","1","2","3","4","5","R"};
    clcd_print(gear[data[0]],LINE2(14));
}

void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    //Implement the rpm function
    
    char rpm_str[9];

    for(int i = 0; i < len; i++)
    {
        rpm_str[i] = data[i];
    }
    rpm_str[len] = '\0';   

    clcd_print(rpm_str, LINE2(0));
    
}

void handle_engine_temp_data(uint8_t *data, uint8_t len) 
{
    //Implement the temperature function
}

void handle_indicator_data(uint8_t *data, uint8_t len) 
{
    //Implement the indicator function
    static unsigned char delay = 0;
    unsigned char blink_time = 2;
    static unsigned char led_state = 0;
    unsigned char pattern = 0x00;
     
    char ind_str[10];

    // Convert to string
    for(uint8_t i = 0; i < len; i++)
    {
        ind_str[i] = data[i];
    }
    ind_str[len] = '\0';

    if(strcmp(ind_str, "LEF") == 0)
    {
        pattern = LEFT_IND_ON();
        clcd_print("LEF   ", LINE2(5));
    }
    else if(strcmp(ind_str, "RIG") == 0)
    {
        pattern = RIGHT_IND_ON();
        clcd_print("RIG  ", LINE2(5));
    }
    else if(strcmp(ind_str, "HAZ") == 0)
    {
        pattern = HAZARD_IND_ON();
        clcd_print("HAZ ", LINE2(5));
    }
    else if(strcmp(ind_str, "OFF") == 0)
    {
        pattern = IND_OFF();
        clcd_print("OFF    ", LINE2(5));
    }

    
     // Non-blocking delay
        if(delay++ >= blink_time)
        {
            delay = 0;
            led_state = !led_state;

            if(led_state)
                PORTB = pattern;
            else
                PORTB = 0x00;
        }
}

void process_canbus_data() 
{   
    //process the CAN bus data
    uint16_t msg_id;                           
    uint8_t data[10];                          
    uint8_t len;                               

    can_receive(&msg_id, data, &len);          
    for(int wait = 3000; wait--;);
    // Handle message based on message ID
    switch (msg_id)
    {
        case SPEED_MSG_ID: 
            handle_speed_data(data, len);      
            break;

        case GEAR_MSG_ID:   
            handle_gear_data(data, len);       
            break;

        case RPM_MSG_ID:   
            handle_rpm_data(data, len);        
            break;

        case INDICATOR_MSG_ID:    
            handle_indicator_data(data, len);  
            break;
    }
}
