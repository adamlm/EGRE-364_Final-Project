/**
* @file     StepperMotor.h
* @author   Adam Morrissett
* @version  v1.0
* @date     26 Nov. 2016
* @brief    This file contains the stepper motor structure. This file also 
*           contains the functions to control the stepper motor structure.
*/

#include "StepperMotor.h"

/**
 * Intiailze all the members of the stepperMotor_t structure
 *
 * @param _stepperMotor pointer to the stepper motor to initialize
 * @param _port GPIO port that the pins belong to
 * @param _stepPin the pin used for the step input on the motor controller
 * @param _directionPin the pin used for the direction input on the motor
 *        controller
 */
void initStepperMotor(stepperMotor_t* _stepperMotor, GPIO_TypeDef * _port, 
  uint8_t _stepPin, uint8_t _directionPin) {
  initGpio(&(_stepperMotor->directionPin), _port, _directionPin);
  initGpio(&(_stepperMotor->stepPin), _port, _stepPin);
    
  setMode(_stepperMotor->directionPin.port, _stepperMotor->directionPin.pin,
    OUTPUT);
  setOType(_stepperMotor->directionPin.port, _stepperMotor->directionPin.pin,
    PUSH_PULL);
  setOSpeed(_stepperMotor->directionPin.port, _stepperMotor->directionPin.pin,
    VERY_HIGH_SPEED);
}
  
/**
 * Set the output of the stepper motor.
 * Controls whether or not the motor will rotate.
 *
 * @param _stepperMotor the stepper motor to be driven or not
 * @param _step whether or not the moter should step (0 = false, 1 = true)
 * @param _direction the direction of the step (0 = , 1 = )
 */
void set(stepperMotor_t* _stepperMotor, uint8_t _step, uint8_t _direction) {
  writePin(_stepperMotor->directionPin.port, _stepperMotor->directionPin.pin, 
    _direction);
  writePin(_stepperMotor->stepPin.port, _stepperMotor->stepPin.pin, _step);
}
