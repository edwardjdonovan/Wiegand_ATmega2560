/**
 * \file
 *
 * \brief ATmega2560 Wiegand To USB 
 *
 */

/**
 * \mainpage
 * \section board Arduino ATmega2560 
 * \section intro Introduction
 * This application firmware receives Wiegand Data from a Wiegand reader and outputs 
 * the raw binary data through UART to a serial terminal emulator
 *
 * \section files Files:
 * - main.c: Integrated Wiegand Product Test Fixture main application source c file
 *
 * \section description Brief description of the main application
 * This application will initialize the UART, initialize Wiegand, recieve Wiegand
 * data, then send a string of the raw Wiegand binary data through UART
 *
 * \note The readers Data 0 should be connected to PE4 (INT4) and Data 1 should be 
 * connected to PE5 (INT5) of the ATmega2560 MCU
 *
 * \section compinfo Compilation Info
 * This software was written for the <A href="http://gcc.gnu.org/">GNU GCC</A>
 * for AVR. \n
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, contact
 * <A href="ejoseph.donovan@gmail.com">Ed Donovan </A>.\n
 * For further information, visit
 * <A href="http://www.atmel.com/">Atmel</A>.\n
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

 // _ASSERT_ENABLE_ is used for enabling assert, typical for debug purposes
#define _ASSERT_ENABLE_
#include <string.h>
#include "compiler.h"

#include "asf.h"

// set the correct BAUD and F_CPU defines before including setbaud.h
#include "conf_clock.h" 
#include "conf_uart.h" 
#include "conf_wiegand.h" 

/**
 * \name avr_libc_inc avr libc include files
 * @{
 */
#include <util/setbaud.h>
#include <avr/interrupt.h>
//! @}

#include "ring_buffer.h"
#include "uart.h"
#include "wiegand.h"

/**
 * \brief The main application
 *
 * This application will initialize the UART, initialize the Wiegand, send a character over UART,
 * recieve a character over UART, recieve Wiegand Data 0 and 1 and ouput the data to UART.
 *
 */
int main(void)
{
	cli();
	uart_init();
	wiegand_init();
	sei();
	while(true){	
		wiegand_credential();	//procudure that waits for wiegand data then outputs the wiegand data via UART
	}
}
	
