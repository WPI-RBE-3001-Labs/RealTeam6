/*
 * Encoder.h
 *
 *  Created on: Feb 13, 2017
 *      Author: jltai
 */

#ifndef ENCODER_H_
#define ENCODER_H_


#define HIGH_ENCODER_SS 4 //PORT C
#define LOW_ENCODER_SS 5 //PORT C


#define NON_QUADRATURE_COUNT 0X00
#define ONE_QUADRATURE_COUNT 0X01
#define TWO_QUADRATURE_COUNT 0X02
#define FOUR_QUADRATURE_COUNT 0X03

#define FREE_RUNNING 0X00
#define SINGLE_CYCLE_COUNT 0X04
#define RANGE_LIMIT_COUNT 0X08
#define MODULO_N_COUNT 0X0C

#define DISABLE_INDEX 0X00
#define INDEX_LOAD_CNTR 0x10
#define INDEX_RESET_CNTR 0X20
#define INDEX_LOAD_OTR 0X30

#define ASYNCHRONOUS_INDEX 0X00
#define SYNCHRONUS_INDEX 0X80

#define CLK_DIV_FACTOR1 0X00
#define CLK_DIV_FACTOR2 0X80

//MDR1

#define CNTR4_BYTE 0X00
#define CNTR3_BYTE 0X01
#define CNTR2_BYTE 0X02
#define CNTR1_BYTE 0X03

#define DISABLE_CNT 0X04
#define ENABLE_CNT 0X00

#define NO_FLAGS 0X00
#define IDX_FLAG 0x10
#define CMP_FLAG 0x20
#define BW_FLAG 0x40
#define CY_FLAG 0x80


//setting the IR
#define CLR_MDR0 0x08
#define CLR_MDR1 0x10
#define CLR_CNTR 0x20
#define CLR_STR 0x30
#define READ_MDR0 0x48
#define READ_MDR1 0x50

#define READ_CNTR   0x60
#define READ_OTR    0x68
#define READ_STR    0x70
#define WRITE_MDR1 0x90
#define WRITE_MDR0 0x88
#define WRITE_DTR   0x98
#define LOAD_CNTR   0xE0
#define LOAD_OTR    0xE4

#define Slave_Select_Low PORTB &= ~(1 << PB4)
#define Slave_Select_High PORTB |= (1 << PB4)


void initEncoder(char pos);
void initEncoders();
int EncoderCounts( char __chan );



#endif /* ENCODER_H_ */
