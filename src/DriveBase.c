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

void initDriveBase(driveBase_t* _driveBase) {  
  initStepperMotor(&(_driveBase->leftMotor), GPIOC, GPIOB, 5, 1);
  initStepperMotor(&(_driveBase->rightMotor), GPIOB, GPIOB, 13, 15);
  
  driveBase = _driveBase; // Store the address of the passed in driveBase_t
  
  initSyncTimer(_driveBase);
}

static void initSyncTimer(driveBase_t* _driveBase) {
  // Init the timer
  RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN; // Enable timer clock
  _driveBase->syncTimer = TIM4; // Set thw syncTimer to general timer 4
  _driveBase->syncTimer->PSC = 400 - 1; // Want to run the counter at 2 kHz
  _driveBase->syncTimer->ARR = 1000 - 1;  // Overrun event will trigger 1 kHz   
  _driveBase->syncTimer->DIER |= TIM_DIER_UIE;  // Enable the update interrupt
  
  // Enable interrupts for TIM4 and set its priority
  NVIC_SetPriority(TIM4_IRQn, 4);
  NVIC_EnableIRQ(TIM4_IRQn);
    
  // Enable the syncTimer
  _driveBase->syncTimer->CR1 = TIM_CR1_CEN;
}

/**
 * Event handler for TIM4 (syncTimer).
 * This function is called whenever there is an event on TIM4. The type of 
 * even determines the action of the handler.
 */
void TIM4_IRQHandler(void) {
  if((TIM4->SR & TIM_SR_UIF) != 0) {
    motorUpdate();
  }
}

static void motorUpdate(void) {
  
	uint8_t right_move = 1;
	uint8_t left_move = 1;
	uint8_t right_dir = 1;
	uint8_t left_dir = 1;
	
	if (left_move) {
		set(&(driveBase->leftMotor), left_dir, 1);
	}
	if (right_move) {
		set(&(driveBase->rightMotor), right_dir, 1);
	}
	
	for(int i=0; i<200; i++);

	if (left_move) {
		set(&(driveBase->leftMotor), left_dir, 0);
	}
	if (right_move) {
		set(&(driveBase->rightMotor), right_dir, 0);
	}
}
