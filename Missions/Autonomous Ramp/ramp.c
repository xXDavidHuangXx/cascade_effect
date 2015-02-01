#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorF,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorD,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     motorE,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     motorG,        tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    l_arm,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    harvmaster,           tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    l_tilt,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_1,    r_arm,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo8,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    r_tilt,                 tServoStandard)

#include "JoystickDriver.c"
#include "./armControlHeader3.h"
#include "./basic_move_header.h"

void initializeRobot()
{
	put_arm_in_prelaunch_pos();
	hold_ball();
	return;
}

void waitForButton(bool button){
	while(!button){}
}
task main()
{
	//waitForStart();
	initializeRobot();
	set_shoulder_degree(60);
	set_catcher_tilt(255);
	//set_catcher_tilt(250);
	move_fwd(70, 2000);
	move_fwd_wait(40,80);
	set_shoulder_degree(52);
	move_fwd_wait(40,150);
	//set_catcher_tilt(255);
	move_bck_wait(50,150);
	set_catcher_tilt(250);
	//wait1Msec(4000);
	set_shoulder_degree(107);
	move_fwd_wait(30,115);
	set_shoulder_degree(107);
	set_catcher_tilt(0);
	set_shoulder_degree(107);
	move_bck_wait(50,50);
	set_shoulder_degree(107);
	move_lft(60, 61);

}
