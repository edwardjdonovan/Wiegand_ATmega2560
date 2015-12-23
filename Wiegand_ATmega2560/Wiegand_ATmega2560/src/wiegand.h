/*
 * wiegand.h
 *
 * Created: 11/10/2015 7:02:37 PM
 *  Author: EdwDon
 */ 


#ifndef WIEGAND_H_
#define WIEGAND_H_

 // _ASSERT_ENABLE_ is used for enabling assert, typical for debug purposes
 #define _ASSERT_ENABLE_
 #include <string.h>
 #include "compiler.h"


/**
 * \def WIEGAND_BUFFER_SIZE
 * \brief The size of the WIEGAND buffer
 */
#define WIEGAND_BUFFER_SIZE 255

/**
 * \name avr_libc_inc avr libc include files
 * @{
 */
#include <avr/interrupt.h>
//! @}

#include "ring_buffer.h"
#include "uart.h"

#include "conf_wiegand.h"

// buffers for use with the ring buffer (belong to the WIEGAND )
uint8_t wiegand_buffer[WIEGAND_BUFFER_SIZE];

//! ring buffer to use for Wiegand reception
struct ring_buffer ring_buffer_wiegand;

uint8_t wdata[200];
int n_bits = 0;

ISR(INT4_vect)
{
	uint8_t i = 0;
	const char wiegand_0[] = "0";
	for (i = 0; i < strlen(wiegand_0); i++) {
		ring_buffer_put(&ring_buffer_wiegand, wiegand_0[i]);
	}

}

ISR(INT5_vect)
{
	uint8_t i = 0;
	const char wiegand_1[] = "1";
	for (i = 0; i < strlen(wiegand_1); i++) {
		ring_buffer_put(&ring_buffer_wiegand, wiegand_1[i]);
	}

}

static void wiegand_init(void){
	
	
	//enable Digital pins 2 and 3 as interrupts
	EIMSK = (1<<INT4) | (1<<INT5);

	//set INT4 and INT5 as interrupts on the falling edge
	EICRB = (1<<ISC41) | (1<<ISC51);

	//initialize Wiegand Data Handling
	ring_buffer_wiegand = ring_buffer_init(wiegand_buffer, WIEGAND_BUFFER_SIZE);
}

static inline void wiegand_putchar(uint8_t data)
{
	// Disable interrupts to get exclusive access to ring_buffer_out.
	cli();
	ring_buffer_put(&ring_buffer_wiegand, data);
	sei();
}


static inline uint8_t wiegand_getchar(void)
{
	return ring_buffer_get(&ring_buffer_wiegand);
}

static inline bool wiegand_char_waiting(void)
{
	return !ring_buffer_is_empty(&ring_buffer_wiegand);
}

static inline void wiegand_credential(void)
{
	uint8_t data;
	while(!wiegand_char_waiting());
	data = wiegand_getchar();
	uart_putchar(data);
	uart_putchar('\r');		//new line after credential is read
}

#endif /* WIEGAND_H_ */