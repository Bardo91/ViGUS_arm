//////////////////////////////////////////////
//                                          //
//                                          //
//                                          //
//                                          //
//////////////////////////////////////////////

#include "Arm.h"

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
void Arm::fkRotateBase(int _theta){
  mBaseRot.write(_theta);
}

//--------------------------------------------------------------------------------
void Arm::fkMoveExtender(int _theta0, int _theta1, int _theta2, int _theta3){
  mExtender0.write(_theta0);
  mExtender1.write(_theta1);
  mExtender2.write(_theta2);
  mExtender3.write(_theta3);
}

//--------------------------------------------------------------------------------
void Arm::fkRotateHand(int _theta){
  mHandRot.write(_theta);
}

//--------------------------------------------------------------------------------
void Arm::fkHandClosing(int _theta){
  mHandGrab.write(_theta);
}

