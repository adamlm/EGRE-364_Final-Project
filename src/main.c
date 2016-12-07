/**
* @file     Main.c
* @author   Adam Morrissett
* @version  v1.0
* @date     5 Dec. 2016
* @brief    This file is the main entry point into the robot code.
*           All startup functions are called from here, and all robot operations
*           are initiated from here.
*/

#include "DriveBase.h"
#include "distance_sensor.h"
#include "reflectance_array.h"
#include "stm32l476xx.h"

// Function prototypes
static void robotInit(void);
static void periphClockInit(void);

// Declarations
static driveBase_t driveBase;  // The drive base of the robot
//  distanceSensor_t distanceSensor;  // The distance sensor on the robot


/**
 * This is the main entry point into the robot code.
 * All initiations are robot actions are originally called from this method.
 *
 */
int main(void) {  
  robotInit();  // Initialize the robot
  
  while(1);
  return 0;
}

/**
 * This is the initiation method.
 * All robot components are initialized here. 
 */
static void robotInit(void) {
  periphClockInit();  // Initialize the peripheral clocks
  initDriveBase(&driveBase);  // Initialize the drive base
	distance_sensor_init();// Initialize the distance sensor   
	reflectance_init();//initialize the reflectance sensors
}

/**
 * Initializes all of the clocks of the peripherals
 */
static void periphClockInit(void) {
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN |
    RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_GPIODEN | RCC_AHB2ENR_GPIOEEN | 
    RCC_AHB2ENR_GPIOFEN | RCC_AHB2ENR_GPIOGEN | RCC_AHB2ENR_GPIOHEN;
}
