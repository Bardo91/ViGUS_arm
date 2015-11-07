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
  arm.setMaxSpeed(1);
  arm.extendVertical();
}

Command lastCmd;
void loop() {
  if(Serial.available()){
    String serialBuffer;
    Serial.println("Data available");
    serialBuffer = Serial.readStringUntil('\n');
    Serial.println(serialBuffer);
    if(lastCmd.parse(serialBuffer)){
      Serial.println("Command Parsed");
      arm.command(lastCmd);
    }
  }
  arm.spin();
  delay(10);
}

 
