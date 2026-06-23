/*
 * File:   main.c
 * Author: Raj
 *
 * Created on 1 April, 2026, 11:43 AM
 */


#include <xc.h>
#include<string.h>
#include"main.h"

void init_config()
{
    init_digital_keypad();
    init_adc();
    init_can();
}

//converting integer to string 
void int_to_str(unsigned int num, char *str)
{
    str[0] = (num / 1000) % 10 + '0';
    str[1] = (num / 100) % 10 + '0';
    str[2] = (num / 10) % 10 + '0';
    str[3] = (num % 10) + '0';
    str[4] = '\0';
}

void main(void) {
    
    init_config();
    
    unsigned char rpm_str[5];
    unsigned int val;
    
    while(1)
    {
        //read rpm
        val = get_rpm(CHANNEL4);
        
        int_to_str(val, rpm_str);
        
        //can transmit(rpm data)
        can_transmit(RPM_MSG_ID,rpm_str,4);
        for(int wait =3000; wait--;);
        
        //read indicator
        uint8_t status = process_indicator();
        
        char indicator_str[10];
        
        //converting into string
        switch(status)
        {
            case e_ind_off:
                strcpy(indicator_str, "OFF");
                break;
            case e_ind_left:
                strcpy(indicator_str, "LEF");
                break;
            case e_ind_right:
                strcpy(indicator_str, "RIG");
                break;
            case e_ind_hazard:
                strcpy(indicator_str, "HAZ");
                break;
        }
        
        //can transmit(indicator data)
        can_transmit(INDICATOR_MSG_ID, indicator_str, strlen(indicator_str));
        for(int wait = 3000; wait--;);
   
    }
    
    return;
}