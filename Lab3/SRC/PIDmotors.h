/*
 * PIDmotors.h
 *
 *  Created on: Feb 5, 2017
 *      Author: nbeeten
 */

#ifndef SRC_PIDMOTORS_H_
#define SRC_PIDMOTORS_H_

void driveLinkPID(int link, int pwr);
void driveLinkPIDDir(int link, int pwr);
void stopSelect(int link);
void homeArm();

#endif /* SRC_PIDMOTORS_H_ */


