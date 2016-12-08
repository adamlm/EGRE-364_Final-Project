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
#include "RobotState.h"
#include "stm32l476xx.h"
#include "SysTimer.h"
#include "Gpio.h"

// Function prototypes
static void robotInit(void);
static void periphClockInit(void);
static void mazePeriodic(void);
static void linePeriodic(void);
static void artPeriodic(void);
static void Dpad_init(void);

// Declarations
static robotState state;
static driveBase_t driveBase;  // The drive base of the robot
//  distanceSensor_t distanceSensor;  // The distance sensor on the robot
uint8_t speed;

/**
 * This is the main entry point into the robot code.
 * All initiations are robot actions are originally called from this method.
 *
 */
int main(void) {
  state = INIT;
  
	robotInit();
	Dpad_init();
	
  while(1) {
		if (readPin(GPIOA, 3)) state = MAZE;
		else if (readPin(GPIOA, 5)) state = ART;
		else if (readPin(GPIOA, 0)) state = LINE, speed = 0;
		else if (readPin(GPIOA, 2)) state = LINE, speed = 1;
		
    switch(state) {
      case INIT : {
				writePin(GPIOA, 7, 1);
        //robotInit();  // Initialize the robot
        //state = MAZE;
      }; break;
      case MAZE : {
				writePin(GPIOA, 7, 0);
        mazePeriodic(); // Perform maze-specific logic
      }; break;
      case LINE : {
				writePin(GPIOA, 7, 0);
        linePeriodic(); // Perform line-specific logic
      }; break;
      case ART : {
				writePin(GPIOA, 7, 0);				
        artPeriodic();  // Perform art-specific logic
      }; break;
    }
  }   
}

/**
 * This is the initiation method.
 * All robot components are initialized here. 
 */
static void robotInit(void) {
	SysTick_Init();
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

/**
 * Performs the maze challenge specific logic.
 */
static void mazePeriodic(void) {
	uint16_t distance;
	distance = distance_read();
	if (distance < 200) {
		accelerateToSpeed(50, -20, 2);
	}
	else if (distance < 210) {
		accelerateToSpeed(90,40, 2); 
	}
	else if (distance < 220) {
		accelerateToSpeed(150,100, 2);
	}
	else if (distance > 260) {
		accelerateToSpeed(20,90 , 2);
	}
	else if (distance > 250) {
		accelerateToSpeed(40,90, 2);
	}
	else if (distance > 240) {
		accelerateToSpeed(100,150, 2);
	}
	else	accelerateToSpeed(400,400, 2);
	
	__asm { nop}
}

/**
 * Performs the line following challenge specific logic
 */
static void linePeriodic(void) {
	uint8_t reflectance = reflectance_read();
	uint8_t outer_left_reflectance = !((reflectance & 8) >> 3);
	uint8_t inner_left_reflectance = !((reflectance & 4) >> 2);
	uint8_t inner_right_reflectance = !((reflectance & 2) >> 1);
	uint8_t outer_right_reflectance = !(reflectance & 1);

if (!speed) {	
	if (outer_left_reflectance == outer_right_reflectance && inner_left_reflectance == inner_right_reflectance){
		accelerateToSpeed(100, 100, 2);
	}
	else if (outer_left_reflectance && ~outer_right_reflectance) {
		accelerateToSpeed(0,0,2);
		accelerateToSpeed(-30,50, 5);
		delay(100);
	}
  else if (outer_right_reflectance && ~outer_left_reflectance) {
		accelerateToSpeed(0,0,2);
		accelerateToSpeed(50,-30, 5);
		delay(100);
	}
	else if (inner_left_reflectance && ~inner_right_reflectance) {
		accelerateToSpeed(50,100, 2);
	}
	else if (inner_right_reflectance && ~inner_left_reflectance) {
		accelerateToSpeed(100,50, 2);
	}
}
else {
	if (outer_left_reflectance == outer_right_reflectance && inner_left_reflectance == inner_right_reflectance){
		accelerateToSpeed(500, 500, 5);
	}
	else if (outer_left_reflectance && ~outer_right_reflectance) {
		accelerateToSpeed(-20,100, 1);
	}
  else if (outer_right_reflectance && ~outer_left_reflectance) {
		accelerateToSpeed(100,-20, 1);
	}
	else if (inner_left_reflectance && ~inner_right_reflectance) {
		accelerateToSpeed(100,180, 3);
	}
	else if (inner_right_reflectance && ~inner_left_reflectance) {
		accelerateToSpeed(180,100, 3);
	}	
}
	//delay(10);
}

/**
 * Performs the art challenge specific logic
 */
static void artPeriodic(void) {
  //accelerateToSpeed(300, 300, 2);
	/*
  static int i=0;
	if (i<3){
  delay(100);
  accelerateToSpeed(200, 30, 5);
	delay(100);
	accelerateToSpeed(30,200,5);
		i++;
	}
	else if (i == 3) {
		accelerateToSpeed(20,200, 5);
		delay(300);
		accelerateToSpeed(200, 200, 5);
		delay(100);
		i++;
	}
	else {
		//delay(400);
				accelerateToSpeed(200,20, 5);
	}
	*/
///////////////1  


  accelerateToSpeed(300, 300, 5);
  
  delay(300);
  accelerateToSpeed(0,0, 2);
  accelerateToSpeed(-170, 170, 30);
  
  delay(20);
  accelerateToSpeed(0,0, 2);
	
}

static void Dpad_init(void) {
	setMode(GPIOA, 0, INPUT);
	setMode(GPIOA, 2, INPUT);
	setMode(GPIOA, 3, INPUT);
	setMode(GPIOA, 5, INPUT);
	
	setPupd(GPIOA, 0, PULL_DOWN);
	setPupd(GPIOA, 2, PULL_DOWN);
	setPupd(GPIOA, 3, PULL_DOWN);
	setPupd(GPIOA, 5, PULL_DOWN);
	
	setMode(GPIOA, 7, OUTPUT);
	setPupd(GPIOA, 7, NO_PUP);
	setOType(GPIOA, 7, PUSH_PULL);
	setOSpeed(GPIOA, 7, VERY_HIGH_SPEED);
	
}
