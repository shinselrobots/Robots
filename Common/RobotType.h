// RobotType.h - FOR TURTLE!
// Top level selection of what kind of robot this is!
// This file included by Microcontroller code, and is shared by both compilers
// Make sure syntax works with all compilers needed

#ifndef __ROBOT_SELECTION_H__
#define __ROBOT_SELECTION_H__

#include "ClientOrServer.h"

// Hardware Configuration for various types of robots
// Robot type
#define LOKI							0
#define TURTLE							1
#define CARBOT							2

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONFIGURE HARDWARE HERE! - USES ENVIRONMENT VARIABLE SET IN PROJECT

#ifdef __LOKI_CONFIG__
	#define ROBOT_TYPE					LOKI
#endif

#ifdef __TURTLE_CONFIG__
	#define ROBOT_TYPE					TURTLE
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define KINECT_OPEN_SOURCE				0
#define KINECT_MICROSOFT_BETA			1
#define KINECT_MICROSOFT_1_0			2

// Select which Kinect SDK to use
#define KINECT_SDK_TYPE		KINECT_MICROSOFT_1_0

// Motor control types
#define ER1_MOTOR_CONTROL				0
#define POLOLU_TREX_MOTOR_CONTROL		1
#define SERVO_MOTOR_CONTROL				2
#define IROBOT_MOTOR_CONTROL			3
#define ARDUINO_MOTOR_CONTROL			4
#define KOBUKI_MOTOR_CONTROL			5

// Servo control types
#define PIC_SERVO_CONTROL				4
#define EXTERN_SERVO_CONTROL			5
#define DYNA_SERVO_CONTROL				6
#define SONY_SERIAL_CAMERA				7

// Servo Config Types
#define SERVO_CONFIG_LOKI				0
#define SERVO_CONFIG_CARBOT				1
#define SERVO_CONFIG_TURTLE				2

// Sensor Configuraitons (varies by robot)
#define SENSOR_CONFIG_LOKI				0
#define SENSOR_CONFIG_CARBOT			1
#define SENSOR_CONFIG_TURTLE			2
#define SENSOR_CONFIG_TELEOP			3

#if ROBOT_TYPE == LOKI
	#define HW_INTERFACE_TYPE			PIC_INTERFACE_BOARD
	#define MOTOR_CONTROL_TYPE			POLOLU_TREX_MOTOR_CONTROL // ARDUINO_MOTOR_CONTROL
	#define CAMERA_CONTROL_TYPE			DYNA_SERVO_CONTROL
	#define SERVO_CONTROL_TYPE			PIC_SERVO_CONTROL
	#define OTHER_SERVO_CONTROL_TYPE	DYNA_SERVO_CONTROL
	#define SENSOR_CONFIG_TYPE			SENSOR_CONFIG_LOKI
	#define ROBOT_DATA_PATH	"C:\\Dev\\_Robot\\LokiData"
	#define ROBOT_COMMON_PATH L"C:\\Dev\\_Robot\\Common"
	#define DYNA_SERVO_RX64_INSTALLED	0 // Set to 0 if no RX64 servos used


#elif ROBOT_TYPE == CARBOT
	#define PIC_CODE_VERSION			22
	#define MOTOR_CONTROL_TYPE			EXTERN_SERVO_CONTROL
	#define SERVO_CONTROL_TYPE			EXTERN_SERVO_CONTROL
	#define CAMERA_CONTROL_TYPE			EXTERN_SERVO_CONTROL
	#define OTHER_SERVO_CONTROL_TYPE	EXTERN_SERVO_CONTROL
	#define SENSOR_CONFIG_TYPE			SENSOR_CONFIG_CARBOT
	#define ROBOT_DATA_PATH	"C:\\Dev\\_Robot\\SeekerData"
	#define ROBOT_COMMON_PATH L"C:\\Dev\\_Robot\\Common"


#elif ROBOT_TYPE == TURTLE
	#define PIC_CODE_VERSION			0	// No PIC used
	#define MOTOR_CONTROL_TYPE			KOBUKI_MOTOR_CONTROL	// <============= Change this depending upon Base used!
//	#define MOTOR_CONTROL_TYPE			IROBOT_MOTOR_CONTROL	// <============= Change this depending upon Base used!
	#define CAMERA_CONTROL_TYPE			DYNA_SERVO_CONTROL
	#define SERVO_CONTROL_TYPE			DYNA_SERVO_CONTROL
	#define OTHER_SERVO_CONTROL_TYPE	DYNA_SERVO_CONTROL
	#define SENSOR_CONFIG_TYPE			SENSOR_CONFIG_TELEOP	// <============= Change this depending upon Base used!
	#define ROBOT_DATA_PATH	"C:\\Dev\\_Robot\\TurtleData"
	#define ROBOT_COMMON_PATH L"C:\\Dev\\_Robot\\Common"

#else
	#error BAD ROBOT_TYPE
#endif


#endif // __ROBOT_SELECTION_H__