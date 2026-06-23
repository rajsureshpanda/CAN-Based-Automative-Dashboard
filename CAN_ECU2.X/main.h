/* 
 * File:   main.h
 * Author: Raj
 *
 * Created on 2 April, 2026, 3:05 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#define _XTAL_FREQ                  20000000

//adc
#define CHANNEL0		0x00
#define CHANNEL1		0x01
#define CHANNEL2		0x02
#define CHANNEL3		0x03
#define CHANNEL4		0x04
#define CHANNEL5		0x05
#define CHANNEL6		0x06
#define CHANNEL7		0x07
#define CHANNEL8		0x08
#define CHANNEL9		0x09
#define CHANNEL10		0x0A

void init_adc(void);
unsigned short read_adc(unsigned char channel);


//can
#include <stdint.h>

/* Defines ECAN */
#define   F_ECAN_MODE2_FP		CANCON & 0x0F
#define   F_ECANFIFO_0			RXB0CONbits.RXFUL
#define   F_ECANFIFO_1			RXB1CONbits.RXFUL
#define   F_ECANFIFO_2			B0CONbits.RXFUL
#define   F_ECANFIFO_3			B1CONbits.RXFUL
#define   F_ECANFIFO_4			B2CONbits.RXFUL
#define   F_ECANFIFO_5			B3CONbits.RXFUL
#define   F_ECANFIFO_6			B4CONbits.RXFUL
#define   F_ECANFIFO_7			B5CONbits.RXFUL

#define CAN_SET_OPERATION_MODE_NO_WAIT(mode)		\
{													\
	CANCON &= 0x1F;									\
	CANCON |= mode;									\
}

#define EIDH					0
#define EIDL					1
#define SIDH					2
#define SIDL					3
#define DLC						4
#define D0						5
#define D1						6
#define D2						7
#define D3						8
#define D4						9
#define D5						10
#define D6						11
#define D7						12

/* Function Prototypes  */
void init_can(void);
void can_transmit(uint16_t msg_id, const uint8_t *data, uint8_t len);
void can_receive(uint16_t *msg_id, uint8_t *data, uint8_t *len);

//dkp
#define LEVEL					     	0
#define EDGE			       	1

#define KEY_PORT					PORTC

#define SWITCH1					0x0E
#define SWITCH2					0x0D
#define SWITCH3					0x0B
#define SWITCH4					0x07
#define ALL_RELEASED					0x0F

#define INPUT_PINS					0x0F

void init_digital_keypad(void);
unsigned char read_digital_keypad(unsigned char detection_type);


//ecu2_sensor
#include <stdint.h>

#define MAX_GEAR 6
#define SPEED_ADC_CHANNEL 0x04
#define GEAR_UP             SWITCH1
#define GEAR_DOWN           SWITCH2
#define COLLISION           SWITCH3

uint16_t get_speed();
unsigned char get_gear_pos();

//msg_id
#define SPEED_MSG_ID 0x10
#define GEAR_MSG_ID 0x20
#define RPM_MSG_ID 0x30
// #define ENG_TEMP_MSG_ID 0x40
#define INDICATOR_MSG_ID 0x50

//uart
#define RX_PIN					TRISC7
#define TX_PIN					TRISC6

void init_uart(void);
void putch(unsigned char byte);
int puts(const char *s);
unsigned char getch(void);
unsigned char getch_with_timeout(unsigned short max_time);
unsigned char getche(void);

#endif	/* MAIN_H */

