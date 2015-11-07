//////////////////////////////////////////////
//                                          //
//                                          //
//                                          //
//                                          //
//////////////////////////////////////////////

#include "Trajectory.h"

//--------------------------------------------------------------------------------
void parabola2d(float _x1[2], float _x2[2], unsigned _nPoints, float *_result){
  
}

//--------------------------------------------------------------------------------
void line2d(float _x1[2], float _x2[2], unsigned _nPoints, float **_result){
  // Allocate new memory
  _result = new float*[2];
  _result[0] = new float[_nPoints];
  _result[1] = new float[_nPoints];

  // Assign points.
  float xStep = (_x2[0] - _x1[0])/_nPoints;
  float yStep = (_x2[1] - _x1[1])/_nPoints;
  for(unsigned i = 0; i < _nPoints; i++){
    _result[0][i] = _x1[0] + xStep*i;
    _result[1][i] = _x1[1] + yStep*i;
  }
}

