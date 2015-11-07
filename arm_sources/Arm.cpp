//////////////////////////////////////////////
//                                          //
//                                          //
//                                          //
//                                          //
//////////////////////////////////////////////

#include "Arm.h"
#include <Arduino.h>

//--------------------------------------------------------------------------------
void Arm::init(){
  mBaseRot.attach(cPinBaseRot);
  mExtender0.attach(cPinExtender0);
  mExtender1.attach(cPinExtender1);
  mExtender2.attach(cPinExtender2);
  mExtender3.attach(cPinExtender3);
  mHandRot.attach(cPinHandRot);
  mHandGrab.attach(cPinHandGrab);
}

//--------------------------------------------------------------------------------
int signo(int _var){
  if(_var < 0)
    return -1;
  else
    return 1;
}
//--------------------------------------------------------------------------------
void Arm::spin(){
  // 666 SO MANY CALCS
  int speed0 = (mThetaTarget0 - mTheta0);
  int speed1 = (mThetaTarget1 - mTheta1);
  int speed2 = (mThetaTarget2 - mTheta2);
  int speed3 = (mThetaTarget3 - mTheta3);
  int speed4 = (mThetaTarget4 - mTheta4);
  int speed5 = (mThetaTarget5 - mTheta5);
  int speed6 = (mThetaTarget6 - mTheta6);
  
  mTheta0 += abs(speed0) > mMaxSpeed ? signo(speed0)*mMaxSpeed : speed0;
  mTheta1 += abs(speed1) > mMaxSpeed ? signo(speed1)*mMaxSpeed : speed1;
  mTheta2 += abs(speed2) > mMaxSpeed ? signo(speed2)*mMaxSpeed : speed2;
  mTheta3 += abs(speed3) > mMaxSpeed ? signo(speed3)*mMaxSpeed : speed3;
  mTheta4 += abs(speed4) > mMaxSpeed ? signo(speed4)*mMaxSpeed : speed4;
  mTheta5 += abs(speed5) > mMaxSpeed ? signo(speed5)*mMaxSpeed : speed5;
  mTheta6 += abs(speed6) > mMaxSpeed ? signo(speed6)*mMaxSpeed : speed6;
  
  mBaseRot.write(mTheta0);
  mExtender0.write(mTheta1);
  mExtender1.write(mTheta2);
  mExtender2.write(mTheta3);
  mExtender3.write(mTheta4);
  mHandRot.write(mTheta5);
  mHandGrab.write(mTheta6);
}

//--------------------------------------------------------------------------------
void Arm::setMaxSpeed(int _maxSpeed){
 mMaxSpeed = _maxSpeed;
}

//--------------------------------------------------------------------------------
void Arm::home(){
  mTheta0 = 90;
  mTheta1 = 0;
  mTheta2 = 180;
  mTheta3 = 0;
  mTheta4 = 90;
  mTheta5 = 90;
  mTheta6 = 90;
}

//--------------------------------------------------------------------------------
void Arm::initialActionPose(){
  mTheta0 = 90;
  mTheta1 = 90;
  mTheta2 = 30;
  mTheta3 = 75;
  mTheta4 = 90;
  mTheta5 = 90;
  mTheta6 = 90;
}

