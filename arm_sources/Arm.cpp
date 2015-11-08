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
  for(unsigned i = 0; i < 7; i++){
    int speed = (mThetasTarget[i] - mThetas[i]);
    mThetas[i] += abs(speed) > mMaxSpeed ? signo(speed)*mMaxSpeed : speed;
  }
  
  mBaseRot.write(mThetas[0]);
  mExtender0.write(mThetas[1]);
  mExtender1.write(mThetas[2]);
  mExtender2.write(mThetas[3]);
  mExtender3.write(mThetas[4]);
  mHandRot.write(mThetas[5]);
  mHandGrab.write(mThetas[6]);
}

//--------------------------------------------------------------------------------
void Arm::setMaxSpeed(int _maxSpeed){
 mMaxSpeed = _maxSpeed;
}

//--------------------------------------------------------------------------------
void Arm::command(Command &_cmd){
  switch(_cmd.type()){
    case Command::cmdAngles:
      angleCmd(_cmd);
      break;
    case Command::cmdGlobal:
      break;
    case Command::cmdSpecial:
      specialCmd(_cmd);
      break;
    default:
      break;
  }
}
//--------------------------------------------------------------------------------
void Arm::home(){
  mThetasTarget[0] = 90;
  mThetasTarget[1] = 0;
  mThetasTarget[2] = 180;
  mThetasTarget[3] = 0;
  mThetasTarget[4] = 90;
  mThetasTarget[5] = 90;
  mThetasTarget[6] = 90;
}

//--------------------------------------------------------------------------------
void Arm::initialActionPose(){
  mThetasTarget[0] = 90;
  mThetasTarget[1] = 90;
  mThetasTarget[2] = 30;
  mThetasTarget[3] = 75;
  mThetasTarget[4] = 90;
  mThetasTarget[5] = 90;
  mThetasTarget[6] = 90;
}

//--------------------------------------------------------------------------------
void Arm::extendVertical(){
  mThetasTarget[0] = 90;
  mThetasTarget[1] = 75;
  mThetasTarget[2] = 10;
  mThetasTarget[3] = 180;
  mThetasTarget[4] = 90;
  mThetasTarget[5] = 90;
  mThetasTarget[6] = 90;
}

//--------------------------------------------------------------------------------
// Private methods
//--------------------------------------------------------------------------------

void Arm::angleCmd(Command _cmd){
  memcpy(mThetas, _cmd.angles(), sizeof(int)*7);
}

//--------------------------------------------------------------------------------
void Arm::globalCmd(Command _cmd){
  
}

//--------------------------------------------------------------------------------
void Arm::specialCmd(Command _cmd){
  Command::eSpecialType espType = _cmd.specialType();
  switch(espType){
    case Command::espHome:
      home();
      break;
    case Command::espInitActionPos:
      initialActionPose();
      break;
    case Command::espExtendVertical:
      extendVertical();
      break;
  }
}

