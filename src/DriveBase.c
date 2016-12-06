/**
* @file     DriveBase.c
* @author   Adam Morrissett
* @version  v1.0
* @date     5 Dec. 2016
* @brief    This file contains the drive base structure and corresponding
*           functions to control it. This is the structure that is 
*           responsible for making the robot drive.
*/

#include "DriveBase.h"

void initDriveBase(driveBase_t* _driveBase) {  
  initStepperMotor(&(_driveBase->leftMotor), GPIOB, GPIOB, 1, 2);
  initStepperMotor(&(_driveBase->rightMotor), GPIOB, GPIOB, 3, 4);
  
  // NEED TO SETUP THE TIMER
}
