#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  forward_button, sensorTouch)
#pragma config(Sensor, dgtl2,  turn_button,    sensorTouch)
#pragma config(Sensor, dgtl3,  spray_button,   sensorTouch)
#pragma config(Sensor, I2C_1,  I2C1,           sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port2,           lt_motor,      tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port3,           rt_motor,      tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
*	For milestone 2 the robot must do the following after a button press: 
*		1) go forward one meter;
*		2) turn 90 deg; and,
*		3) operate the neutralization mechanism
*
*	This code was thrown together very quickly and doesn't do much more than that
*/

/*
=================
 CONSTANTS
=================
*/

#define FWD_SPEED 50				// forward speed
#define TURN_SPEED 50				// turning speed
#define ONE_M_DIST 1750 		// encoder value for 1 meter
#define NINETY_DEGREES 230	// encoder value for turning robot 90 deg

/*
=================
 FLAGS
=================
*/

bool forward_button_pushed;
bool turn_button_pushed;
bool spray_button_pushed;
//bool test = false;

/*
=================
 STATES
=================
*/
typedef enum{
	STOPPED=0,
	FORWARD,
	TURN,
	SPRAY,
}T_State;

T_State current_state = STOPPED; // start in stopped state


/* monitorInput()
*
*  Used to flag button inputs
*       - this avoids errors caused by program recognizing input, taking action, and
*         reading input again before button is released
*/
void monitorInput()
{
  if(SensorValue(forward_button) && !forward_button_pushed)
  {
    forward_button_pushed = true;
  }
  if(SensorValue(turn_button) && !turn_button_pushed)
  {
    turn_button_pushed = true;
  }
  if(SensorValue(spray_button) && !spray_button_pushed)
  {
    spray_button_pushed = true;
  }
}/* monitorInput */

/* 	stop_robot()
*		stops all motors and then waits for button input to change state
*/
void stop_robot()
{
	//reset flags
	resetMotorEncoder(lt_motor);
	forward_button_pushed = turn_button_pushed = spray_button_pushed = false;

	//stop motors
	motor(lt_motor) = motor(rt_motor) = 0;

	//wait for button press
	while(current_state == STOPPED){
		monitorInput();
		if(forward_button_pushed == true)
		{
			current_state = FORWARD;
		}
		if(turn_button_pushed == true)
		{
			current_state = TURN;
		}
		if(spray_button_pushed == true)
		{
			current_state = SPRAY;
		}
	}/*while*/
}/* stop_robot() */

/*	go_forward()
*		motors go forward until set counter is reached
*/
void go_forward()
{
	//reset flags 
	resetMotorEncoder(lt_motor);
	forward_button_pushed = turn_button_pushed = spray_button_pushed = false;

	//run motors
	motor(lt_motor) = motor(rt_motor) = FWD_SPEED;

	//monitor encoder for max distance
	while (nMotorEncoder(lt_motor) < ONE_M_DIST)
		{
			//do nothing until value reached
		}; 

	current_state = STOPPED;
}/*go_forward*/

/* 	turn_left()
*		the robot turns 90 degrees left
*/
void turn_left()
{
	//reset flags
	resetMotorEncoder(lt_motor);
	forward_button_pushed = turn_button_pushed = spray_button_pushed = false;

	//engage motors
	motor(lt_motor) = (0 - TURN_SPEED); 	// go in reverse
	motor(rt_motor) = TURN_SPEED;			// go forward

	//monitor encoder for max distance
	while((0 - nMotorEncoder(lt_motor)) < NINETY_DEGREES)
		{
			 // just turn those wheels
		};

	current_state = STOPPED;
}/* turn_left */

/*	activate_spray()
*		turns on the motor that controls the spray activation mechanism
*		stops spraying when a condition is met
*/
void activate_spray()
{
	//reset flags
	forward_button_pushed = turn_button_pushed = spray_button_pushed = false;

	/*

		stuff happens~~~

	*/

	current_state = STOPPED;
}/* activate_spray */

task main()
{
	while(true)
	{
		switch(current_state)
		{
			case(STOPPED):
				stop_robot();
				break;
			case(FORWARD):
				go_forward();
				break;
			case(TURN):
				turn_left();
				break;
			case(SPRAY):
				activate_spray();
				break;
			default:	//lol
		}/*switch*/
	}/* while */

}/*main*/
