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
 *
 */
typedef enum robotState {
    INIT = 0,
    MAZE = 1,
    LINE = 2,
    ART = 3
};

/**
* Sets the desired state of the robot
*
* @param _state desired state of the robot
*/
static void setState(robotState _state);


/**
* Gets the current state of the robot.
*
* @return current state of the robot
*/
static robotState getState(void);

#endif
