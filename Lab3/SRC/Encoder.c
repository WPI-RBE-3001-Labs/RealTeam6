/*
 * Encoder.c
 *
 *  Created on: Feb 13, 2017
 *      Author: jltai
 */

#include "main.h"
#include "RBELib/RBELib.h"

void initEncoders(){
	DDRC &= 0b00000000;
}

int EncoderCounts( int __chan ){
	int encValue = 0;
	if(__chan == 0){
		encValue = PINCbits._P5;
		return encValue;
	} else if(__chan == 1){
		encValue = PINCbits._P4;
		return encValue;
	} else {
		return -1;
	}

}
