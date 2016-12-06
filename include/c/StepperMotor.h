/**
* @file     StepperMotor.h
* @author   Adam Morrissett
* @version  v1.0
* @date     26 Nov. 2016
* @brief    This file contains the stepper motor structure. This file also 
*           contains the functions to control the stepper motor structure.
*/

#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include "stm32l476xx.h"
#include "Gpio.h"

/**
* Stepper motor structure.
*
* This structure contains the 4 pins (wires) used to 
* connect to the physical stepper motor
*/
typedef struct {
    gpio_t* stepPin;  // Pin used to denote if the motor should step
    gpio_t* directionPin;  // Pin used to denote the direction of the step
} stepperMotor_t;

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
  uint8_t _stepPin, uint8_t _directionPin);

/**
 * Set the output of the stepper motor.
 * Controls whether or not the motor will rotate.
 *
 * @param _stepperMotor the stepper motor to be driven or not
 * @param _step whether or not the moter should step (0 = false, 1 = true)
 * @param _direction the direction of the step (0 = , 1 = )
 */
void set(stepperMotor_t* _stepperMotor, uint8_t _step, uint8_t _direction);

#endif
