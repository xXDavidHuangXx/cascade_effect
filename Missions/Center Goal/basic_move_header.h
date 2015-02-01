//----------------------------------------------------------------------
// (C) MVMS RoboTechs FTC Team #8742
//  File Nmae : basic_move_header.h
//  Version   : 1.0
//  Function  : Implements basic move functions for the robot base
//----------------------------------------------------------------------

// Define motor mapping constants for movements
#define   MV_FWD  0xF
#define   MV_BCK  0x0
#define   MV_LFT  0x6
#define   MV_RHT  0x9
#define   TRN_LFT 0xA
#define   TRN_RHT 0x5

void reset_encoders() {
	nMotorEncoder[motorD]=0;
	nMotorEncoder[motorE]=0;
	nMotorEncoder[motorF]=0;
	nMotorEncoder[motorG]=0;
	wait1Msec(1);
}

void wheel_stop() {
	motor[motorD]=0;
	motor[motorE]=0;
	motor[motorF]=0;
	motor[motorG]=0;
}

void wheel_rotate_count( short power, unsigned int count, short clockWiseMap){
	reset_encoders();
	if (count > 0) {
		nMotorEncoderTarget[motorD] = count;
		nMotorEncoderTarget[motorE] = count;
		nMotorEncoderTarget[motorF] = count;
		nMotorEncoderTarget[motorG] = count;
	}
	motor[motorD] = (clockWiseMap%2) ? power : -power;
	clockWiseMap >>=1;
	motor[motorE] = (clockWiseMap%2) ? power : -power;
	clockWiseMap >>=1;
	motor[motorF] = (clockWiseMap%2) ? power : -power;
	clockWiseMap >>=1;
	motor[motorG] = (clockWiseMap%2) ? power : -power;
}

void wheel_rotate_count_wait( short power, unsigned int count, short clockWiseMap){
	reset_encoders();
	if (count > 0) {
		nMotorEncoderTarget[motorD] = count;
		nMotorEncoderTarget[motorE] = count;
		nMotorEncoderTarget[motorF] = count;
		nMotorEncoderTarget[motorG] = count;
	}
	motor[motorD] = (clockWiseMap%2) ? power : -power;
	clockWiseMap >>=1;
	motor[motorE] = (clockWiseMap%2) ? power : -power;
	clockWiseMap >>=1;
	motor[motorF] = (clockWiseMap%2) ? power : -power;
	clockWiseMap >>=1;
	motor[motorG] = (clockWiseMap%2) ? power : -power;
		while(nMotorRunState[motorD] != runStateIdle){}
		while(nMotorRunState[motorE] != runStateIdle){}
		while(nMotorRunState[motorF] != runStateIdle){}
		while(nMotorRunState[motorG] != runStateIdle){}
}
void move_bck_wait(short power, int mm) {
	int motor_turn_count = (mm*40)/9;
	wheel_rotate_count_wait(power,motor_turn_count,MV_BCK);
}

void move_fwd_wait(short power, int mm) {
	int motor_turn_count = (mm*40)/9;
	wheel_rotate_count_wait(power,motor_turn_count,MV_FWD);
}

void move_fwd(short power, int mm) {
	int motor_turn_count = (mm*40)/9;
	wheel_rotate_count_wait(power,motor_turn_count,MV_FWD);
}

void move_bck(short power, int mm) {
	int motor_turn_count = (mm*40)/9;
	wheel_rotate_count_wait(power,motor_turn_count,MV_BCK);
}

void move_rht(short power, int mm) {
	long motor_turn_count = mm*1600/315;
	wheel_rotate_count_wait(power,motor_turn_count,MV_RHT);
}

void move_lft(short power, int mm) {
	long motor_turn_count = mm*1600/315;
	wheel_rotate_count_wait(power,motor_turn_count,MV_LFT);
}

void turn_rht(short power, int degrees) {
	int motor_turn_count = (degrees*27);
	wheel_rotate_count_wait(power,motor_turn_count,TRN_RHT);
}

void turn_lft(short power, int degrees) {
	int motor_turn_count = (degrees*26);
	wheel_rotate_count_wait(power,motor_turn_count,TRN_LFT);
}

void turn_move( short power, unsigned int count, short clockWiseMap, int steering ){
	int l_power, r_power;

 if (((clockWiseMap!=MV_FWD)&&(clockWiseMap!=MV_BCK))||(steering <-100)||(steering>100))
    return;

 l_power = (power*(100+steering))/100;
 if (l_power>100)
   l_power = 100;

 r_power = (power*(100-steering))/100;
 if (r_power>100)
   r_power = 100;

	reset_encoders();
	if (count > 0) {
		nMotorEncoderTarget[motorD] = count;
		nMotorEncoderTarget[motorE] = count;
		nMotorEncoderTarget[motorF] = count;
		nMotorEncoderTarget[motorG] = count;
	}

	motor[motorD] = (clockWiseMap%2) ? l_power : -l_power;
	clockWiseMap >>=1;
	motor[motorE] = (clockWiseMap%2) ? r_power : -r_power;
	clockWiseMap >>=1;
	motor[motorF] = (clockWiseMap%2) ? l_power : -l_power;
	clockWiseMap >>=1;
	motor[motorG] = (clockWiseMap%2) ? r_power : -r_power;
}
