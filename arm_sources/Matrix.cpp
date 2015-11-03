/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-04-22
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "Matrix.h"

//-----------------------------------------------------------------------------
Matrix<float> createGivenRotation(int _n, int _i, int _j, float _theta){
	Matrix<float>  mat = createEye<float>(_n);

	mat[_i*_n + _i] = cos(_theta);
	mat[_j*_n + _j] = cos(_theta);
	mat[_i*_n + _j] = sin(_theta);
	mat[_j*_n + _i] = -sin(_theta);

	return mat;
}
