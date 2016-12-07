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
  initStepperMotor(&(_driveBase->leftMotor), GPIOC, GPIOB, 5, 1);
  initStepperMotor(&(_driveBase->rightMotor), GPIOB, GPIOB, 13, 15);
  
  initSyncTimer(_driveBase);
}

static void initSyncTimer(driveBase_t* _driveBase) {
  // Init the timer
  RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN; // Enable timer clock
  _driveBase->syncTimer = TIM4; // Set thw syncTimer to general timer 4
  _driveBase->syncTimer->PSC = 0xDEADBEEF;
  _driveBase->syncTimer->ARR = 0xDEADBEEF;
  _driveBase->syncTimer->CCR1 = 0xDEADBEEF;
  _driveBase->syncTimer->ARR = 0xDEADBEEF;
  _driveBase->syncTimer->ARR = 0xDEADBEEF;
  
  // Enable the syncTimer
  _driveBase->syncTimer->CR1 = TIM_CR1_CEN;
}
