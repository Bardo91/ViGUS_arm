//////////////////////////////////////////////
//                                          //
//                                          //
//                                          //
//                                          //
//////////////////////////////////////////////

#ifndef ARM_H_
#define ARM_H_

#include <Servo.h>

const int cPinBaseRot   = 3;
const int cPinExtender0 = 5;
const int cPinExtender1 = 6;
const int cPinExtender2 = 9;
const int cPinExtender3 = 10;
const int cPinHandRot   = 11;
const int cPinHandGrab  = 13;

class Arm{
public:   // Public interface
  // Initialize arm harware and configuration.
  void init();
  
  // Run one iteration of robot movement.
  void spin();

  // Set max speed in degrees/s
  void setMaxSpeed(int _maxSpeed);

  // Forward Kinematic methods
  /// Rotate base of the arm from 0 to 180.
  void fkRotateBase(int _theta0);
  /// Move extender servos. Each input from 0 to 180.
  void fkMoveExtender(int _theta1, int _theta2, int _theta3, int _theta4);
  /// Rotate hand from 0 to 180
  void fkRotateHand(int _theta5);
  /// Move servo responsible of closing the hand from 0 to 180.
  void fkHandClosing(int _theta6);  

  // Inverse Kinematicmethods


  // Other methods.
  /// Send Robot to home
  void home();

  /// Send Robot to initial stable position for action
  void initialActionPose();

  /// Get current target.
  void target(float *_target);
  void position(float *_position);
private:  // Private methods

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
