//////////////////////////////////////////////
//                                          //
//                                          //
//                                          //
//                                          //
//////////////////////////////////////////////

#ifndef ARM_H_
#define ARM_H_

#include <Servo.h>
#include "Command.h"

const int cPinBaseRot   = 3;
const int cPinExtender0 = 5;
const int cPinExtender1 = 6;
const int cPinExtender2 = 9;
const int cPinExtender3 = 10;
const int cPinHandRot   = 11;
const int cPinHandGrab  = 13;

class Arm{
public:   // Public interface
  /// Initialize arm harware and configuration.
  void init();
  
  /// Run one iteration of robot movement.
  void spin();

  /// Set max speed in degrees/s
  void setMaxSpeed(int _maxSpeed);

  /// Set inputcommand as next target
  void command(Command &_cmd);
  
  // Other methods.
  /// Send Robot to home
  void home();

  /// Send Robot to initial stable position for action
  void initialActionPose();
  
private:  // Private methods
  void angleCmd(const Command &_cmd);
  void globalCmd(const Command &_cmd);
  void specialCmd(const Command &_cmd);
private:  // Members
  Servo mBaseRot;
  Servo mExtender0, mExtender1, mExtender2, mExtender3;
  Servo mHandRot;
  Servo mHandGrab;

  int mTheta0, mTheta1, mTheta2, mTheta3, mTheta4, mTheta5, mTheta6;
  int mThetaTarget0, mThetaTarget1, mThetaTarget2, mThetaTarget3, mThetaTarget4, mThetaTarget5, mThetaTarget6;

  int mMaxSpeed = 1;
};

#endif // ARM_H_

