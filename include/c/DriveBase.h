/**
* @file     DriveBase.h
* @author   Adam Morrissett
* @version  v1.0
* @date     5 Dec. 2016
* @brief    This file contains the drive base structure and corresponding
*           functions to control it. This is the structure that is 
*           responsible for making the robot drive.
*/

#ifndef DRIVE_BASE_H
#define DRIVE_BASE_H

#include "stm32l476xx.h"

#include "Gpio.h"
#include "StepperMotor.h"

/**
 * The structure for the drive base.
 * This structure contains the stepper motors that will be controlled in order
 * to drive the robot. 
 */
typedef struct {
  stepperMotor_t* leftMotor;   // The front right motor on the robot
  stepperMotor_t* rightMotor;  // The front left motor on the robot
  TIM_TypeDef syncTimer;      // Timer to synchronize movement of motors
} driveBase_t;


/**
 * Initializes all of the members of the driveBase_t structure.
 *
 * @param _driveBase pointer to tthe drive base to initialize
 */
void initDriveBase(driveBase_t* _driveBase);

#endif