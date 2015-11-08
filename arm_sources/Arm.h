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
  /// Extend vertically the arm
  void extendVertical();
  
private:  // Private methods
  void angleCmd(Command _cmd);
  void globalCmd(Command _cmd);
  void specialCmd(Command _cmd);
private:  // Members
  Servo mBaseRot;
  Servo mExtender0, mExtender1, mExtender2, mExtender3;
  Servo mHandRot;
  Servo mHandGrab;

  int mThetas[7];
  int mThetasTarget[7];

  int mMaxSpeed = 1;

private:  // Hardware configuration
  // Servo pints.
  const int cPinBaseRot   = 3;
  const int cPinExtender0 = 5;
  const int cPinExtender1 = 6;
  const int cPinExtender2 = 9;
  const int cPinExtender3 = 10;
  const int cPinHandRot   = 11;
  const int cPinHandGrab  = 13;

  // Geometric data.
  const float a1 = 83;
  const float a2 = 177;
  const float a3 = 75;
  const float a4 = 40;

};

#endif // ARM_H_

