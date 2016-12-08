/**
* @file     DriveBase.h
* @author   Adam Morrissett
* @version  v1.0
* @date     5 Dec. 2016
* @brief    This file contains the drive base structure and corresponding
*           functions to control it. This is the structure that is 
*           responsible for making the robot drive.
* @TODO:    Implement a way to disable the back two steppers so there is
*           less power consumption
*/

#ifndef DRIVE_BASE_H
#define DRIVE_BASE_H

#include "stm32l476xx.h"

#include "Gpio.h"
#include "StepperMotor.h"

/**
 * This is the enumeration for the driveBase states. These states control
 * the direction of movement of the robot.
 */
typedef enum {
  FORWARD = 0,  // The robot is moving forward
  REVERSE = 1,  // The robot is moving backward
  LEFT_TURN = 2,  // The robot is turning left
  RIGHT_TURN = 3, // The robot is turning right
  STOP = 4  // The robot is stopped  
} driveBaseState;

/**
 * The structure for the drive base.
 * This structure contains the stepper motors that will be controlled in order
 * to drive the robot. 
 */
typedef struct {
  stepperMotor_t leftMotor;   // The front right motor on the robot
  stepperMotor_t rightMotor;  // The front left motor on the robot
  TIM_TypeDef* syncTimer;      // Timer to synchronize movement of motors
} driveBase_t;

/**
 * Initializes all of the members of the driveBase_t structure.
 *
 * @param _driveBase pointer to tthe drive base to initialize
 * @param _state pointer to the state of the drive base
 */
void initDriveBase(driveBase_t* _driveBase, driveBaseState* _state);

/**
 * Initializes the motor sync timer.
 * The timer used for the drive base is hard coded, so any changes would
 * have to be made here.
 *
 * @param _driveBase the drive base of the desired syncTimer
 */
static void initSyncTimer(driveBase_t* _driveBase);

/**
 * Event handler for TIM4 (syncTimer).
 * This function is called whenever there is an event on TIM4. The type of 
 * even determines the action of the handler.
 */
void TIM4_IRQHandler(void);

/**
 * Updates the output of the motor.
 * This function basically determines if the motors need to step.
 */
void motorUpdate(void);

/** 
 * Sets the state of the drive base to determine the direction of motor
 * rotation.
 *
 * @param _state the desired state of the driveBase
 */
void setState(driveBaseState* _state);

#endif
