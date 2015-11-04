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
 /* float matArray[12] = { 1,-1, 4, 
                        1, 4, -2, 
                        1, 4, 2, 
                        1,-1, 0};*/
  float matArray[9] = { 12,-51,4, 
                        6,167,-68, 
                        -4, 24, -41};
  Matrix<float> m43(matArray, 3,3);
  m43.show();
  Serial.println("---------");
  Matrix<float> Q,R;
  m43.decompositionQR_HH(Q,R);
  Q.show();
  R.show();
  Serial.println("---------");
  //pinv.show();
  delay(1000000);
}
