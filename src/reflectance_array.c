#include "Gpio.h"
#include <stdint.h"

uint8_t reflectance_read(void) {
	
		// Counters for the individual reflectance sensors
	int32_t counter_1 = 0;
	int32_t counter_2 = 0;
	int32_t counter_3 = 0;
	int32_t counter_4 = 0;
	
	// Reflectance seen by the sensors (0 for black, 1 for white)
	int32_t reflectance_1 = 0;
	int32_t reflectance_2 = 0;
	int32_t reflectance_3 = 0;
	int32_t reflectance_4 = 0;
	
	// Threshold for the reflectance sensors
	// The threshold is the same for all the sensors
	const int32_t common_threshold = 0x60;
	const uint32_t timeout = 10000;
	
	// Read reflectance sensor 1
		setMode(GPIOE, 10, OUTPUT);	// Set GPIOB pin 2 to output	mode
		writePin(GPIOE, 10, 1);			// Set GPIOB pin 2 output to high (1)
		delay(2);									// Wait 10 ms
		
		setMode(GPIOE, 10, INPUT);		// Set GPIOB pin 2 to input mode
		while (GPIOE->IDR & 1<<10 && counter_1<timeout) {
			counter_1++;							// Count up until GPIOB pin 2's IDR is low (0)
		}
		
		if (counter_1 < common_threshold) {
			reflectance_1 = 1; 	// Object is white
		} else {
			reflectance_1 = 0;	// Object is black
		}
		
		counter_1 = 0;	// Reset the counter to 0		
	
		// Read reflectance sensor 2
		setMode(GPIOE, 11, OUTPUT);	// Set GPIOB pin 2 to output	mode
		writePin(GPIOE, 11, 1);			// Set GPIOB pin 2 output to high (1)
		delay(2);									// Wait 10 ms
		
		setMode(GPIOE, 11, INPUT);		// Set GPIOB pin 2 to input mode
		while (GPIOE->IDR & 1<<11 && counter_2<timeout) {
			counter_2++;							// Count up until GPIOB pin 2's IDR is low (0)
		}
		
		if (counter_2 < common_threshold) {
			reflectance_2 = 1; 	// Object is white
		} else {
			reflectance_2 = 0;	// Object is black
		}
		
		counter_2 = 0;	// Reset the counter to 0		
		
		// Read reflectance sensor 3
		setMode(GPIOE, 12, OUTPUT);	// Set GPIOB pin 2 to output	mode
		writePin(GPIOE, 12, 1);			// Set GPIOB pin 2 output to high (1)
		delay(2);									// Wait 10 ms
		
		setMode(GPIOE, 12, INPUT);		// Set GPIOB pin 2 to input mode
		while (GPIOE->IDR & 1<<12 && counter_3<timeout) {
			counter_3++;							// Count up until GPIOB pin 2's IDR is low (0)
		}
		
		if (counter_3 < common_threshold) {
			reflectance_3 = 1; 	// Object is white
		} else {
			reflectance_3 = 0;	// Object is black
		}
		
		counter_3 = 0;	// Reset the counter to 0		
		
		// Read reflectance sensor 4
		setMode(GPIOE, 13, OUTPUT);	// Set GPIOB pin 2 to output	mode
		writePin(GPIOE, 13, 1);			// Set GPIOB pin 2 output to high (1)
		delay(2);									// Wait 10 ms
		
		setMode(GPIOE, 13, INPUT);		// Set GPIOB pin 2 to input mode
		while (GPIOE->IDR & 1<<13 && counter_4<timeout) {
			counter_4++;							// Count up until GPIOB pin 2's IDR is low (0)
			}
		
		if (counter_4 < common_threshold ) {
			reflectance_4 = 1; 	// Object is white
		} else {
			reflectance_4 = 0;	// Object is black
		}
		
		return (uint8_t) ((reflectance_1 & 1) << 3) | ((reflectance_2 & 1) << 2)
									| ((reflectance_3 & 1) << 1) | (reflectance_4 & 1);
		
}

void reflectance_Init(void){	
	
	// Enable the clock for GPIOB
	enableClock(RCC_AHB2ENR_GPIOEEN);

	// Set MODERs for the pins
	setMode(GPIOE, 10, OUTPUT);
	setMode(GPIOE, 11, OUTPUT);
	setMode(GPIOE, 12, OUTPUT);
	setMode(GPIOE, 13, OUTPUT);
	
	// Set OSPEEDRs for the pins
	setOSpeed(GPIOE, 10, HIGH_SPEED);
	setOSpeed(GPIOE, 11, HIGH_SPEED);
	setOSpeed(GPIOE, 12, HIGH_SPEED);
	setOSpeed(GPIOE, 13, HIGH_SPEED);
	
	// Set OTYPERs for the pins
	setOType(GPIOE, 10, PUSH_PULL);
	setOType(GPIOE, 11, PUSH_PULL);
	setOType(GPIOE, 12, PUSH_PULL);
	setOType(GPIOE, 13, PUSH_PULL);

	// Set PUPDRs for the pins
	setPupd(GPIOE, 10, NO_PUP);
	setPupd(GPIOE, 11, NO_PUP);
	setPupd(GPIOE, 12, NO_PUP);
	setPupd(GPIOE, 13, NO_PUP);	
}