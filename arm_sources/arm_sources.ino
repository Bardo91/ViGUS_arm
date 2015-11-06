//////////////////////////////////////////////
//                                          //
//                                          //
//                                          //
//                                          //
//////////////////////////////////////////////

// Includes
#include <Servo.h>
#include "Arm.h"
#include "Trajectory.h"
#include "Matrix.h"

Arm arm;

// Initializing .
void setup() {
  arm.init();
  Serial.begin(115200);
  arm.setMaxSpeed(5);
  arm.initialActionPose();
}

// Main loop.
int rot1 = 0, rot2 = 0;

void loop() {
  //arm.fkRotateBase(0);
  //arm.fkMoveExtender(90,0,90,90);
  //arm.fkRotateHand(90);
  //arm.fkHandClosing(90);
  if(Serial.available()){
    char buffer[50];
    int index = 0;
    while(Serial.available()){
      buffer[index] = Serial.read() - '0';
      index++;
    }
    index--;
    int prod = 1, rot = 0;
    for(int i = index; i>=0; i--){
      rot += buffer[i]*prod;
      prod *= 10;
    }
    
    arm.fkMoveExtender(90,rot,75,90);
    Serial.println(rot);
  }
  arm.spin();
  delay(50);
}

 
