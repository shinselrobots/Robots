// HeadBehavior.cpp: Subset of Behavior Module for Head Control
// Head movements aim cameras, PIR sendors, and IR Range finders mounted in the head
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ClientOrServer.h"
#if ( ROBOT_SERVER == 1 )	// This module used for Robot Server only

#include <math.h>
//#include <MMSystem.h>	// For Sound functions
#include "Globals.h"
#include "module.h"
#include "thread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Macros and defines

DWORD dbgHeadTime = 0;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/***
void CBehaviorModule::HeadTiltTest( )
{


	// test code


	ROBOT_LOG( TRUE,"\n\nTESTING YtoTilt\n\n")


	double Tilt = m_pHeadControl->YtoTilt( 4.0 );
	ROBOT_LOG( TRUE,"For Y = 4.0, Target Tilt = -64.0,   Tilt = %3.1f, Delta = %3.1f\n", Tilt, (Tilt+64.0) )

	Tilt = m_pHeadControl->YtoTilt( 5.0 );
	ROBOT_LOG( TRUE,"For Y = 5.0, Target Tilt = -63.0,   Tilt = %3.1f, Delta = %3.1f\n", Tilt, (Tilt+63.0) )

	Tilt = m_pHeadControl->YtoTilt( 7.0 );
	ROBOT_LOG( TRUE,"For Y = 7.0, Target Tilt = -60.0,   Tilt = %3.1f, Delta = %3.1f\n", Tilt, (Tilt+60.0) )

	Tilt = m_pHeadControl->YtoTilt( 10.0 );
	ROBOT_LOG( TRUE,"For Y = 10.0, Target Tilt = -55.0,  Tilt = %3.1f, Delta = %3.1f\n", Tilt, (Tilt+55.0) )

	Tilt = m_pHeadControl->YtoTilt( 14.5 );
	ROBOT_LOG( TRUE,"For Y = 14.5, Target Tilt = -49.0,   Tilt = %3.1f, Delta = %3.1f\n", Tilt, (Tilt+49.0) )

	Tilt = m_pHeadControl->YtoTilt( 26.5 );
	ROBOT_LOG( TRUE,"For Y = 26.5, Target Tilt = -36.0,   Tilt = %3.1f, Delta = %3.1f\n", Tilt, (Tilt+36.0) )

	Tilt = m_pHeadControl->YtoTilt( 38.5 );
	ROBOT_LOG( TRUE,"For Y = 38.5, Target Tilt = -25.0,   Tilt = %3.1f, Delta = %3.1f\n", Tilt, (Tilt+25.0) )

	Tilt = m_pHeadControl->YtoTilt( 52.5 );
	ROBOT_LOG( TRUE,"For Y = 52.5, Target Tilt = -19.0,   Tilt = %3.1f, Delta = %3.1f\n", Tilt, (Tilt+19.0) )

	Tilt = m_pHeadControl->YtoTilt( 61.5 );
	ROBOT_LOG( TRUE,"For Y = 61.5, Target Tilt = -15.0,   Tilt = %3.1f, Delta = %3.1f\n", Tilt, (Tilt+15.0) )


	ROBOT_LOG( TRUE,"\n\n")

}

***/




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HandleHeadServoStatusUpdate
// Handle status update from the servos.
// Check Head Movement State Machine.  Only used with movements that have multiple steps
// Uses m_HeadMovementState to track progress
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Not implemented.  If desired, see LaserScannerBehavior.cpp for example


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HandleUserHeadMovementCmd
// Handle head move request from user.
// Send Command to tell camera to move Pan and Tilt. This command controls both Pan and Tilt
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CBehaviorModule::HandleUserHeadMovementCmd( WPARAM wParam, LPARAM lParam )
{
	//IGNORE_UNUSED_PARAM (lParam);

	int  m_nCameraPanTiltCmd = wParam;	// Tells info on movement direction
	int  nPanTiltIncrement = lParam*10;	// in TenthDegrees - (example: speed 5 = 50 tenthdegrees = 5.0 degrees)

	// lParam is the speed, but ignored for now
	//IGNORE_UNUSED_PARAM (lParam);

	// Set default to current position
	int NewPanPosition, NewTiltPosition, SideTilt;
	m_pHeadControl->GetHeadPosition( NewPanPosition, NewTiltPosition, SideTilt );

	// Convert command to servo movement	
	//int  nPanTiltIncrement = m_pHeadControl->GetUserHeadSpeed();	// in TenthDegrees - (example: speed 5 = 50 tenthdegrees = 5.0 degrees)
	
	switch( m_nCameraPanTiltCmd )  // Which direction to Pan/Tilt
	{
		case CAMERA_PAN_STOP:
		{
			m_pHeadControl->ReleaseOwner( HEAD_OWNER_USER_CONTROL );
			return;
		}
		case CAMERA_PAN_UP:
		{
			NewTiltPosition += nPanTiltIncrement;
			break;
		}
		case CAMERA_PAN_DOWN:
		{
			NewTiltPosition -= nPanTiltIncrement;
			break;
		}

		case CAMERA_PAN_LEFT:
		{
			NewPanPosition -= nPanTiltIncrement;
			break;
		}

		case CAMERA_PAN_RIGHT:
		{
			NewPanPosition += nPanTiltIncrement;
			break;
		}

		// Combo Pan/Tilt commands
		case CAMERA_PAN_UP_LEFT:
		{
			NewTiltPosition += nPanTiltIncrement;
			NewPanPosition -= nPanTiltIncrement;
			break;
		}
		case CAMERA_PAN_UP_RIGHT:
		{
			NewTiltPosition += nPanTiltIncrement;
			NewPanPosition += nPanTiltIncrement;
			break;
		}
		case CAMERA_PAN_DOWN_LEFT:
		{
			NewTiltPosition -= nPanTiltIncrement;
			NewPanPosition -= nPanTiltIncrement;
			break;
		}
		case CAMERA_PAN_DOWN_RIGHT:
		{
			NewTiltPosition -= nPanTiltIncrement;
			NewPanPosition += nPanTiltIncrement;
			break;
		}
		case CAMERA_PAN_ABS_CENTER:
		{
			NewTiltPosition = 0;
			NewPanPosition = 0;
			break;
		}
		default:
		{
			ROBOT_LOG( TRUE, "ERROR! Invalid Camera Pan Direction, m_nCameraPanTiltCmd = 0x%08lX\n", m_nCameraPanTiltCmd )
		}
		break;
	}

	m_pHeadControl->SetHeadSpeed( HEAD_OWNER_USER_CONTROL, SERVO_SPEED_MED, SERVO_SPEED_MED, SERVO_SPEED_MED );
	m_pHeadControl->SetHeadPosition( HEAD_OWNER_USER_CONTROL, NewPanPosition, NewTiltPosition, NOP );
	m_pHeadControl->ExecutePositionAndSpeed( HEAD_OWNER_USER_CONTROL );

}




#endif	// ROBOT_SERVER - This module used for Robot Server only