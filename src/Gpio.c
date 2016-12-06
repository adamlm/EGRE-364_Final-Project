/**
* @file     Gpio.c
* @author   Adam Morrissett
* @version  v1.0
* @date     27 Sept. 2016
* @brief    This file is used to call starup functions
*           Because the clocks and modes for each pin
*           group has to be configured for each project,
*           it was decided it would be better to make a
*           faster and more reliable way to do this.
*/

#include "Gpio.h"
#include <stdint.h>

/**
 * Initializes the gpio structure.
 *
 * @param _gpioStructure the desired gpio_t structure to initialize
 * @param _gpioPort the desired port of the gpio structure
 * @param _gpioPin the desired pin number of the gpio structure
 */
void initGpio(gpio_t* _gpioStructure, GPIO_TypeDef * _gpioPort, 
  uint8_t _pinNumber) {
  // Assign members    
  _gpioStructure->port = _gpioPort;
  _gpioStructure->pin = _pinNumber;
}

void enableClock(uint32_t _gpioGroup) {
	RCC->AHB2ENR |= _gpioGroup;
}

void setMode(GPIO_TypeDef *_gpioGroup, uint32_t _pinNum, mode _value) {
	_gpioGroup->MODER &= ~(TWO_BIT_RESET << (MODE_WIDTH * _pinNum));	// Reset MODER for pin
	_gpioGroup->MODER |= (_value << (MODE_WIDTH * _pinNum));					// Set MODER for pin
}

void setOType(GPIO_TypeDef *_gpioGroup, uint32_t _pinNum, outputType _value) {
	_gpioGroup->OTYPER &= ~(ONE_BIT_RESET << (OTYPE_WIDTH * _pinNum));	// Reset OTYPE for pin
	_gpioGroup->OTYPER |= (_value << (OTYPE_WIDTH * _pinNum));					// Set OTYPE for pin
}

void setOSpeed(GPIO_TypeDef *_gpioGroup, uint32_t _pinNum, outputSpeed _value) {
	_gpioGroup->OSPEEDR &= ~(TWO_BIT_RESET << (OSPEED_WIDTH * _pinNum));	// Reset OSPEED for pin
	_gpioGroup->OSPEEDR |= (_value << (OSPEED_WIDTH * _pinNum));					// Set OSPEED for pin
}

void setPupd(GPIO_TypeDef *_gpioGroup, uint32_t _pinNum, pullUpPullDown _value) {
	_gpioGroup->PUPDR &= ~(ONE_BIT_RESET << (PUPD_WIDTH * _pinNum));	// Reset PUPD for pin
	_gpioGroup->PUPDR |= (_value << (PUPD_WIDTH * _pinNum));					// Set PUPD for pin
}


uint8_t readPin (GPIO_TypeDef *_gpioGroup, uint8_t _pinNum)  {
	
	return _gpioGroup->IDR & (1 << _pinNum);
}

void writePin (GPIO_TypeDef *_gpioGroup, uint8_t _pinNum, uint8_t _value) {
	if (_value) {
		_gpioGroup->ODR |= (1 << _pinNum);
	}
	else {
		_gpioGroup->ODR &= ~(1 << _pinNum);
	}
}
