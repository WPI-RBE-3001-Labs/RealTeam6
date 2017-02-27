/*
 * USART.h
 *
 *  Created on: Jan 23, 2017
 *      Author: nbeeten
 */
#define F_CLOCK 18432000

#include "main.h"
#include "avr/io.h"

/**
 * @brief Initializes USART1 as a print terminal to the PC. This function
 * must check the incoming baudrate against the valid baudrates
 * from the data-sheet. If the baudrate is invalid, then the
 * DEFAULT_BAUD constant must be used instead.
 *
 * @param baudrate The desired baudrate to set for USART1.
 *
 * @todo Create the function that will initialize USART1 for debugging use.
 */
void debugUSARTInit(unsigned long baudrate){

	//ensure that was handed a valid baud rate, otherwise set baud rate to be default
	const long validBauds[14] = {110, 150, 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};
	unsigned long baud = DEFAULT_BAUD;
	for(int i = 0; i < 13; i++) {
		if(baudrate == validBauds[i]) {
			baud = baudrate;
			break;
		}
	}


	//set the baudrate
	UBRR1H = (unsigned char)((F_CLOCK / (16 * baudrate) - 1) >> 8);
	UBRR1L = (unsigned char)(F_CLOCK / (16 * baudrate) - 1);

	UCSR1B = 0b00011000;
	/* Set frame format: 8data, 1stop bit */
	UCSR1C = 0b00000110;
}

/**
 * @brief Sends one byte to the USART1 Tx pin (Transmits one byte).
 *
 * @param byteToSend The byte that is to be transmitted through USART1.
 *
 * @todo Make the function that will put a character on the USART1 TX line.
 */
void putCharDebug(char byteToSend){
	/* Wait for empty transmit buffer */
	while ( !( UCSR1A & (1 << UDRE1)));
	/* Put data into buffer, sends the data */
	UDR1 = byteToSend;
}

/**
 * @brief Recieves one byte of data from the serial port (i.e. from the PC).
 *
 * @return byteReceived Character that was received on the USART.
 *
 * @todo Make the function that will listen for input on the USART1 RX line.
 */
unsigned char getCharDebug(void){
	/* Wait for empty transmit buffer */
	/* Wait for data to be received */
	while ( !(UCSR1A & (1<<RXC1)) );
	/* Get and return received data from buffer */
	return UDR1;

}


//just to see whats wrong
