//----------------------------------------------------------------------
// (C) MVMS Robotechs Team #8742
//  File Nmae : arm_control_header.h
//  Version   : 1.0
//  Function  : Implements arm control functions
//----------------------------------------------------------------------

unsigned int cur_shoulder_degree;
unsigned int cur_catcher_tilt;

bool         do_safety_check = false;
bool         do_auto_correction = false;

unsigned int get_shoulder_degree(){
	return cur_shoulder_degree;
}

void set_shoulder( unsigned int degree){
	short time=0;

	if(degree<45){
		degree=45;
		}else if(degree>180){
		degree=180;
	}
	cur_shoulder_degree = degree;

	degree = ((184*degree)-7567)/100;
	servo[l_arm]=degree;
	servo[r_arm]=255-degree;

	while((unsigned int) ServoValue[l_arm]!=degree&&time<200){
		wait1Msec(10);
		time++;
	}
}

void set_shoulder_degree(unsigned int degree){
	//moves five until you need to go less than 2
	while(abs(cur_shoulder_degree-degree)>2){
		if(cur_shoulder_degree-degree>0){
			set_shoulder(cur_shoulder_degree-2);
			}else{
			set_shoulder(cur_shoulder_degree+2);
		}
	}
	//moves the rest
	if(cur_shoulder_degree-degree!=0)
		set_shoulder(degree);
}
void set_shoulder_degree_slow(unsigned int degree){
	//moves five until you need to go less than 2
	while(abs(cur_shoulder_degree-degree)>2){
		if(cur_shoulder_degree-degree>0){
			set_shoulder(cur_shoulder_degree-2);
			}else{
			set_shoulder(cur_shoulder_degree+2);
		}
			wait1Msec(10);
	}
	//moves the rest
	if(cur_shoulder_degree-degree!=0)
		set_shoulder(degree);
}

void set_catcher_tilt(short servopos){
	short time=0;
	servoChangeRate[r_tilt]=1;
	servoChangeRate[l_tilt]=1;
	servo[l_tilt]=servopos;
	servo[r_tilt]=255-servopos;
	cur_catcher_tilt = servopos;
	while(ServoValue[l_tilt]!=servopos&&time<200){
		wait1Msec(10);
		time++;
	}
}

void put_catcher_down(){
	servoChangeRate[r_tilt]=1;
	servoChangeRate[l_tilt]=1;
	servoChangeRate[r_arm]=1;
	servoChangeRate[l_arm]=1;
	set_shoulder(60);
	set_catcher_tilt(145);
	set_shoulder_degree(46);
}
void put_catcher_ground(bool button){
	if(button){
		set_catcher_tilt(145);
		set_shoulder_degree(46);
	}
}
void put_arm_in_prelaunch_pos(){
	servoChangeRate[r_tilt]=1;
	servoChangeRate[l_tilt]=1;
	servoChangeRate[r_arm]=1;
	servoChangeRate[l_arm]=1;
	//set_catcher_tilt(127);
	//set_shoulder_degree(90);
	set_catcher_tilt(255);
	set_shoulder_degree(47);
}

void drop_ball(){
	servo[harvmaster]=0;
}
void hold_ball(){
	servo[harvmaster]=127;
}
void get_ball(){
	servo[harvmaster]=255;
}

void drop_ball_in_30cm_goal(){
	get_ball();
	set_shoulder_degree(55);

	set_catcher_tilt(255);

	set_shoulder_degree(90);

	set_catcher_tilt(70);
	drop_ball();
}


void resetArmTilt()
{
	if(joy1Btn(8) == 1)
	{
		set_catcher_tilt(250);
		wait1Msec(2000);
		set_shoulder_degree_slow(45);
		hold_ball();
	}
	return;
}
