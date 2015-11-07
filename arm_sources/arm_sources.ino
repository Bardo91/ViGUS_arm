// Includes
#include <Servo.h>
#include "Arm.h"
#include "Trajectory.h"
#include "Matrix.h"
#include "Command.h"

Arm arm;

// Initializing .
void setup() {
  arm.init();
  Serial.begin(115200);
  arm.setMaxSpeed(5);
  arm.initialActionPose();
}

String serialBuffer;
Command lastCmd;
void loop() {
  if(Serial.available()){
    Serial.println("Data available");
    while(Serial.available()){
      serialBuffer = Serial.readStringUntil('\n');
    }
    if(lastCmd.parse(serialBuffer)){
      Serial.println("Command parsed");
      const int *thetas = lastCmd.angles();
      for(unsigned i = 0; i < 7; i++){
        Serial.println(thetas[i]);
      }
      Serial.println("----------------");
    }
  }
  arm.spin();
}

 
