//////////////////////////////////////////////
//                                          //
//                                          //
//                                          //
//                                          //
//////////////////////////////////////////////

// Includes
#include "Arm.h"

Arm arm;

// Initializing .
void setup() {
  arm.init();
  Serial.begin(115200);
  arm.setMaxSpeed(5);
  arm.initialActionPose();
}

void loop() {
  arm.spin();
  delay(30);  
}

 
