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
  
  initSyncTimer(_driveBase);
}

static void initSyncTimer(driveBase_t* _driveBase) {
  // Init the timer
  RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN; // Enable timer clock
  _driveBase->syncTimer = TIM4; // Set thw syncTimer to general timer 4
  _driveBase->syncTimer->PSC = 400 - 1; // Want to run the counter at 2 kHz
  _driveBase->syncTimer->ARR = 1000 - 1;  // Overrun event will trigger 1 kHz   
  
  // Enable interrupts for TIM4 and set its priority
  NVIC->ISER[0] = 1 << TIM4_IRQn;
  NVIC->IP[TIM4_IRQn] = 0xFF;  // lower number means higher priority
  
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
    
  }
}

void motorUpdate(void) {
  
	uint8_t right_move;
	uint8_t left_move;
	uint8_t right_dir;
	uint8_t left_dir;
	
	if (left_move) {
		set(&(_driveBase->leftMotor), left_dir, 1);
	}
	if (right_move) {
		set(&(_driveBase->rightMotor), right_dir, 1);
	}
	
	for(int i=0; i<200; i++);

	if (left_move) {
		set(&(_driveBase->leftMotor), left_dir, 0);
	}
	if (right_move) {
		set(&(_driveBase->rightMotor), right_dir, 0);
	}
}
