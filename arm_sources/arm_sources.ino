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
  Serial.begin(9600);
}

// Main loop.
void loop() {
  float matArray[9] = {  1.0, 3.0, 3.0, 
                          4.0, 51.0, 6.0, 
                          7.0, 84.0, 8.0 };
  Matrix<float> m33(matArray, 3, 3);
  Matrix<float> Q,R;
  m33.decompositionQR_GR(Q,R);
  Serial.println("---------");
  Serial.println(m33(0,0));
  Serial.println(m33(0,1));
  Serial.println(m33(0,2));
  Serial.println(m33(1,0));
  Serial.println(m33(1,1));
  Serial.println(m33(1,2));
  Serial.println(m33(2,0));
  Serial.println(m33(2,1));
  Serial.println(m33(2,2));

  Serial.println("---------");
  
  Serial.println(Q(0,0));
  Serial.println(Q(0,1));
  Serial.println(Q(0,2));
  Serial.println(Q(1,0));
  Serial.println(Q(1,1));
  Serial.println(Q(1,2));
  Serial.println(Q(2,0));
  Serial.println(Q(2,1));
  Serial.println(Q(2,2));
  Serial.println("---------");
  
  Serial.println(R(0,0));
  Serial.println(R(0,1));
  Serial.println(R(0,2));
  Serial.println(R(1,0));
  Serial.println(R(1,1));
  Serial.println(R(1,2));
  Serial.println(R(2,0));
  Serial.println(R(2,1));
  Serial.println(R(2,2));
  delay(100000);
}
