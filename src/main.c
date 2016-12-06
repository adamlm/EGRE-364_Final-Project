/**
* @file     Main.c
* @author   Adam Morrissett
* @version  v1.0
* @date     5 Dec. 2016
* @brief    This file is the main entry point into the robot code.
*           All startup functions are called from here, and all robot operations
*           are initiated from here.
*/

#include "stm32l476xx.h"
#include "DriveBase.h"

// Function prototypes
static void robotInit(void);

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
  
  return 0;
}

/**
 * This is the initiation method.
 * All robot components are initialized here. 
 */
static void robotInit(void) {
  initDriveBase(&driveBase);  // Initialize the drive base
// initiDistanceSensor(&distanceSensor);  // Initialize the distance sensor    
}
