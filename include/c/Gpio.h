/**
* @file     Gpio.h
* @author   Adam Morrissett
* @version  v1.0
* @date     27 Sept. 2016
* @brief    This file is used to call startup functions
*           Because the clocks and modes for each pin
*           group has to be configured for each project,
*           it was decided it would be better to make a
*           faster and more reliable way to do this.
*/

#ifndef GPIO_H
#define GPIO_H

#include "stm32l476xx.h"

#define MODE_WIDTH 2		// Width of mode setting for each port (2 bits)
#define OTYPE_WIDTH 1		// Width of output tpye setting for each port (1 bit)
#define OSPEED_WIDTH 2	// Width of mode output speed setting for each port (2 bits)
#define PUPD_WIDTH 2		// Width of internal resistor setting for each port (2 bits)

#define TWO_BIT_RESET 3	// Used to reset 2-bit wide settings
#define ONE_BIT_RESET 1	// Used to reset 1-bit wide settings

/**
 * Structure for the GPIO. This structure is similar to the GPIO_TypeDef, but
 * this structure contains a GPIO_TypeDef and a pin number. 
 */
typedef struct {
  GPIO_TypeDef* port;  // Pin number within the GPIO port; used for shifting
  uint8_t pin;        // GPIO port (A, B, C, etc.)
} gpio_t;

/**
* Enumeration for port modes. 
* 
*	INPUT (Input/Reset) - 00
* OUTPUT (General Purpose Output) - 01
* ALTERNATE (Alternate function mode) - 10
* ANALOG (Analog) - 11
*/
typedef enum {INPUT = 0, \
							OUTPUT = 1, \
							ALTERNATE = 2, \
							ANALOG = 3} mode;

/**
* Enumeration for output types.
*							
*	PUSH_PULL	(Push Pull/Reset) - 0						
* OPEN_DRAIN (Open Drain) - 1
*/							
typedef enum {PUSH_PULL = 0, \
							OPEN_DRAIN = 1} outputType;

/**
* Enumeration for output speed.
*
* LOW_SPEED (Low Speed/Reset) - 00
* MEDIUM_SPEED (Medium Speed) - 01
* HIGH_SPEED (High Speed) - 10
* VERY_HIGH_SPEED	(Very High Speed) - 11
*/	
typedef enum {LOW_SPEED = 0, \
							MEDIUM_SPEED = 1, \
							HIGH_SPEED = 2, \
							VERY_HIGH_SPEED = 3} outputSpeed;

/**
* Enumeration for internal port resistor.
*							
*	NO_PUPD (No Pull-Up, Pull-Down/Reset) - 00
* PULL_UP (Pull-Up) - 01
* PULL_DOWN (Pull-Down) - 10					
* RESERVED (Reserved) - 11 ** NOT IMPLEMENTED **
*/
typedef enum {NO_PUP = 0, \
							PULL_UP = 1, \
							PULL_DOWN = 2} pullUpPullDown;

/**
 * Initializes the gpio structure.
 *
 * @param _gpioStructure the desired gpio_t structure to initialize
 * @param _gpioPort the desired port of the gpio structure
 * @param _gpioPin the desired pin number of the gpio structure
 */
void initGpio(gpio_t* _gpioStructure, GPIO_TypeDef * _gpioPort, 
  uint8_t _pinNumber);
              
/**
* Enable the clock of a specified GPIO group.
* 
* @param _gpioGroup GPIO group for which the clock
*				 should be enbaled
*/
void enableClock(uint32_t _gpioGroup);

/**
*	Set mode of specified GPIO pin to specified value.
*							
* @param _gpioGroup GPIO group for which the mode 
* 			 should be set
* @param _pinNum pin number within the GPIO group
* @param _value mode to which the GPIO pin should be set					
*/
void setMode(GPIO_TypeDef *_gpioGroup, uint32_t _pinNum, mode _value);

/**
* Set output type of specified GPIO pin to specified value
*							
* @param _gpioGroup GPIO group for which the output type 
* 			 should be set
* @param _pinNum pin number within the GPIO group
* @param _value output type to which the GPIO pin should 
				 be set
*/
void setOType(GPIO_TypeDef *_gpioGroup, uint32_t _pinNum, outputType _value);

/**
* Set output speed of specified GPIO pin to specified value
*							
* @param _gpioGroup GPIO group for which the output speed 
* 			 should be set
* @param _pinNum pin number within the GPIO group
* @param _value output speed to which the GPIO pin should 
				 be set
*/
void setOSpeed(GPIO_TypeDef *_gpioGroup, uint32_t _pinNum, outputSpeed _value);

/**
* Set the internal resistor of specified GPIO pin to specified
* mode.
*
* @param _gpioGroup GPIO group for which the internal resistor mode
* 			 should be set
* @param _pinNum pin number within the GPIO group
* @param _value mode to which the internal resistor should be set
*/
void setPupd(GPIO_TypeDef *_gpioGroup, uint32_t _pinNum, pullUpPullDown _value);
	
/**
 * Reads the IDR value of the specified pin.
 * 
 * @param _gpioGroup pointer to the port of the specified pin
 * @param _pinNum the number of the specified pin
 * @return the value of the IDR of the specified pin
 */
uint8_t readPin(GPIO_TypeDef *_gpioGroup, uint8_t _pinNum);

/**
 * Writes a value to the ODR of the specified pin.
 *
 * @param _gpioGroup pointer to the GPIO port of the specified pin
 * @param _pinNum the number of the specified pin
 * @param _value the value to write to the specified pin's ODR
 */
void writePin(GPIO_TypeDef *_gpioGroup, uint8_t _pinNum, uint8_t _value);
	
#endif
