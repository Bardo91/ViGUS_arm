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

//--------------------------------------------------------------------------------
void Arm::inverseKinematics(float _x, float _y, float _z){

  
}

//--------------------------------------------------------------------------------
void Arm::jacobi(Matrix<float> &_j, float _t1, float _t2, float _t3, float _t4){
  _j = Matrix<float>(2,4);
  
  _j(0,0) = - 75*sin(_t1 + _t2 + _t3) - 40*sin(_t1 + _t2 + _t3 + _t4) - 177*sin(_t1 + _t2) - 83*sin(_t1);
  _j(0,1) = - 75*sin(_t1 + _t2 + _t3) - 40*sin(_t1 + _t2 + _t3 + _t4) - 177*sin(_t1 + _t2);
  _j(0,2) = - 75*sin(_t1 + _t2 + _t3) - 40*sin(_t1 + _t2 + _t3 + _t4);
  _j(0,3) = -40*sin(_t1 + _t2 + _t3 + _t4);
  _j(1,0) = 75*cos(_t1 + _t2 + _t3) + 40*cos(_t1 + _t2 + _t3 + _t4) + 177*cos(_t1 + _t2) + 83*cos(_t1);
  _j(1,1) = 75*cos(_t1 + _t2 + _t3) + 40*cos(_t1 + _t2 + _t3 + _t4) + 177*cos(_t1 + _t2);
  _j(1,2) = 75*cos(_t1 + _t2 + _t3) + 40*cos(_t1 + _t2 + _t3 + _t4);
  _j(1,3) = 40*cos(_t1 + _t2 + _t3 + _t4);
}

//--------------------------------------------------------------------------------
void Arm::pinvJacobi(Matrix<float> &_pinvJ, float _t1, float _t2, float _t3, float _t4){
  _pinvJ = Matrix<float>(4,2);

  _pinvJ(0,0) = ((367275*sin(_t1 - _t3))/2 - 177000*sin(_t1 + _t2 + 2*_t3 + _t4) - 195880*sin(_t1 + 2*_t2 + _t3 + _t4) - (866769*sin(_t1 + 2*_t2))/2 - 20000*sin(_t1 + _t2 + _t3 + 2*_t4) + 83000*sin(_t1 - _t4) + 20000*sin(_t1 + _t2 + _t3) + 88500*sin(_t1 + _t2 + _t4) + 97940*sin(_t1 + _t3 + _t4) - 94400*sin(_t1 + _t2 + 2*_t3 + 2*_t4) - 166000*sin(_t1 + 2*_t2 + 2*_t3 + _t4) - (331875*sin(_t1 + _t2 + 2*_t3))/2 + 88500*sin(_t1 + _t2 - _t4) - 367275*sin(_t1 + 2*_t2 + _t3) + (520675*sin(_t1 + _t2))/2 + (367275*sin(_t1 + _t3))/2 + 83000*sin(_t1 + _t4) - 66400*sin(_t1 + 2*_t2 + 2*_t3 + 2*_t4) + (1310819*sin(_t1))/2 - 155625*sin(_t1 + 2*_t2 + 2*_t3) + 97940*sin(_t1 - _t3 - _t4))/(27545625*cos(_t2 + 2*_t3) - 14691000*cos(_t2 - _t4) + 30483825*cos(2*_t2 + _t3) + 14160000*cos(_t3 + 2*_t4) + 62658000*cos(2*_t3 + _t4) + (71941827*cos(2*_t2))/2 + 58741875*cos(2*_t3) + 4500000*cos(2*_t4) + 5511200*cos(2*_t2 + 2*_t3 + 2*_t4) + 12916875*cos(2*_t2 + 2*_t3) + 33417600*cos(2*_t3 + 2*_t4) + 3320000*cos(_t2 + _t3 + 2*_t4) + 29382000*cos(_t2 + 2*_t3 + _t4) + 16258040*cos(2*_t2 + _t3 + _t4) - 3320000*cos(_t2 + _t3) - 14691000*cos(_t2 + _t4) - 16258040*cos(_t3 + _t4) - 43216025*cos(_t2) - 44643825*cos(_t3) - 76436000*cos(_t4) + 15670400*cos(_t2 + 2*_t3 + 2*_t4) + 13778000*cos(2*_t2 + 2*_t3 + _t4) - 302116927/2);
  _pinvJ(0,1) = -((367275*cos(_t1 - _t3))/2 - (866769*cos(_t1 + 2*_t2))/2 + 83000*cos(_t1 - _t4) + 20000*cos(_t1 + _t2 + _t3) + 88500*cos(_t1 + _t2 + _t4) + 97940*cos(_t1 + _t3 + _t4) - 94400*cos(_t1 + _t2 + 2*_t3 + 2*_t4) - 166000*cos(_t1 + 2*_t2 + 2*_t3 + _t4) - (331875*cos(_t1 + _t2 + 2*_t3))/2 + 88500*cos(_t1 + _t2 - _t4) - 367275*cos(_t1 + 2*_t2 + _t3) + (520675*cos(_t1 + _t2))/2 + (367275*cos(_t1 + _t3))/2 + 83000*cos(_t1 + _t4) - 66400*cos(_t1 + 2*_t2 + 2*_t3 + 2*_t4) + (1310819*cos(_t1))/2 - 155625*cos(_t1 + 2*_t2 + 2*_t3) + 97940*cos(_t1 - _t3 - _t4) - 20000*cos(_t1 + _t2 + _t3 + 2*_t4) - 177000*cos(_t1 + _t2 + 2*_t3 + _t4) - 195880*cos(_t1 + 2*_t2 + _t3 + _t4))/(27545625*cos(_t2 + 2*_t3) - 14691000*cos(_t2 - _t4) + 30483825*cos(2*_t2 + _t3) + 14160000*cos(_t3 + 2*_t4) + 62658000*cos(2*_t3 + _t4) + (71941827*cos(2*_t2))/2 + 58741875*cos(2*_t3) + 4500000*cos(2*_t4) + 5511200*cos(2*_t2 + 2*_t3 + 2*_t4) + 12916875*cos(2*_t2 + 2*_t3) + 33417600*cos(2*_t3 + 2*_t4) + 3320000*cos(_t2 + _t3 + 2*_t4) + 29382000*cos(_t2 + 2*_t3 + _t4) + 16258040*cos(2*_t2 + _t3 + _t4) - 3320000*cos(_t2 + _t3) - 14691000*cos(_t2 + _t4) - 16258040*cos(_t3 + _t4) - 43216025*cos(_t2) - 44643825*cos(_t3) - 76436000*cos(_t4) + 15670400*cos(_t2 + 2*_t3 + 2*_t4) + 13778000*cos(2*_t2 + 2*_t3 + _t4) - 302116927/2);
  _pinvJ(1,0) = -(120000*sin(_t1 + _t2 + _t3 + 2*_t4) + 1062000*sin(_t1 + _t2 + 2*_t3 + _t4) - 1175280*sin(_t1 + 2*_t2 + _t3 + _t4) + 1219353*sin(_t1 - _t2) - 2600307*sin(_t1 + 2*_t2) + 1101825*sin(_t1 - _t3) + 249000*sin(_t1 - _t4) - 636675*sin(_t1 + _t2 + _t3) - 531000*sin(_t1 + _t2 + _t4) + 587640*sin(_t1 + _t3 + _t4) + 566400*sin(_t1 + _t2 + 2*_t3 + 2*_t4) - 498000*sin(_t1 + 2*_t2 + 2*_t3 + _t4) + 995625*sin(_t1 + _t2 + 2*_t3) - 531000*sin(_t1 + _t2 - _t4) - 2203650*sin(_t1 + 2*_t2 + _t3) - 275560*sin(_t1 + _t2 + _t3 + _t4) - 2781378*sin(_t1 + _t2) + 1101825*sin(_t1 + _t3) + 249000*sin(_t1 + _t4) + 275560*sin(_t1 - _t2 - _t3 - _t4) - 132800*sin(_t1 + 2*_t2 + 2*_t3 + 2*_t4) + 3199982*sin(_t1) + 516675*sin(_t1 - _t2 - _t3) - 466875*sin(_t1 + 2*_t2 + 2*_t3) + 587640*sin(_t1 - _t3 - _t4))/(3*(55091250*cos(_t2 + 2*_t3) - 29382000*cos(_t2 - _t4) + 60967650*cos(2*_t2 + _t3) + 28320000*cos(_t3 + 2*_t4) + 125316000*cos(2*_t3 + _t4) + 71941827*cos(2*_t2) + 117483750*cos(2*_t3) + 9000000*cos(2*_t4) + 11022400*cos(2*_t2 + 2*_t3 + 2*_t4) + 25833750*cos(2*_t2 + 2*_t3) + 66835200*cos(2*_t3 + 2*_t4) + 6640000*cos(_t2 + _t3 + 2*_t4) + 58764000*cos(_t2 + 2*_t3 + _t4) + 32516080*cos(2*_t2 + _t3 + _t4) - 6640000*cos(_t2 + _t3) - 29382000*cos(_t2 + _t4) - 32516080*cos(_t3 + _t4) - 86432050*cos(_t2) - 89287650*cos(_t3) - 152872000*cos(_t4) + 31340800*cos(_t2 + 2*_t3 + 2*_t4) + 27556000*cos(2*_t2 + 2*_t3 + _t4) - 302116927));
  _pinvJ(1,1) = (1219353*cos(_t1 - _t2) - 2600307*cos(_t1 + 2*_t2) + 1101825*cos(_t1 - _t3) + 249000*cos(_t1 - _t4) - 636675*cos(_t1 + _t2 + _t3) - 531000*cos(_t1 + _t2 + _t4) + 587640*cos(_t1 + _t3 + _t4) + 566400*cos(_t1 + _t2 + 2*_t3 + 2*_t4) - 498000*cos(_t1 + 2*_t2 + 2*_t3 + _t4) + 995625*cos(_t1 + _t2 + 2*_t3) - 531000*cos(_t1 + _t2 - _t4) - 2203650*cos(_t1 + 2*_t2 + _t3) - 275560*cos(_t1 + _t2 + _t3 + _t4) - 2781378*cos(_t1 + _t2) + 1101825*cos(_t1 + _t3) + 249000*cos(_t1 + _t4) + 275560*cos(_t1 - _t2 - _t3 - _t4) - 132800*cos(_t1 + 2*_t2 + 2*_t3 + 2*_t4) + 3199982*cos(_t1) + 516675*cos(_t1 - _t2 - _t3) - 466875*cos(_t1 + 2*_t2 + 2*_t3) + 587640*cos(_t1 - _t3 - _t4) + 120000*cos(_t1 + _t2 + _t3 + 2*_t4) + 1062000*cos(_t1 + _t2 + 2*_t3 + _t4) - 1175280*cos(_t1 + 2*_t2 + _t3 + _t4))/(3*(55091250*cos(_t2 + 2*_t3) - 29382000*cos(_t2 - _t4) + 60967650*cos(2*_t2 + _t3) + 28320000*cos(_t3 + 2*_t4) + 125316000*cos(2*_t3 + _t4) + 71941827*cos(2*_t2) + 117483750*cos(2*_t3) + 9000000*cos(2*_t4) + 11022400*cos(2*_t2 + 2*_t3 + 2*_t4) + 25833750*cos(2*_t2 + 2*_t3) + 66835200*cos(2*_t3 + 2*_t4) + 6640000*cos(_t2 + _t3 + 2*_t4) + 58764000*cos(_t2 + 2*_t3 + _t4) + 32516080*cos(2*_t2 + _t3 + _t4) - 6640000*cos(_t2 + _t3) - 29382000*cos(_t2 + _t4) - 32516080*cos(_t3 + _t4) - 86432050*cos(_t2) - 89287650*cos(_t3) - 152872000*cos(_t4) + 31340800*cos(_t2 + 2*_t3 + 2*_t4) + 27556000*cos(2*_t2 + 2*_t3 + _t4) - 302116927));
  _pinvJ(2,0) = -(120000*sin(_t1 + _t2 + _t3 + 2*_t4) - 2124000*sin(_t1 + _t2 + 2*_t3 + _t4) - 587640*sin(_t1 + 2*_t2 + _t3 + _t4) + 2203650*sin(_t1 - _t3) + 249000*sin(_t1 - _t4) - 5336025*sin(_t1 + _t2 + _t3) + 1062000*sin(_t1 + _t2 + _t4) - 587640*sin(_t1 + _t3 + _t4) + 2506320*sin(_t1 + _t2 - _t3 - _t4) - 566400*sin(_t1 + _t2 + 2*_t3 + 2*_t4) - 498000*sin(_t1 + 2*_t2 + 2*_t3 + _t4) + 4699350*sin(_t1 + _t2 - _t3) - 1991250*sin(_t1 + _t2 + 2*_t3) + 1062000*sin(_t1 + _t2 - _t4) - 1101825*sin(_t1 + 2*_t2 + _t3) - 2781880*sin(_t1 + _t2 + _t3 + _t4) + 2557650*sin(_t1 + _t2) - 1101825*sin(_t1 + _t3) + 249000*sin(_t1 + _t4) + 275560*sin(_t1 - _t2 - _t3 - _t4) - 132800*sin(_t1 + 2*_t2 + 2*_t3 + 2*_t4) + 599675*sin(_t1) + 516675*sin(_t1 - _t2 - _t3) - 466875*sin(_t1 + 2*_t2 + 2*_t3) + 1175280*sin(_t1 - _t3 - _t4))/(3*(55091250*cos(_t2 + 2*_t3) - 29382000*cos(_t2 - _t4) + 60967650*cos(2*_t2 + _t3) + 28320000*cos(_t3 + 2*_t4) + 125316000*cos(2*_t3 + _t4) + 71941827*cos(2*_t2) + 117483750*cos(2*_t3) + 9000000*cos(2*_t4) + 11022400*cos(2*_t2 + 2*_t3 + 2*_t4) + 25833750*cos(2*_t2 + 2*_t3) + 66835200*cos(2*_t3 + 2*_t4) + 6640000*cos(_t2 + _t3 + 2*_t4) + 58764000*cos(_t2 + 2*_t3 + _t4) + 32516080*cos(2*_t2 + _t3 + _t4) - 6640000*cos(_t2 + _t3) - 29382000*cos(_t2 + _t4) - 32516080*cos(_t3 + _t4) - 86432050*cos(_t2) - 89287650*cos(_t3) - 152872000*cos(_t4) + 31340800*cos(_t2 + 2*_t3 + 2*_t4) + 27556000*cos(2*_t2 + 2*_t3 + _t4) - 302116927));
  _pinvJ(2,1) = (2203650*cos(_t1 - _t3) + 249000*cos(_t1 - _t4) - 5336025*cos(_t1 + _t2 + _t3) + 1062000*cos(_t1 + _t2 + _t4) - 587640*cos(_t1 + _t3 + _t4) + 2506320*cos(_t1 + _t2 - _t3 - _t4) - 566400*cos(_t1 + _t2 + 2*_t3 + 2*_t4) - 498000*cos(_t1 + 2*_t2 + 2*_t3 + _t4) + 4699350*cos(_t1 + _t2 - _t3) - 1991250*cos(_t1 + _t2 + 2*_t3) + 1062000*cos(_t1 + _t2 - _t4) - 1101825*cos(_t1 + 2*_t2 + _t3) - 2781880*cos(_t1 + _t2 + _t3 + _t4) + 2557650*cos(_t1 + _t2) - 1101825*cos(_t1 + _t3) + 249000*cos(_t1 + _t4) + 275560*cos(_t1 - _t2 - _t3 - _t4) - 132800*cos(_t1 + 2*_t2 + 2*_t3 + 2*_t4) + 599675*cos(_t1) + 516675*cos(_t1 - _t2 - _t3) - 466875*cos(_t1 + 2*_t2 + 2*_t3) + 1175280*cos(_t1 - _t3 - _t4) + 120000*cos(_t1 + _t2 + _t3 + 2*_t4) - 2124000*cos(_t1 + _t2 + 2*_t3 + _t4) - 587640*cos(_t1 + 2*_t2 + _t3 + _t4))/(3*(55091250*cos(_t2 + 2*_t3) - 29382000*cos(_t2 - _t4) + 60967650*cos(2*_t2 + _t3) + 28320000*cos(_t3 + 2*_t4) + 125316000*cos(2*_t3 + _t4) + 71941827*cos(2*_t2) + 117483750*cos(2*_t3) + 9000000*cos(2*_t4) + 11022400*cos(2*_t2 + 2*_t3 + 2*_t4) + 25833750*cos(2*_t2 + 2*_t3) + 66835200*cos(2*_t3 + 2*_t4) + 6640000*cos(_t2 + _t3 + 2*_t4) + 58764000*cos(_t2 + 2*_t3 + _t4) + 32516080*cos(2*_t2 + _t3 + _t4) - 6640000*cos(_t2 + _t3) - 29382000*cos(_t2 + _t4) - 32516080*cos(_t3 + _t4) - 86432050*cos(_t2) - 89287650*cos(_t3) - 152872000*cos(_t4) + 31340800*cos(_t2 + 2*_t3 + 2*_t4) + 27556000*cos(2*_t2 + 2*_t3 + _t4) - 302116927));
  _pinvJ(3,0) = (4*(45000*sin(_t1 + _t2 + _t3 + 2*_t4) - 84375*sin(_t1 + _t2 + _t3 - _t4) + 132750*sin(_t1 + _t2 + 2*_t3 + _t4) + 73455*sin(_t1 + 2*_t2 + _t3 + _t4) - 62250*sin(_t1 - _t4) - 45000*sin(_t1 + _t2 + _t3) + 132750*sin(_t1 + _t2 + _t4) + 73455*sin(_t1 + _t3 + _t4) - 313290*sin(_t1 + _t2 - _t3 - _t4) + 70800*sin(_t1 + _t2 + 2*_t3 + 2*_t4) + 31125*sin(_t1 + 2*_t2 + 2*_t3 + _t4) - 265500*sin(_t1 + _t2 - _t4) + 432110*sin(_t1 + _t2 + _t3 + _t4) - 70800*sin(_t1 + _t2) + 31125*sin(_t1 + _t4) - 34445*sin(_t1 - _t2 - _t3 - _t4) + 16600*sin(_t1 + 2*_t2 + 2*_t3 + 2*_t4) - 16600*sin(_t1) - 146910*sin(_t1 - _t3 - _t4)))/(3*(27545625*cos(_t2 + 2*_t3) - 14691000*cos(_t2 - _t4) + 30483825*cos(2*_t2 + _t3) + 14160000*cos(_t3 + 2*_t4) + 62658000*cos(2*_t3 + _t4) + (71941827*cos(2*_t2))/2 + 58741875*cos(2*_t3) + 4500000*cos(2*_t4) + 5511200*cos(2*_t2 + 2*_t3 + 2*_t4) + 12916875*cos(2*_t2 + 2*_t3) + 33417600*cos(2*_t3 + 2*_t4) + 3320000*cos(_t2 + _t3 + 2*_t4) + 29382000*cos(_t2 + 2*_t3 + _t4) + 16258040*cos(2*_t2 + _t3 + _t4) - 3320000*cos(_t2 + _t3) - 14691000*cos(_t2 + _t4) - 16258040*cos(_t3 + _t4) - 43216025*cos(_t2) - 44643825*cos(_t3) - 76436000*cos(_t4) + 15670400*cos(_t2 + 2*_t3 + 2*_t4) + 13778000*cos(2*_t2 + 2*_t3 + _t4) - 302116927/2));
  _pinvJ(3,1) = -(4*(132750*cos(_t1 + _t2 + _t4) - 45000*cos(_t1 + _t2 + _t3) - 62250*cos(_t1 - _t4) + 73455*cos(_t1 + _t3 + _t4) - 313290*cos(_t1 + _t2 - _t3 - _t4) + 70800*cos(_t1 + _t2 + 2*_t3 + 2*_t4) + 31125*cos(_t1 + 2*_t2 + 2*_t3 + _t4) - 265500*cos(_t1 + _t2 - _t4) + 432110*cos(_t1 + _t2 + _t3 + _t4) - 70800*cos(_t1 + _t2) + 31125*cos(_t1 + _t4) - 34445*cos(_t1 - _t2 - _t3 - _t4) + 16600*cos(_t1 + 2*_t2 + 2*_t3 + 2*_t4) - 16600*cos(_t1) - 146910*cos(_t1 - _t3 - _t4) - 84375*cos(_t1 + _t2 + _t3 - _t4) + 45000*cos(_t1 + _t2 + _t3 + 2*_t4) + 132750*cos(_t1 + _t2 + 2*_t3 + _t4) + 73455*cos(_t1 + 2*_t2 + _t3 + _t4)))/(3*(27545625*cos(_t2 + 2*_t3) - 14691000*cos(_t2 - _t4) + 30483825*cos(2*_t2 + _t3) + 14160000*cos(_t3 + 2*_t4) + 62658000*cos(2*_t3 + _t4) + (71941827*cos(2*_t2))/2 + 58741875*cos(2*_t3) + 4500000*cos(2*_t4) + 5511200*cos(2*_t2 + 2*_t3 + 2*_t4) + 12916875*cos(2*_t2 + 2*_t3) + 33417600*cos(2*_t3 + 2*_t4) + 3320000*cos(_t2 + _t3 + 2*_t4) + 29382000*cos(_t2 + 2*_t3 + _t4) + 16258040*cos(2*_t2 + _t3 + _t4) - 3320000*cos(_t2 + _t3) - 14691000*cos(_t2 + _t4) - 16258040*cos(_t3 + _t4) - 43216025*cos(_t2) - 44643825*cos(_t3) - 76436000*cos(_t4) + 15670400*cos(_t2 + 2*_t3 + 2*_t4) + 13778000*cos(2*_t2 + 2*_t3 + _t4) - 302116927/2));
}
