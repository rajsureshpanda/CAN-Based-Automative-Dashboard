/*
 * File:   main.c
 * Author: Raj
 *
 * Created on 2 April, 2026, 3:03 PM
 */


#include <xc.h>
#include<string.h>
#include"main.h"

void init_config()
{
    init_adc();
    init_can();
    init_digital_keypad();
    init_uart();
}

void int_to_str(unsigned int num, char *str);

void main(void) {
    
    init_config();
    
    unsigned int speed;
    uint8_t tx_speed_str[6];
    uint8_t len1;
    uint8_t rx_speed_str[6];
    uint16_t speed_msg_id;
    
    
    unsigned int gear_value;
    
    uint16_t gare_msg_id;
    uint8_t rx_gear_value;
    uint8_t len2;
    
    char *gear[] = {"N","1","2","3","4","5","R"};

    while(1)
    {
        speed = get_speed();
        
        
        gear_value = get_gear_pos();

        // If gear is neutral speed = 0
        if(gear_value == 0)
        {
            speed = 0;
        }

        // Convert to string
        int_to_str(speed, tx_speed_str);

        //can transmit(speed data)
        can_transmit(SPEED_MSG_ID,tx_speed_str,strlen(tx_speed_str));
        for(int wait = 3000; wait--;);
                
        //can transmit(gear data)
        can_transmit(GEAR_MSG_ID,&gear_value,1);
        for(int wait = 3000; wait--;);
        
    }
    
    
    return;
}

void int_to_str(unsigned int num, char *str)
{
    str[0] = (num / 100) % 10 + '0';
    str[1] = (num / 10) % 10 + '0';
    str[2] = (num % 10) + '0';
    str[3] = '\0';
}