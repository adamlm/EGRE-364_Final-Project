#include "distance_sensor.h"
#include "ADC.h"

void distance_sensor_init(void) {
	ADC_Init();
}

uint16_t distance_read(void) {
	//returns distance in mm;
	
	uint32_t sample;
	
		ADC1->CR |= ADC_CR_ADSTART;														// Start the ADC conversion sequence
		while ( (ADC123_COMMON->CSR | ADC_CSR_EOC_MST) == 0);	// Wait for the end of conversion (EOC) flag
		sample = ADC1->DR;																		// Store the result from the ADC

		// To determine this equation, the ADC result was
		// graphed against the inverse of the measured
		// distance between the sensor and the target.
		// The data was used to create a linear fit, and
		// the resulting equatoin was used to determine 
		// equation for the result
		// Result is the distance between the sensor and the target (in mm)
		// Sample is the 12-bit number from the ADC
		return 278020U/(sample-162U);	// Equation for determining the result (12-bit)
}
