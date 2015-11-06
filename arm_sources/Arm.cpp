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
void Arm::fkRotateBase(int _theta0){
  mThetaTarget0 = _theta0;
}

//--------------------------------------------------------------------------------
void Arm::fkMoveExtender(int _theta1, int _theta2, int _theta3, int _theta4){
  mThetaTarget1 = _theta1;
  mThetaTarget2 = _theta2;
  mThetaTarget3 = _theta3;
  mThetaTarget4 = _theta4;
}

//--------------------------------------------------------------------------------
void Arm::fkRotateHand(int _theta5){
  mThetaTarget5 = _theta5;
}

//--------------------------------------------------------------------------------
void Arm::fkHandClosing(int _theta6){
  mThetaTarget6 = _theta6;
}

//--------------------------------------------------------------------------------
void Arm::home(){
  fkRotateBase(90);
  fkMoveExtender(0,180,0,90);
  fkRotateHand(90);
  fkHandClosing(90);
}

//--------------------------------------------------------------------------------
void Arm::initialActionPose(){
  fkRotateBase(90);
  fkMoveExtender(90,30,75,90);
  fkRotateHand(90);
  fkHandClosing(90);
}

//--------------------------------------------------------------------------------
void Arm::target(float *_target){
  float target[7];
  _target[0] = mThetaTarget0;
  _target[1] = mThetaTarget1;
  _target[2] = mThetaTarget2;
  _target[3] = mThetaTarget3;
  _target[4] = mThetaTarget4;
  _target[5] = mThetaTarget5;
  _target[6] = mThetaTarget6;
}

//--------------------------------------------------------------------------------
void Arm::position(float* _position){
  float pos[7];
  _position[0] = mTheta0;
  _position[1] = mTheta1;
  _position[2] = mTheta2;
  _position[3] = mTheta3;
  _position[4] = mTheta4;
  _position[5] = mTheta5;
  _position[6] = mTheta6;
}
