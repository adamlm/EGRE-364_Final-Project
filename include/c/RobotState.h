/**
* @file     RobotState.h
* @author   Adam Morrissett
* @version  v1.0
* @date     28 Nov. 2016
* @brief    This file contains the functions to set
*           and get the current state of the robot.
*/

#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H

/**
 * Enumeration for the robot states. 
 */
typedef enum {
    INIT = 0, // Initialize the robot 
    MAZE = 1, // Robot is performing the maze challenge
    LINE = 2, // Robot is performing the line challenge
    ART = 3   // Robot is performing the art challenge
} robotState;

#endif
