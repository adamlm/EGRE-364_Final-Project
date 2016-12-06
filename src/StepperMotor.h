/**
* @file            StepperMotor.h
* @author       Adam Morrissett
* @version      v1.0
* @date          26 Nov. 2016
* @brief          This file is used to control a single stepper
*                    motor.
*/

#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include "stm32l476xx.h"

/**
* TODO: Abstract the stepper motor enough so a speed 
* and direction value can be passed into a function
*/

/**
* Stepper motor structure.
*
* This structure contains the 4 pins (wires) used to 
* connect to the physical stepper motor
*/
typedef struct {
    uint8_t port1;  // Wire 1 on the stepper motor
    uint8_t port2;  // Wire 2 on the stepper motor
    uint8_t port3;  // Wire 3 on the stepper motor
    uint8_t port3;  // Wire 4 on the stepper motor
} stepperMotor_t;


/**
* Set the speed of the stepper motor.
*
* @param _speed desired speed of the stepper motor
*/
public static void setSpeed(uint8_t _speed);

#endif
