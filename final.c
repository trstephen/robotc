#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    sprayPot,       sensorPotentiometer)
#pragma config(Sensor, in2,    far_lt_sensor,  sensorAnalog)
#pragma config(Sensor, in3,    far_rt_sensor,  sensorAnalog)
#pragma config(Sensor, in4,    near_lt_sensor, sensorAnalog)
#pragma config(Sensor, in5,    near_rt_sensor, sensorAnalog)
#pragma config(Sensor, dgtl1,  spray_button,   sensorTouch)
#pragma config(Sensor, dgtl2,  start_button,   sensorTouch)
#pragma config(Sensor, dgtl3,  debug_button,   sensorTouch)
#pragma config(Sensor, dgtl5,  far_rt_led,     sensorDigitalOut)
#pragma config(Sensor, dgtl6,  near_rt_led,    sensorDigitalOut)
#pragma config(Sensor, dgtl7,  neutralize_led, sensorDigitalOut)
#pragma config(Sensor, dgtl8,  near_lt_led,    sensorDigitalOut)
#pragma config(Sensor, dgtl9,  far_lt_led,     sensorDigitalOut)
#pragma config(Sensor, dgtl10, siren_trigger,  sensorDigitalOut)
#pragma config(Sensor, dgtl11, sonar,          sensorSONAR_cm)
#pragma config(Sensor, I2C_1,  I2C1,           sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port2,           rt_motor,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           lt_motor,      tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port10,          spray_motor,   tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
*	NEW DESCRIPTION REQUIRED FOR MILESTONE 4
*
*/

/*
======================================================
=
=	 				CONSTANTS
=
======================================================
*/

/*
////////////////////////
		motor speeds
////////////////////////
*/
const int FWD_SPEED = 60;		// forward speed
const int FWD_SPEED_NEAR = 40;
const int MIN_FWD_SPEED = 10;	// minimum allowable motor speed for forward motion
const int SWEEP_SPEED_FAST = 30; // wheel turn speed for fast sweeping
const int SWEEP_SPEED_SLOW = 25; // wheel turn speed for slow sweeping
const int SPRAY_SPEED = 30;		// spray motor speed
#define ONE_M_DIST 1750 		// encoder value for 1 meter


/*
////////////////////////
		turning
////////////////////////
*/
const int THREE_SIXTY_DEG = 1300; // encoder value for turning robot 360 deg
const float DEADBAND_LIMIT = 0.2; // go straight when bearing is < abs(deadband_limit)
#define TURN_SLOW 20	//when turning, inside wheel turns at this speed
#define TURN_FAST 35	//when turning, outside wheel turns at this speed
#define TURN_SLOW_NEAR 15
#define TURN_FAST_NEAR 30

/*
////////////////////////
		IR thresholds
////////////////////////
*/
#define IR_REFRESH_RATE 10	//gets new max/min values for IR readings (*10 miliseconds)
const int FAR_IR_TEST_THRESHOLD = 100;	// debug lights come on when far IR reading is above this value
const int NEAR_IR_TEST_THRESHOLD = 1900; // debug lights come on when near IR reading is above this value
const float FAR_IR_BALANCE_THRESHOLD = 0.20; // debug lights come on when scaled balance is less than this value
const float NEAR_IR_BALANCE_THRESHOLD = 0.25; // debug lights come on when scalaned balance is less than this value
#define FAR_IR_CEILING 800		// when far IR stronger than this value, switch to near IR
#define NEAR_IR_FLOOR 400 	// when near IR weaker than this value, switch to far IR

/*
////////////////////////
		IR sweep
////////////////////////
*/
#define SWEEP_SENSOR_THRESHOLD 100 //transition to slow sweep when left sensor is above this value
#define SWEEP_BALANCE_LIMIT 0.45

/*
////////////////////////
		sonar
////////////////////////
*/
const float MAX_SPEED_THRESHOLD = 100.0;	//max distance (cm) before sonar starts limiting wheel speed
const int STOPPING_DIST = 10;	// robot will stop when sonar detects objects within this dist (cm)

/*
////////////////////////
		neutralization
////////////////////////
*/
#define NUM_SPRAYS	3			// number of times to spray bottle
#define NEUTRALIZE_POSN_IR 2000 	// when near IR is stronger than this value...																	}
#define NEUTRALIZE_IR_BALANCE_TOLERANCE  400 // when diff between lt and rt sensors is less than this value...		} begin neutralization
#define NEUTRALIZE_POSN_SONAR 30	// and sonar detects an object close than this value...													}


/*
======================================================
=
=	 				FLAGS
=
======================================================
*/

bool start_button_pushed = false;
bool debug_button_pushed = false;
bool spray_button_pushed = false;


/*
======================================================
=
=	 			GLOBAL VARIABLES
=
======================================================
*/

//strength of signal for each IR phototransistor
//records difference between up-down cycle
int far_lt_IR, far_rt_IR,  near_lt_IR, near_rt_IR;

//recodes the difference between the left and right readings for sensor pairs
// < 0 indicates lt is stronger; > 0 indicates rt is stronger
int far_IR_balance, near_IR_balance;
float far_IR_balance_scaled, near_IR_balance_scaled;


/*
======================================================
=
=	 				STATES
=
======================================================
*/

//robot states
typedef enum{
	STANDBY=0,
	DEBUG,
	SEARCH,
	SEEK,
	NEUTRALIZE,
}T_State;

T_State current_state = STANDBY;	//start in standby mode

//sensor states
typedef enum{
	FAR=0,
	NEAR,
}T_Sensor;

T_Sensor active_sensor = FAR;//keeps track of which sensor is being used for guidance

/*
======================================================
=
=	 				PROTOTYPES
=
======================================================
*/

/*
* debug_sensors()
*	lights associated to each IR sensor will come on when they receive a signal
*	above a threshold value. when sonar is in the correct position, the center
*	LED comes on. this is controlled by debug_sensors_LED_control().
*	an additional button press will change into calibration mode.
*/
void debug_sensors();

/*
*	debug_sensors_LED_control();
* checks if the reading for an IR sensor is above a threshold value.
* if yes, an LED is turned on; if no, LED is turned off.
*/
void debug_sensor_LED_control(int IR_reading, int threshold, tSensors LED);

/*
*	calibrate_sensors()
*	when both sensors in a pair are above a threshold, the associated left LED comes on.
*	when their absolute balance is within a threshold, the associated right LED comes on.
*	the sonar LED comes on when it passes a threshold.
*/
void calibrate_sensors();

/*
*	blink_all()
* flashes all lights with a given delay
*	often used to after changing behavior to prevent immediately re-reading
*	the button press.
*/
void blink_all(int delay_time);

/*
*	monitor_input();
*	used to flag button inputs. prevents recognizing input, taking action
* and then reading again before button release.
*/
void monitor_input(tSensors button, bool flag);

/* 	stop_robot()
*		stops all motors and then waits for button input to change state
*/
void stop_robot();

/*	go_forward()
*		motors go forward until set counter is reached
*/
//void go_forward();

///* 	go_reverse()
//*		motors go backwards until set counter is reached
//*/
//void go_reverse();

///* 	turn_left()
//*		the robot turns 90 degrees left
//*/
//void turn_left();

///*	set_speed();
//*		takes a reading from front-facing sonar and uses it to create a bias for
//*		slowing the robot.
//*/
void set_speed(int* speed_adjust_ptr);

/*	activate_spray()
*		turns on the motor that controls the spray activation mechanism
*		the motor direction is switched depending on the reading of the angle potentiometer
*		loops for NUM_SPRAYS times
*		the potentiometer attached to the spray arm reads 0 when the arm is up and the
*		handle of the spray bottle is released. It reads around 150 when the spray
*		bottle handle is fully depressed.
*/
void activate_spray();

/*	sweep_search()
*	robot begins turning ccw. it slows when the left sensor senses IR and determines
*	the motor encoder value corresponding to the strongetst reading (i.e. a balanced and
* strong signal). the robot will turn itself back to the position with the best reading
*	and begin moving forward.
*	if no IR source is found, it just sits there and pouts ;_;
*/
void sweep_search();

//void seek_source();

/*	seek_source_reckoning()
*	seeks the IR source using dead reckoning (i.e. turn_linear() )for guidance
*/
void seek_source_reckoning();

/* turn_linear()
* a linear function which reads the scaled IR balance and
*	maps DEADBAND_LIMIT -> no turn, full deflection (i.e. +/- 1) -> maxium turn.
*	each wheel slows down independently, with inside wheel slowing faster
*	than outside wheel. the difference between the two values is the strength
*	of the turn.
*/
void turn_linear(int* inside_wheel, int* outside_wheel);



/*
======================================================
=
=	 				TASKS
=
======================================================
*/


task kill_switch()
/*
*	if any button is pressed, all motors are stopped and all other
*	tasks are stopped. even main().
*	main() is then restarted with default values for current_state and
*	kill_switch() ends.
*/
{
	wait1Msec(500);
	while(true)
	{
		//you can't stop a task from within a task (except main) so a helper function executes when this task runs
		//kill_switch_helper();
		if(SensorValue(start_button) == true || SensorValue(debug_button) == true || SensorValue(spray_button) == true) stopAllTasks();

		//prevent CPU hogging
		wait1Msec(50);
	}/*while*/

}/*kill_switch*/


task pulse()
/*
*	flashes all of the LEDs in a repeating pattern.
*	used to indicate the operation of the spray mechanism.
*	positioning of LEDs on robot is:
*
*			(*)						(*)						(*)						(*)						(*)
* 	far_lt_led 	near_lt_led	neutralize_led 	near_rt_led 	far_rt_led
*
*	the pattern loops to create the illusion of a pulse moving out from the centre
*/
{
	while(true)
	{
		wait1Msec(150);
		SensorValue(near_lt_led) = SensorValue(near_rt_led) = SensorValue(far_lt_led) = SensorValue(far_rt_led) = false;
		wait1Msec(10);
		SensorValue(neutralize_led) = true;
		wait1Msec(150);
		SensorValue(far_lt_led) = SensorValue(far_rt_led) = SensorValue(neutralize_led) = false;
		wait1Msec(10);
		SensorValue(near_lt_led) = SensorValue(near_rt_led) = true;
		wait1Msec(150);
		SensorValue(near_lt_led) = SensorValue(near_rt_led) = SensorValue(neutralize_led) = false;
		wait1Msec(10);
		SensorValue(far_lt_led) = SensorValue(far_rt_led) = true;
	}/*while*/
}/*pulse*/

task get_IR()
/*
* reads the value of both sets of phototransistor used for detecting IR.
* the task continuously reads voltage of the divider circuit and keeps track of the
*	max/min values it sees. every 100ms the max/min are written to global variables and then reset.
*
*												far			 near
*											-------		-------
*		bias resistor 	= 50k ohm		10k ohm
*		max detect dist = 300 cm		100 cm
*		min detect dist = 100 cm 		5 cm (full deflection)
*/
{
	int max_far_lt_IR, max_far_rt_IR, min_far_lt_IR, min_far_rt_IR, far_lt_IR_reading, far_rt_IR_reading;
	int max_near_lt_IR, max_near_rt_IR, min_near_lt_IR, min_near_rt_IR, near_lt_IR_reading, near_rt_IR_reading;

	//set initial values for comparison
	max_far_lt_IR = min_far_lt_IR = SensorValue(far_lt_sensor);
	max_far_rt_IR = min_far_rt_IR = SensorValue(far_rt_sensor);

	max_near_lt_IR = min_near_lt_IR = SensorValue(near_lt_sensor);
	max_near_rt_IR = min_near_rt_IR = SensorValue(near_rt_sensor);

	clearTimer(timer1);

	while(true)
	{
		//get lt/rt IR readings
		far_lt_IR_reading = SensorValue(far_lt_sensor);
		far_rt_IR_reading = SensorValue(far_rt_sensor);

		near_lt_IR_reading = SensorValue(near_lt_sensor);
		near_rt_IR_reading = SensorValue(near_rt_sensor);

		//compare against existing min/max values
		if(far_lt_IR_reading > max_far_lt_IR) max_far_lt_IR = far_lt_IR_reading;
		if(far_lt_IR_reading < min_far_lt_IR) min_far_lt_IR = far_lt_IR_reading;

		if(far_rt_IR_reading > max_far_rt_IR) max_far_rt_IR = far_rt_IR_reading;
		if(far_rt_IR_reading < min_far_rt_IR) min_far_rt_IR = far_rt_IR_reading;

		if(near_lt_IR_reading > max_near_lt_IR) max_near_lt_IR = near_lt_IR_reading;
		if(near_lt_IR_reading < min_near_lt_IR) min_near_lt_IR = near_lt_IR_reading;

		if(near_rt_IR_reading > max_near_rt_IR) max_near_rt_IR = near_rt_IR_reading;
		if(near_rt_IR_reading < min_near_rt_IR) min_near_rt_IR = near_rt_IR_reading;


		//every 100ms...
		if(time10[T1] % IR_REFRESH_RATE == 0)
		{
			//update global variables
			far_lt_IR = max_far_lt_IR - min_far_lt_IR;
			far_rt_IR = max_far_rt_IR - min_far_rt_IR;
			far_IR_balance = far_rt_IR - far_lt_IR;
			far_IR_balance_scaled = (float)(far_rt_IR - far_lt_IR) / (float)(far_rt_IR + far_lt_IR);

			near_lt_IR = max_near_lt_IR - min_near_lt_IR;
			near_rt_IR = max_near_rt_IR - min_near_rt_IR;
			near_IR_balance = near_rt_IR - near_lt_IR;
			near_IR_balance_scaled = (float)(near_rt_IR - near_lt_IR) / (float)(near_rt_IR + near_lt_IR);

			//reset max/min
			max_far_lt_IR = min_far_lt_IR = SensorValue(far_lt_sensor);
			max_far_rt_IR = min_far_rt_IR = SensorValue(far_rt_sensor);

			max_near_lt_IR = min_near_lt_IR = SensorValue(near_lt_sensor);
			max_near_rt_IR = min_near_rt_IR = SensorValue(near_rt_sensor);

			//pause to prevent overloading processor
			wait1Msec(10);
		}/*if*/
	}/*while*/
} /*get_far_IR*/

/*
======================================================
=
=	 				MAIN TASK
=
======================================================
*/

task main()
{
	while(true)
	{
		switch(current_state)
		{
			case(STANDBY):
				stop_robot();
				break;
			case(DEBUG):
				debug_sensors();
				break;
			case(SEARCH):
				startTask(kill_switch);
				sweep_search();
				break;
			case(SEEK):
				seek_source_reckoning();
				break;
			case(NEUTRALIZE):
				activate_spray();
				break;
			default:	//lol
		}/*switch*/
	}/* while */

}/*main*/

/*
======================================================
=
=	 				FUNCTIONS
=
======================================================
*/


void stop_robot()
{
	//stop motors
	motor(lt_motor) = motor(rt_motor) = motor(spray_motor) = 0;

	//turn off kill switch
	stopTask(kill_switch);

	//turn on standby LED
	SensorValue(neutralize_led) = true;

	//wait for button press
	while(current_state == STANDBY)
	{
		//monitor_input(start_button, start_button_pushed);
		//monitor_input(debug_button, debug_button_pushed);
		//monitor_input(spray_button, spray_button_pushed);

		if(SensorValue(start_button) && !start_button_pushed) start_button_pushed = true;
		if(SensorValue(debug_button) && !debug_button_pushed) debug_button_pushed = true;
		if(SensorValue(spray_button) && !spray_button_pushed) spray_button_pushed = true;


		if(start_button_pushed == true)
		{
			//start the magic~~~
			current_state = SEARCH;
			start_button_pushed = false;
		}/*if*/

		if(debug_button_pushed == true)
		{
			current_state = DEBUG;
			debug_button_pushed = false;
		}/*if*/

		//don't bother making a state for this, it's debug stuff
		if(spray_button_pushed == true)
		{
			activate_spray();
			spray_button_pushed = false;
		}/*if*/
	}/*while*/

	//turn off standby LED
	SensorValue(neutralize_led) = false;

}/* stop_robot */


/* WHY DOESN'T THIS WORK :C */
void monitor_input(tSensors button, bool flag)
{
	if(SensorValue(button) && flag == false)
	{
		flag = true;
	}/*if*/

}/*monitor_input*/


void debug_sensors()
{
	//wait 1s before beginning demo; prevents immediately triggering exit condition
	blink_all(1000);

	//activate sensors
	startTask(get_IR);

	//wait for exit button press
	while(!SensorValue(debug_button))
	{
		//set the flag for far or near sensors depending on the floor/ceiling conditions
		//switch to near mode when either far sensor goes above a ceiling
		if(active_sensor == FAR && (far_lt_IR > FAR_IR_CEILING || far_rt_IR > FAR_IR_CEILING))
		{
			active_sensor = NEAR;
		}/*if*/
		//switch to far mode if both near sensors drop below a floor
		if(active_sensor == NEAR && (near_lt_IR < NEAR_IR_FLOOR && near_rt_IR < NEAR_IR_FLOOR))
		{
			active_sensor = FAR;
		}/*if*/

		//check to see if LEDs need to be turned on/off
		debug_sensor_LED_control(far_lt_IR, FAR_IR_TEST_THRESHOLD, far_lt_led);
		debug_sensor_LED_control(far_rt_IR, FAR_IR_TEST_THRESHOLD, far_rt_led);
		debug_sensor_LED_control(near_lt_IR, NEAR_IR_TEST_THRESHOLD, near_lt_led);
		debug_sensor_LED_control(near_rt_IR, NEAR_IR_TEST_THRESHOLD, near_rt_led);

		//check for neutralization condition
		if(
			near_lt_IR > NEUTRALIZE_POSN_IR && near_rt_IR > NEUTRALIZE_POSN_IR //source is strong...
			&&
			SensorValue(sonar) < NEUTRALIZE_POSN_SONAR	//source is close...
			)
		{
					//detection confirmed!
					SensorValue(neutralize_led) = true;
		}
			else
		{
					//no detection :(
					SensorValue(neutralize_led) = false;
		}/*if-else*/

		//watch for button press to enter calibration mode
		if(SensorValue(start_button)) calibrate_sensors();

	}/*while*/

	//turn off sensors
	stopTask(get_IR);

	//say goodbye
	blink_all(500);
	current_state = STANDBY;

}/*debug_sensors*/


void debug_sensor_LED_control(int IR_reading, int threshold, tSensors LED)
{
	if(IR_reading > threshold)
	{
		SensorValue(LED) = true;
	}
	else
	{
		SensorValue(LED) = false;
	}/*if-else*/

}/*debug_sensor_LED_control*/


void calibrate_sensors()
{
	//blink lights to indicate calibration mode and prevent triggering exit condition
	blink_all(250);
	blink_all(250); //do it twice to differentiate it from the entry to debug mode

	//wait for escape buttons
	while(!SensorValue(debug_button) && !SensorValue(start_button))
	{
		//check to see if both far sensors are strong...
		if(far_lt_IR > FAR_IR_TEST_THRESHOLD && far_rt_IR > FAR_IR_TEST_THRESHOLD)
		{
			SensorValue(far_lt_led) = true;

			//... then check to see if balance is good
			if(abs(far_IR_balance_scaled) < FAR_IR_BALANCE_THRESHOLD)
			{
				SensorValue(far_rt_led) = true;
			}else{
				SensorValue(far_rt_led) = false;
			}/*if-else*/

		}
		else
		{
			SensorValue(far_lt_led) = false;
		}/*if-else*/

		//then repeat for the near sensors
		if(near_lt_IR > NEAR_IR_TEST_THRESHOLD && near_rt_IR > NEAR_IR_TEST_THRESHOLD)
		{
			SensorValue(near_lt_led) = true;
			if(abs(near_IR_balance_scaled) < NEAR_IR_BALANCE_THRESHOLD)
			{
				SensorValue(near_rt_led) = true;
			}else{
				SensorValue(near_rt_led) = false;
			}/*if-else*/
		}else{
			SensorValue(near_lt_led) = false;
		}/*if-else*/

		//finally, check sonar
		if(SensorValue(sonar) < NEUTRALIZE_POSN_SONAR)
		{
			SensorValue(neutralize_led) = true;
		}
		else
		{
			SensorValue(neutralize_led) = false;
		}/*if-else*/

	}/*while*/

	//say goodbye if going back to debug mode
	if(SensorValue(start_button))
	{
		blink_all(250);
		blink_all(250);
	}/*if*/

}/*calibrate_sensors*/


void blink_all(int delay_time)
{
		SensorValue(near_lt_led) = SensorValue(near_rt_led) = SensorValue(far_lt_led) = SensorValue(far_rt_led) = SensorValue(neutralize_led) = true;
		wait1Msec(delay_time);
		SensorValue(near_lt_led) = SensorValue(near_rt_led) = SensorValue(far_lt_led) = SensorValue(far_rt_led) = SensorValue(neutralize_led) = false;
		wait1Msec(delay_time);

}/*blink_all*/


void sweep_search()
{
	//turn on sensors and indicator LED
	startTask(get_IR);
	SensorValue(far_lt_led) = true;

	//turn ccw until lt sensor above threshold or 360 deg has been swept
	resetMotorEncoder(lt_motor);
	while(far_lt_IR < SWEEP_SENSOR_THRESHOLD && nMotorEncoder(lt_motor) > -THREE_SIXTY_DEG)
	{
		motor[lt_motor] = -SWEEP_SPEED_FAST;
		motor[rt_motor] = SWEEP_SPEED_FAST;
	}/*while*/

	//determine the next state based on exit condition of loop
	if(nMotorEncoder(lt_motor) <= -THREE_SIXTY_DEG)
	{
		//robot did 360 spin and no detection
		//go back to standby
		stopTask(get_IR);
		current_state = STANDBY;
	}
	else
	{
		//sweep slowly and determine when the source is centered
		motor[lt_motor] = -SWEEP_SPEED_SLOW;
		motor[rt_motor] = SWEEP_SPEED_SLOW;

		//initialize variables
		int max_bearing_score = 0;
		int bearing_score, max_bearing_encoder_value;

		//loop until bearing is strong right or 360 spin complete
		while(far_IR_balance_scaled < SWEEP_BALANCE_LIMIT && nMotorEncoder(lt_motor) > -THREE_SIXTY_DEG)
		{
			//high score occurs when signal is balanced (i.e. far_IR_balance_scaled = 0) and signal is strong
			bearing_score = (1 - abs(far_IR_balance_scaled)) * (far_lt_IR + far_rt_IR);
			if(bearing_score > max_bearing_score)
			{
				max_bearing_score = bearing_score;
				max_bearing_encoder_value = nMotorEncoder[lt_motor];
			}/*for*/
		}/*while*/

		//briefly pause before reorienting to prevent sliding
		motor[lt_motor] = motor[rt_motor] = 0;
		wait1Msec(150);

		//let me know if 360 deg was reached; useful for debugging behavior
		if(nMotorEncoder(lt_motor) <= -THREE_SIXTY_DEG) SensorValue(far_rt_led) = true;

		//reorient to bearing with highest score
		while(nMotorEncoder(lt_motor) < max_bearing_encoder_value)
		{
			//turn cw
			motor[lt_motor] = SWEEP_SPEED_SLOW;
			motor[rt_motor] = -SWEEP_SPEED_SLOW;
		}/*while*/

		motor[lt_motor] = motor[rt_motor] = 0;

		current_state = SEEK; //go get it, champ!
	}/*if-else*/

	//turn off indicator LEDs
	SensorValue(far_lt_led) = SensorValue(far_rt_led) = false;

}/*sweep_search*/


void seek_source_reckoning()
{
	//turn on sensors and indicator light
	startTask(get_IR);
	SensorValue(far_lt_led) = true;
	active_sensor = FAR;

	//declarations
	float IR_balance = 0.0;
	int lt_motor_speed, rt_motor_speed = 0;
	int current_forward_speed;
	tSensors balance_led;

	//navigate until robot has closed to an object
	while(SensorValue(sonar) >= 20 || active_sensor == FAR)
	{
		//check if we're close enough to switch to near sensors
		if(far_lt_IR > FAR_IR_CEILING || far_rt_IR > FAR_IR_CEILING)
		{
			active_sensor = NEAR;
			SensorValue(near_lt_led) = true;
		}/*if*/

		//determine variables based on which sensor is active
		if(active_sensor == FAR)
		{
			IR_balance = far_IR_balance_scaled;
			balance_led = far_rt_led;
			current_forward_speed = FWD_SPEED;
		}
		else //use near
		{
			IR_balance = near_IR_balance_scaled;
			balance_led = near_rt_led;
			current_forward_speed = FWD_SPEED_NEAR;
		}/*if-else*/

		//turn based on feedback from IR balance
		if(IR_balance <= -DEADBAND_LIMIT)
		{
			//turn left
			turn_linear(&rt_motor_speed, &lt_motor_speed);
			SensorValue(balance_led) = false;
		}
		else if(IR_balance >= DEADBAND_LIMIT)
		{
			//turn right
			turn_linear(&lt_motor_speed, &rt_motor_speed);
			SensorValue(balance_led) = false;
		}
		else
		{
			//IR is balanced, go straight
			lt_motor_speed = rt_motor_speed = current_forward_speed;
			SensorValue(balance_led) = true;
		}/*if-else*/

		//update motors with new speed
		motor[lt_motor] = lt_motor_speed;
		motor[rt_motor] = rt_motor_speed;
	}/*while*/

	//just assume we're in the right position, for now
	motor[lt_motor] = motor[rt_motor] = 0;
	SensorValue(far_lt_led) = SensorValue(far_rt_led) = SensorValue(near_lt_led) = SensorValue(near_rt_led) = false;
	current_state = STANDBY;
	stopTask(get_IR);
}/*seek_source_reckoning*/


void turn_linear(int* inside_wheel, int* outside_wheel)
{
	float IR_balance, scale;
	int fast_speed, slow_speed;
	float full_deflection = 1.0 - DEADBAND_LIMIT;

	//determine constants based on which sensor is active
	if(active_sensor == FAR)
	{
		IR_balance = far_IR_balance_scaled;
		fast_speed = TURN_SLOW;
		slow_speed = TURN_FAST;
		scale = fast_speed - slow_speed;
	}
	else //use near sensors
	{
		IR_balance = near_IR_balance_scaled;
		fast_speed = TURN_FAST_NEAR;
		slow_speed = TURN_SLOW_NEAR;
		scale = fast_speed - slow_speed;
	}

	//a linear function which maps DEADBAND_LIMIT -> 1, full deflection (+/- 1) -> 0
	float turn_amount = ( 1.0 - (full_deflection - (abs(IR_balance) - DEADBAND_LIMIT)/full_deflection ));

	//inside wheel turns slow
	*inside_wheel = slow_speed + (int)(turn_amount * scale);

	//outside wheel turns fast
	*outside_wheel = fast_speed + (int)(turn_amount * scale);

}/*turn_linear_near*/


void set_speed(int* speed_adjust_ptr)
{
	//if sonar does not detect an object closer than threshold dist, go max speed
	if(SensorValue(sonar) > MAX_SPEED_THRESHOLD)
	{
		*speed_adjust_ptr = 0;
	}
	//if sonar detects an object closer than STOPPING_DIST, stop motors
	else if(SensorValue(sonar) <= STOPPING_DIST)
	{
		*speed_adjust_ptr = FWD_SPEED;
	}
	//otherwise, reduce speed proportional to dist from object
	else
	{
		*speed_adjust_ptr = (int)(abs(SensorValue(sonar) - MAX_SPEED_THRESHOLD) * ((FWD_SPEED - MIN_FWD_SPEED) / MAX_SPEED_THRESHOLD));
	}/*if-else*/
}/*set_speed*/


void activate_spray()
{
	//initialize variables
	int spray_pot_val = SensorValue(sprayPot);
	int i;

	//start the light show
	startTask(pulse);
	SensorValue(siren_trigger) = true;

	//spray the assigned number of times, then stop
	for(i = 0; i < NUM_SPRAYS; i++)
	{
		//depress handle
		while(spray_pot_val < 150)
		{
			spray_pot_val = SensorValue(sprayPot);
			motor(spray_motor) = SPRAY_SPEED;
		}/*while*/

		//release handle
		while(spray_pot_val > 0)
		{
			spray_pot_val = SensorValue(sprayPot);
			motor(spray_motor) = -SPRAY_SPEED;
		}/*while*/
	}/*for*/
	motor(spray_motor) = 0;

	//stop the light show
	stopTask(pulse);
	SensorValue(siren_trigger) = false;

	//celebrate your success by flashing the lights 5 times
	int j;
	for(j = 0; j < 5; j++) blink_all(250);

	current_state = STANDBY;

}/* activate_spray */
