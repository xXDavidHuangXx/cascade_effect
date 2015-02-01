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
#include "./arm_control_header.h"
#include "./basic_move_header.h"

void initializeRobot()
{
	hold_ball();
	put_catcher_ground(true);
	hold_ball();
	return;
}

void teleTilt(bool Y_pressed, bool A_pressed)
{
	static short timer = 0;

	if (!Y_pressed && !A_pressed) {
		timer=0;
		return;
	}

	if (timer>0) {
		timer--;
		return;
		} else {
		if (Y_pressed && A_pressed) {
			return;
		}
		if(Y_pressed){
			set_catcher_tilt(ServoValue[l_tilt]+1);
			timer=200;
			return;
		}
		if(A_pressed){
			set_catcher_tilt(ServoValue[l_tilt]-1);
			timer=200;
			return;
		}
	}
}

void teleArm(bool X_pressed, bool B_pressed)
{
	static short timer = 0;

	if (!X_pressed && !B_pressed) {
		timer=0;
		return;
	}

	if (timer>0) {
		timer--;
		return;
		} else {
		if (X_pressed && B_pressed) {
			return;
		}
		if(X_pressed){
			set_shoulder_degree(get_shoulder_degree()-1);
			timer=100;
			return;
		}
		if(B_pressed){
			set_shoulder_degree(get_shoulder_degree()+1);
			timer=100;
			return;
		}
	}
}
void teleHarvest(bool begin,bool back){
	static int timer=0;
	if(timer>0){
		timer--;
		return;
		}else{
		if(begin&&back){
			hold_ball();
			timer=100;
			return;
		}
		if(begin){
			drop_ball();
			return;
		}
		if(back){
			get_ball();
			return;
		}
	}
}

void teleMove(short x2,short y2, short x1, short y1, bool turnlft, bool turnrht, short tophat,short scale){
	const short epsilon=30;
	const short movespeed=40/scale;
	const short turnspeed=40/scale;
	const short sidespeed=30/scale;
	//if turnmove
	if(abs(y1)>epsilon&&abs(x1)>epsilon){
		//forward
		if(y1>0){
			if(x1>0){
				turn_move(50,0,0xF,50);
				}else{
				turn_move(50,0,0xF,-50);
			}
		}
		//backward
		else{
			if(x1>0){
				turn_move(50,0,0x0,50);
				}else{
				turn_move(50,0,0x0,-50);
			}
		}
		}else if(abs(y2)>epsilon){
		if(y2>epsilon){
			move_fwd(movespeed,0);
			}else if(y2<epsilon){
			move_bck(movespeed,0);
		}
		}else if(turnrht||turnlft){
		if(turnrht){
			turn_rht(turnspeed,0);
			}else if(turnlft){
			turn_lft(turnspeed,0);
		}
		}else if(tophat==6||tophat==2){
		if(tophat==6){
			move_lft(sidespeed,0);
		}
		if(tophat==2){
			move_rht(sidespeed,0);
		}
		}else{
		wheel_stop();
	}
}

void goal_set(short tophat){
	if(joy1Btn(1)==1){
		set_shoulder_degree(90);
		set_catcher_tilt(70);
	}
	if(joy1Btn(4)==1){
		set_shoulder_degree(115);
		set_catcher_tilt(20);
	}
}
task main()
{
	initializeRobot();
	set_shoulder_degree(60);
	while (true)
	{
		getJoystickSettings(joystick);
		if(joy1Btn(11)==1&&joy2Btn(11)==1){
			PlaySound(soundBeepBeep);
		}
		put_catcher_ground(joy1Btn(7)==1||joy2Btn(7)==1);
		put_catcher_60(joy1Btn(8)==1||joy2Btn(8)==1);
		teleArm(joy2Btn(2)==1,joy2Btn(4)==1);
		teleTilt(joy2Btn(1)==1,joy2Btn(3)==1);
		teleHarvest(joy2Btn(10)==1,joy2Btn(9)==1);
		//goal_set();
		if((abs(joystick.joy1_x2)+abs(joystick.joy1_y2)+abs(joystick.joy1_x1)+abs(joystick.joy1_y1)<10)&&joy1Btn(5)==0&&joy1Btn(6)==0&&joystick.joy1_TopHat!=6&&joystick.joy1_TopHat!=2){
			teleMove(joystick.joy2_x2,joystick.joy2_y2,joystick.joy2_x1,joystick.joy2_y1,joy2Btn(5)==1,joy2Btn(6)==1,joystick.joy2_TopHat,2);
		}else{
		teleMove(joystick.joy1_x2,joystick.joy1_y2,joystick.joy1_x1,joystick.joy1_y1,joy1Btn(5)==1,joy1Btn(6)==1,joystick.joy1_TopHat,1);
	}
		wait1Msec(1);
	}
}
