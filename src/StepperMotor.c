/**
* @file     StepperMotor.h
* @author   Adam Morrissett
* @version  v1.0
* @date     26 Nov. 2016
* @brief    This file contains the stepper motor structure. This file also 
*           contains the functions to control the stepper motor structure.
*/

#include "StepperMotor.h"

void initStepperMotor(stepperMotor_t* _stepperMotor, GPIO_TypeDef * _stepPort,
  GPIO_TypeDef* _directionPort, uint8_t _stepPin, uint8_t _directionPin) {
  initGpio(&(_stepperMotor->directionPin), _directionPort, _directionPin);
  initGpio(&(_stepperMotor->stepPin), _stepPort, _stepPin);
    
  setMode(_stepperMotor->directionPin.port, _stepperMotor->directionPin.pin,
    OUTPUT);
  setOType(_stepperMotor->directionPin.port, _stepperMotor->directionPin.pin,
    PUSH_PULL);
  setOSpeed(_stepperMotor->directionPin.port, _stepperMotor->directionPin.pin,
    VERY_HIGH_SPEED);
    
  setMode(_stepperMotor->stepPin.port, _stepperMotor->stepPin.pin,
    OUTPUT);
  setOType(_stepperMotor->stepPin.port, _stepperMotor->stepPin.pin,
    PUSH_PULL);
  setOSpeed(_stepperMotor->stepPin.port, _stepperMotor->stepPin.pin,
    VERY_HIGH_SPEED);
}

void set(stepperMotor_t* _stepperMotor, uint8_t _step, uint8_t _direction) {
  writePin(_stepperMotor->directionPin.port, _stepperMotor->directionPin.pin, 
    _direction);
  writePin(_stepperMotor->stepPin.port, _stepperMotor->stepPin.pin, _step);
}
