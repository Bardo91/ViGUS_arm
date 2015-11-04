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
 float matArray[6] = { 1,1.26,
              1, 1.82,
              1, 2.22};
  Matrix<float> m43(matArray, 3,2);
  /*float matArray[9] = { 12,-51,4, 
  6,167,-68, 
  -4, 24, -41};
  Matrix<float> m43(matArray, 3,3);*/
  m43.show();
  Serial.println("---------");
  Matrix<float> pinv = m43.pinv();
  pinv.show();
  delay(1000000);
}
