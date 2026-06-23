/* 
 * File:   main.h
 * Author: Raj
 *
 * Created on 3 April, 2026, 3:46 PM
 */

#ifndef MAIN_H
#define	MAIN_H

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


//clcd
#define CLCD_PORT			PORTD
#define CLCD_EN				RC2
#define CLCD_RS				RC1
#define CLCD_RW				RC0
#define CLCD_BUSY			RD7
#define PORT_DIR			TRISD7

#define HI												1
#define LO												0

#define INPUT											0xFF
#define OUTPUT											0x00

#define DATA_COMMAND									1
#define INSTRUCTION_COMMAND								0

#define LINE1(x)									(0x80 + (x))
#define LINE2(x)										(0xC0 + (x))

#define TWO_LINE_5x8_MATRIX_8_BIT					clcd_write(0x38, INSTRUCTION_COMMAND)
#define CLEAR_DISP_SCREEN				                clcd_write(0x01, INSTRUCTION_COMMAND)
#define CURSOR_HOME							clcd_write(0x02, INSTRUCTION_COMMAND)
#define DISP_ON_AND_CURSOR_OFF						clcd_write(0x0C, INSTRUCTION_COMMAND)

void init_clcd(void);
void clcd_print(const unsigned char *data, unsigned char addr);
void clcd_putch(const unsigned char data, unsigned char addr);
void clcd_write(unsigned char bit_values, unsigned char control_bit);


//message_handler
//#include <stdint.h>

#define LED_OFF 0
#define LED_ON 1

//#define RIGHT_IND_ON() (PORTB = PORTB | 0xC0)
//#define RIGHT_IND_OFF() (PORTB = PORTB & ~0xC0)
//#define LEFT_IND_ON() (PORTB = PORTB | 0x03)
//#define LEFT_IND_OFF() (PORTB = PORTB & ~0x03)
//#define HAZARD_IND_ON() (PORTB = 0xC3);
//#define IND_OFF() (PORTB = 0x00);

#define LEFT_IND_ON()     0x01   // RB0 ON
#define RIGHT_IND_ON()    0x80   // RB7 ON
#define HAZARD_IND_ON()   0x81   // RB0 + RB7 ON
#define IND_OFF()         0x00

extern volatile unsigned char led_state, status;

typedef enum {
    e_ind_off,
    e_ind_left,
    e_ind_right,
    e_ind_hazard
} IndicatorStatus;

void process_canbus_data();
void handle_speed_data(uint8_t *data, uint8_t len);
void handle_gear_data(uint8_t *data, uint8_t len);
void handle_rpm_data(uint8_t *data, uint8_t len);
void handle_engine_temp_data(uint8_t *data, uint8_t len);
void handle_indicator_data(uint8_t *data, uint8_t len);

//msg_id
#define SPEED_MSG_ID 0x10
#define GEAR_MSG_ID 0x20
#define RPM_MSG_ID 0x30
#define ENG_TEMP_MSG_ID 0x40
#define INDICATOR_MSG_ID 0x50

//timer0
void init_timer0(void);


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

