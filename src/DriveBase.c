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

/**
 * Initializes all of the members of the driveBase_t structure.
 *
 * @param _driveBase pionter to the drive base to initialize
 */
void initDriveBase(driveBase_t* _driveBase) {
  GPIOB->MODER &= ~(0xffff);
  initStepperMotor(&(_driveBase->leftMotor), GPIOB, 1, 2);
  initStepperMotor(&(_driveBase->rightMotor), GPIOB, 3, 4);
  
  // NEED TO SETUP THE TIMER
}
