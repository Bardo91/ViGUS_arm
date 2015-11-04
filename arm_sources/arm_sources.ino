//////////////////////////////////////////////
//                                          //
//                                          //
//                                          //
//                                          //
//////////////////////////////////////////////

// Includes
#include <Servo.h>
#include "Arm.h"
#include "Matrix.h"

Arm arm;

// Initializing .
void setup() {
  //arm.init();
  Serial.begin(115200);
}

// Main loop.
void loop() {
  float matArray[6] = { 2,1,1,3,2,1};
  Matrix<float> m33(matArray, 3,2);
  m33.show();
  Serial.println("---------");
  Matrix<float> pinv=m33.pinv();
  //pinv.show();
  delay(1000000);
}
