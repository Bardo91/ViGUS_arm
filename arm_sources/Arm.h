//////////////////////////////////////////////
//                                          //
//                                          //
//                                          //
//                                          //
//////////////////////////////////////////////

#ifndef ARM_H_
#define ARM_H_

#include <Servo.h>

const int cPinBaseRot   = 9;
const int cPinExtender0 = 10;
const int cPinExtender1 = 11;
const int cPinExtender2 = 12;
const int cPinExtender3 = 13;
const int cPinHandRot   = 14;
const int cPinHandGrab  = 15;

class Arm{
public:   // Public interface
  // Initialize arm harware and configuration.
  void init();

  // Forward Kinematic methods
  // Rotate base of the arm from 0 to 180.
  void fkRotateBase(int _theta);
  // Move extender servos. Each input from 0 to 180.
  void fkMoveExtender(int _theta0, int _theta1, int _theta2, int _theta3);
  // Rotate hand from 0 to 180
  void fkRotateHand(int _theta);
  // Move servo responsible of closing the hand from 0 to 180.
  void fkHandClosing(int _theta);  

  // Inverse Kinematicmethods
  
private:  // Private methods

private:  // Members
  Servo mBaseRot;
  Servo mExtender0, mExtender1, mExtender2, mExtender3;
  Servo mHandRot;
  Servo mHandGrab;
};

#endif // ARM_H_
