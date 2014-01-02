// HWInterfaceLokiArduino.h
// Command interface between the PC and Arduino Microcontroller; Shared by both compilers
// Make sure syntax works with all compilers needed
#ifndef __ROBOT_HW_INTERFACE_LOKI_ARDUINO_H__
#define __ROBOT_HW_INTERFACE_LOKI_ARDUINO_H__
//#include "stdafx.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         LOKI ARDUINO INTERFACE
////////////////////////////////////////////////////////////////////////////////////////////////////////

	#define ARDUINO_CODE_VERSION		3 // Must match between PC and Arduino.  This file is shared by both

	// Message Types from the Arduino
	#define ARDUINO_MESSAGE_STATUS	1
	#define ARDUINO_MESSAGE_TEXT	2

	#define NUMBER_OF_WHEEL_ODOMETERS							  2		// LOKI has a Right and Left Odometer

	// WARNING! If you change these, you must update SensorOffsetDegrees in Globals.cpp!
	#define NUM_IR_SENSORS										  6	// 2 head mounted LR, 2 front facing LR, 2 side mounted SR
	#define NUM_IR3_SENSORS										  4 // 8	// I2C-IT IR Sensors - DEBUG!!!!
	#define NUM_US_SENSORS										  3	// 1 head mounted, 2 front mounted


	// Sensor Positions in arrays
	#define	IR_SENSOR_SIDE_LEFT									  0
	#define	IR_SENSOR_FRONT_LEFT								  1
	#define	IR_SENSOR_HEAD_LEFT									  2
	#define	IR_SENSOR_HEAD_RIGHT								  3
	#define	IR_SENSOR_FRONT_RIGHT								  4
	#define	IR_SENSOR_SIDE_RIGHT								  5

	#define US_SENSOR_CAMERA									  0	// Mounted on Camera
	#define US_SENSOR_FRONT_LEFT								  1
	#define US_SENSOR_FRONT_RIGHT								  2

	// Raw data from the Arduino for Loki
	typedef struct
	{
		BYTE StatusFlags;		
		BYTE LastError;			
		BYTE DebugCode;			
		BYTE HWBumper;			
		BYTE IRBumper;		
		BYTE ArmBumperL;		
		BYTE ArmBumperR;		
		BYTE Battery0;			
		BYTE CompassHigh;
		BYTE CompassLow;		
		BYTE OdometerHighL;		
		BYTE OdometerLowL;		
		BYTE OdometerHighR;		
		BYTE OdometerLowR;		
		BYTE nOdometerSamples;
		BYTE AndroidConnected;
		BYTE AndroidAccEnabled;
		BYTE AndroidCmd;
		BYTE AndroidCompassHigh;	
		BYTE AndroidCompassLow;		
		BYTE AndroidRollHigh;
		BYTE AndroidRollLow;
		BYTE AndroidPitchHigh;
		BYTE AndroidPitchLow;
		BYTE LeftHandPressureL;
		BYTE LeftHandPressureR;
		BYTE IR[NUM_IR_SENSORS];//18-23 	- UP TO N, may be less! - On main Arduino board
		BYTE IR3[NUM_IR3_SENSORS];//24-27	- UP TO N, may be less! - I2C-IT IR Rangers
//		BYTE ThermalArray[9];	//			- Ambient + 8 Pixels - Devantech TPA81 Thermal Array Sensor
//		BYTE US[NUM_US_SENSORS];//

	} ARDUINO_STATUS_T;
	#ifndef __ARDUINO_TARGET
	#pragma pack( 4 )
	#endif

	////////////////////////////////////////////////////////////////
	#ifndef __ARDUINO_TARGET	// Arduino Compiler does not understand pack
	#pragma pack( 1 )
	#endif


// I2C-IT Sensors
#define ARM_L_IR_SENSOR_CLAW		g_SensorStatus.IR3[0]
#define ARM_L_IR_SENSOR_ELBOW		g_SensorStatus.IR3[1]
#define ARM_R_IR_SENSOR_CLAW		g_SensorStatus.IR3[2]
#define ARM_R_IR_SENSOR_ELBOW		g_SensorStatus.IR3[3]


// HW Bumpers.  Arduino uses: gStatus_HW_Bumper
#define HW_BUMPER_AVAILABLE_MASK_00			0x00	// Bit 0 mask
#define HW_BUMPER_AVAILABLE_MASK_02			0x02	// Bit 1 mask
#define HW_BUMPER_AVAILABLE_MASK_04			0x04	// Bit 2 mask
#define HW_BUMPER_AVAILABLE_MASK_08			0x08	// Bit 3 mask
#define HW_BUMPER_SIDE_RIGHT_MASK			0x10	// Bit 4 mask
#define HW_BUMPER_SIDE_LEFT_MASK			0x20	// Bit 5 mask
#define HW_BUMPER_REAR_MASK					0x40	// Bit 6 mask
#define HW_BUMPER_FRONT_MASK				0x80	// Bit 7 mask

// No longer used for Loki:
//#define FRONT_LEFT_BUMPER_BIT				   6	// Bit 6 - used by bit_set function in TimerISR
//#define FRONT_RIGHT_BUMPER_BIT				   7	// Bit 7


// IR Bumpers.  Arduino uses: gStatus_IR_Bumper
#define IR_BUMPER_FRONT_LEFT_MASK			0x01	// Bit 0 mask
#define IR_BUMPER_FRONT_RIGHT_MASK			0x02	// Bit 1 mask
#define IR_BUMPER_CLIFF_LEFT_MASK			0x04	// Bit 2 mask
#define IR_BUMPER_CLIFF_RIGHT_MASK			0x08	// Bit 3 mask
#define IR_BUMPER_REAR_LEFT_MASK			0x10	// Bit 4 mask
#define IR_BUMPER_REAR_RIGHT_MASK			0x20	// Bit 5 mask
#define IR_BUMPER_PIR_LEFT_MASK				0x40	// Bit 6 mask
#define IR_BUMPER_PIR_RIGHT_MASK			0x80	// Bit 7 mask

// Left Arm Bumpers (IR and HW)
//#define ARM_L_BUMPER_NC_MASK				0x01	// Bit 0 mask
#define ARM_L_BUMPER_INSIDE_CLAW_MASK		0x02	// Bit 1 mask
//#define ARM_L_BUMPER_NC_MASK				0x04	// Bit 2 mask
//#define ARM_L_BUMPER_NC_MASK				0x08	// Bit 3 mask
//#define ARM_L_BUMPER_NC_MASK				0x10	// Bit 4 mask
#define ARM_L_HW_BUMPER_ELBOW_MASK			0x20	// Bit 5 mask	- HW Bumper switch on Elbow!
#define ARM_L_IR_BUMPER_FINGER_L_MASK		0x40	// Bit 6 mask
#define ARM_L_IR_BUMPER_FINGER_R_MASK		0x80	// Bit 7 mask

// Right Arm Bumpers (IR and HW)
//#define ARM_R_BUMPER_NC_MASK				0x01	// Bit 0 mask
//#define ARM_R_BUMPER_INSIDE_CLAW_MASK		0x02	// Bit 1 mask
//#define ARM_R_BUMPER_NC_MASK				0x04	// Bit 2 mask
//#define ARM_R_BUMPER_NC_MASK				0x08	// Bit 3 mask
//#define ARM_R_BUMPER_NC_MASK				0x10	// Bit 4 mask
#define ARM_R_HW_BUMPER_ELBOW_MASK			0x20	// Bit 5 mask	- HW Bumper switch on Elbow!
//#define ARM_R_IR_BUMPER_FINGER_L_MASK		0x40	// Bit 6 mask
//#define ARM_R_IR_BUMPER_FINGER_R_MASK		0x80	// Bit 7 mask


// Bumper Macros
#define IR_BUMPER_RANGE						 100	// Tenth_Inches - detection distance for IR bumpers
#define IR_BUMPER_OBJECT_FRONT_LEFT			(  g_SensorStatus.IRBumper & IR_BUMPER_FRONT_LEFT_MASK   )
#define IR_BUMPER_OBJECT_FRONT_RIGHT		(  g_SensorStatus.IRBumper & IR_BUMPER_FRONT_RIGHT_MASK  )
#define IR_BUMPER_CLIFF_LEFT				(  g_SensorStatus.IRBumper & IR_BUMPER_CLIFF_LEFT_MASK   )	// Lack of object = cliff
#define IR_BUMPER_CLIFF_RIGHT				(  g_SensorStatus.IRBumper & IR_BUMPER_CLIFF_RIGHT_MASK  )
#define IR_BUMPER_OBJECT_REAR_LEFT			(  g_SensorStatus.IRBumper & IR_BUMPER_REAR_LEFT_MASK    )
#define IR_BUMPER_OBJECT_REAR_RIGHT			(  g_SensorStatus.IRBumper & IR_BUMPER_REAR_RIGHT_MASK   )
#define PIR_MOTION_DETECTED_LEFT			(  g_SensorStatus.IRBumper & IR_BUMPER_PIR_LEFT_MASK     )
#define PIR_MOTION_DETECTED_RIGHT			(  g_SensorStatus.IRBumper & IR_BUMPER_PIR_RIGHT_MASK    )

#define ARM_L_HW_BUMPER_OBJECT_ELBOW		(  g_SensorStatus.ArmBumperL & ARM_L_HW_BUMPER_ELBOW_MASK	 )
#define ARM_L_IR_BUMPER_OBJECT_FINGER_L		(  g_SensorStatus.ArmBumperL & ARM_L_IR_BUMPER_FINGER_L_MASK )
#define ARM_L_IR_BUMPER_OBJECT_FINGER_R		(  g_SensorStatus.ArmBumperL & ARM_L_IR_BUMPER_FINGER_R_MASK )
#define ARM_L_IR_BUMPER_INSIDE_CLAW			(  g_SensorStatus.ArmBumperL & ARM_L_BUMPER_INSIDE_CLAW_MASK )

#define ARM_R_HW_BUMPER_OBJECT_ELBOW		(  g_SensorStatus.ArmBumperR & ARM_R_HW_BUMPER_ELBOW_MASK	 )

#define HW_BUMPER_HIT_FRONT					(  g_SensorStatus.HWBumper & HW_BUMPER_FRONT_MASK  )
#define HW_BUMPER_HIT_REAR					(  g_SensorStatus.HWBumper & HW_BUMPER_REAR_MASK   )
#define HW_BUMPER_HIT_SIDE_LEFT				(  g_SensorStatus.HWBumper & HW_BUMPER_SIDE_LEFT_MASK   )
#define HW_BUMPER_HIT_SIDE_RIGHT			(  g_SensorStatus.HWBumper & HW_BUMPER_SIDE_RIGHT_MASK  )


// Analog Sensors used as bumper sensors
#define S_FOREARM_BONE_LEN_TENTH_INCHES_L							147.5	// Tenth_Inches
#define S_FOREARM_BONE_LEN_TENTH_INCHES_R							132.5	// Tenth_Inches

#define ARM_L_IR_BUMPER_OBJECT_ELBOW		(  ARM_L_IR_SENSOR_ELBOW < (S_FOREARM_BONE_LEN_TENTH_INCHES_L+IR_ELBOW_HIT_RANGE_TENTH_INCHES)  ) // I2C-IT Sensor: True if object detected within N Tenth_Inches
#define ARM_R_IR_BUMPER_OBJECT_ELBOW		(  ARM_R_IR_SENSOR_ELBOW < (S_FOREARM_BONE_LEN_TENTH_INCHES_R+IR_ELBOW_HIT_RANGE_TENTH_INCHES)  ) // I2C-IT Sensor: True if object detected within N Tenth_Inches




////////////////////////////////////////////////////////////////
// Packet Structure for Comands to Arduino
#ifndef __ARDUINO_TARGET	// Arduino Compiler does not understand pack
#pragma pack( 1 )
#endif

typedef struct
{
	//BYTE Sync0;
	//BYTE Sync1;
	BYTE Cmd;
	BYTE Param1;
	BYTE Param2;
	BYTE Param3;
	BYTE Param4;
	//BYTE TermChar;
} ARDUINO_CMD_T;
#define ARDUINO_CMD_SIZE 5	// 5 bytes
#define PIC_CMD_MSG_SIZE (ARDUINO_CMD_SIZE + 3) // bytes

#ifndef __ARDUINO_TARGET
#pragma pack( 4 )
#endif


#define SIO_SYNC_0							'Z' 	// Serial Command Sync characters
#define SIO_SYNC_1							'Z'
#define CMD_TERM_CHAR						0xC4	// Serial Command termination character (use for check)
#define SERIAL_CMD_SIZE 					   8	// Fixed length of a command from the Host to the Arduino

/*
#define LED_EYES_OFF						0x00
#define LED_EYES_ON							0x01
#define LED_EYES_CLOSE						0x02
#define LED_EYES_OPEN						0x03
#define LED_EYES_BLINK						0x04
#define LED_EYE_BRIGHTNESS_MAX				  19	// On time in 20ms cycle
*/





#endif	//__ROBOT_HW_INTERFACE_LOKI_ARDUINO_H__
