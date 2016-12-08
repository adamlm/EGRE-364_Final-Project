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
#include "stdint.h"
#include "math.h"

static driveBase_t* driveBase;  // Pointer to actual driveBase in Main.c

static volatile int right_speed; // Speed of the right motor (arbitrary unit)
static volatile int left_speed;  // Speed of the left motor (arbitrary unit)

void initDriveBase(driveBase_t* _driveBase) {  
  driveBase = _driveBase;
  
  right_speed = 0;
  left_speed = 0;
  
  // Initialize both of the stepper motors
  initStepperMotor(&(_driveBase->leftMotor), GPIOC, GPIOB, 5, 1);
  initStepperMotor(&(_driveBase->rightMotor), GPIOB, GPIOB, 13, 15);
  
  // Initialize the motor synchornization timer
  initSyncTimer(_driveBase);
}

static void initSyncTimer(driveBase_t* _driveBase) {
  // Init the timer
  RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN; // Enable timer clock
  _driveBase->syncTimer = TIM4; // Set thw syncTimer to general timer 4
  _driveBase->syncTimer->PSC = 800 - 1; // Want to run the counter at 2 kHz
  _driveBase->syncTimer->ARR = 1000 - 1;  // Overrun event will trigger 1 kHz   
  
  // Enable interrupt for TIM4 and set its priority
  NVIC_EnableIRQ(TIM4_IRQn);
  NVIC_SetPriority(TIM4_IRQn,1);
  _driveBase->syncTimer->DIER |= TIM_DIER_UIE;  // Enable the update event
  
  // Enable the syncTimer
  _driveBase->syncTimer->CR1 = TIM_CR1_CEN;
}

void TIM4_IRQHandler(void) {
  if((TIM4->SR & TIM_SR_UIF) != 0) {
    TIM4->SR &= 1;  // Clear the update interrupt flag
    motorUpdate();  // Update the motor outputs
  }
}

static void motorUpdate(void) {
  
	uint8_t right_move = 0; // Whether or not the right motor should step
	uint8_t left_move = 0;  // Whether or not the left motor should step

  uint8_t leftDirection = 0;
  uint8_t rightDirection = 1;
  
	int i;  // Iterator for for-loop delay
	
  // The way the motor control works is by keeping track of how many ticks the
  // motor has gone through without stepping. The motors move once every X
  // ticks, and the tick threshold determines the speed of the motors.  
	static uint8_t right_count; // The number of right motor ticks
	static uint8_t left_count;  // The number of left motor ticks
  
  if (right_speed < 0) rightDirection = 0;
	if (left_speed < 0) leftDirection = 1;
  
  if (right_speed != 0 && right_count > 1000/abs(right_speed)) {
		right_count = 0;
		right_move = 1;
	} else right_count++;

	if (left_speed != 0 && left_count > 1000/abs(left_speed)) {
		left_count = 0;
		left_move = 1;
	} else left_count++;
         
	if (left_move) {
		set(&(driveBase->leftMotor),1, leftDirection);
	}
	if (right_move) {
		set(&(driveBase->rightMotor),1, rightDirection);
	}
	
	if (left_move || right_move) for(i=0; i<10; i++);

	if (left_move) {
		set(&(driveBase->leftMotor),0, leftDirection);
	}
	if (right_move) {
		set(&(driveBase->rightMotor),0, rightDirection);
	}
}

void setLeftMotorSpeed(uint8_t _speed) {
  left_speed = _speed;
}

void setRightMotorSpeed(uint8_t _speed) {
  right_speed = _speed;
}
