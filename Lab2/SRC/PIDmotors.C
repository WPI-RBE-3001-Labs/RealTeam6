/*
 * PIDmotors.C
 *
 *  Created on: Feb 5, 2017
 *      Author: nbeeten
 */

#include "main.h"

void stopSelect(int link){

	switch (link){
	case 0: //lower link
			setDAC(0, 0);
			setDAC(1, 0);
	break;

	case 1: //high link
			setDAC(2, 0);
			setDAC(3, 0);

	break;
	}

}

void driveLinkPID(int link, int dir, int pwr){
	switch (link){
	case 0: //lower link
		if(dir){
			setDAC(0, pwr);
			setDAC(1, 0);
		} else {
			setDAC(0, 0);
			setDAC(1, pwr);
		}
	break;
	case 1: //high link
		if(dir){
			setDAC(2, pwr);
			setDAC(3, 0);
		} else {
			setDAC(2, 0);
			setDAC(3, pwr);
		}
	break;
	}

}
