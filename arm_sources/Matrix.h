/////////////////////////////////////////////////////////////////////////////////////////
//  BOVIL: core
//
//    Author: Pablo Raón Soria
//    Date: 2014-03-05
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_CORE_MATH_MATRIX_H_
#define _BOVIL_CORE_MATH_MATRIX_H_

#include <assert.h>
#include <math.h>
#include <string.h>
#include <Arduino.h>
//-----------------------------------------------------------------------------
template <typename type_> 
class Matrix{
public:   // Main interface
  Matrix();   // Default constructor
  Matrix(int _rows, int _cols);   // Empty matrix constructor
  Matrix(const type_* _mat, int _rows, int _cols);  // Full-defined matrix constructor
  Matrix(const Matrix& _mat);   // Copy constructor

  ~Matrix();    // De-constructor

  void show();

  type_* getMatrixPtr() const;
  int getWidth() const;
  int getHeight() const;

public: // Overloaded Operators
  type_& operator[](const int _index) const;
  type_& operator()(const int _i, const int _j);
  const type_& operator()(const int _i, const int _j) const;
  Matrix operator=(const Matrix& _mat);       // Assignement operator
  Matrix operator+(const Matrix& _mat) const;   // Add operator
  Matrix operator-(const Matrix& _mat) const;   // Sub operator
  Matrix operator*(const Matrix& _mat) const;   // Mul operator
  Matrix operator*(const type_ _scalar) const;    // Scalar operator
  Matrix operator/(const type_ _scalar) const;    // Scalar division
  Matrix operator^(const double _exp) const;    // Pow operator     666 TODO:

public: // Other operations 666 TODO: Change names
  Matrix operator&(const Matrix& _mat) const;   // Projection operator._mat is projected to this
  Matrix transpose();               // Transpose operator
  type_ determinant();              // Determinant operator

  Matrix block(int _i, int _j, int _rows, int _cols);
public:   // Various algorithms
  double norm();
  bool decompositionLU(Matrix& _L, Matrix& _U);
  bool decompositionCholesky(Matrix& _L, Matrix& _Lt);
  bool decompositionLDL(Matrix& _L, Matrix& _D, Matrix& _Lt);
  bool decompositionQR_HH(Matrix& _Q, Matrix& _R);    // QR decomposition using Householder reflexions algorithm.

  Matrix inverse();   // Using QR algorithm

  Matrix pinv();

private:  // Private interface
  int mRows, mCols;
  type_* mPtr;

};
//-----------------------------------------------------------------------------
//---------------- Other functions --------------------------------------------
template<typename type_>
Matrix<type_> createEye(int _n);

Matrix<float> createGivenRotation(int _n, int _i, int _j, float _theta);

//-----------------------------------------------------------------------------
// Inline implementation
//-----------------------------------------------------------------------------

template<typename type_>
Matrix<type_>::Matrix() : mRows(0),
mCols(0),
mPtr(NULL){
}

//-----------------------------------------------------------------------------
template<typename type_>
Matrix<type_>::Matrix(int _rows, int _cols) : mRows(_rows),
mCols(_cols),
mPtr(new type_[_cols*_rows])  {
  memset(mPtr, 0, sizeof(type_)* _cols * _rows);
}

//-----------------------------------------------------------------------------
template<typename type_>
Matrix<type_>::Matrix(const type_* _matPtr, int _rows, int _cols) : mRows(_rows),
mCols(_cols),
mPtr(new type_[_cols*_rows])  {
  for (int i = 0; i < _cols*_rows; i++){
    mPtr[i] = _matPtr[i];
  }
}

//-----------------------------------------------------------------------------
template<typename type_>
Matrix<type_>::Matrix(const Matrix<type_>& _mat) : mRows(_mat.mRows),
mCols(_mat.mCols),
mPtr(new type_[_mat.mCols*_mat.mRows]) {
  for (int i = 0; i < mCols*mRows; i++){
    mPtr[i] = _mat.mPtr[i];
  }
}

//-----------------------------------------------------------------------------
template<typename type_>
Matrix<type_>::~Matrix(){
  if (mPtr)
    delete[] mPtr;
}

//-----------------------------------------------------------------------------
template<typename type_>
void Matrix<type_>::show(){
  Serial.print("[");
  for(unsigned i = 0; i < mRows; i++){
    for(unsigned j = 0; j < mCols; j++){
      Serial.print(mPtr[i * mCols + j]);
      if(j != mCols -1)
        Serial.print(", \t");
    }
    if(i != mRows -1)
      Serial.print(";\n");
  }
  Serial.print("]\n");
}
//-----------------------------------------------------------------------------
template<typename type_>
type_* Matrix<type_>::getMatrixPtr() const{
  return mPtr;
}

//-----------------------------------------------------------------------------
template<typename type_>
int Matrix<type_>::getWidth() const{
  return mCols;
}

//-----------------------------------------------------------------------------
template<typename type_>
int Matrix<type_>::getHeight() const{
  return mRows;
}

//-----------------------------------------------------------------------------
//------------------------ Overloaded operators ------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template<typename type_>
type_& Matrix<type_>::operator[](int _index) const{
  return mPtr[_index];
}

//-----------------------------------------------------------------------------
template<typename type_>
type_& Matrix<type_>::operator()(int _i, int _j){
  return mPtr[_i * mCols + _j];
}

//-----------------------------------------------------------------------------
template<typename type_>
const type_& Matrix<type_>::operator()(int _i, int _j) const{
  return mPtr[_i * mCols + _j];
}

//-----------------------------------------------------------------------------
template<typename type_>
Matrix<type_> Matrix<type_>::operator= (const Matrix<type_>& _mat){
  if (this != &_mat){
    if (mRows != _mat.mRows || mCols != _mat.mCols){
      if (mPtr)
        delete[] mPtr;
      mRows = _mat.mRows;
      mCols = _mat.mCols;

      mPtr = new type_[mRows*mCols];
    }
    for (int i = 0; i < mCols*mRows; i++){
      mPtr[i] = _mat.mPtr[i];
    }
  }
  return *this;
}

//-----------------------------------------------------------------------------
template<typename type_>
Matrix<type_> Matrix<type_>::operator+ (const Matrix<type_>& _mat) const{
  assert(_mat.mCols == mCols || _mat.mRows == mRows);

  Matrix<type_> mat(mRows, mCols);

  for (int i = 0; i < mRows; i++){
    for (int j = 0; j < mCols; j++){
      mat(i, j) = (*this)(i, j) + _mat(i, j);
    }
  }

  return mat;
}

//-----------------------------------------------------------------------------
template<typename type_>
Matrix<type_> Matrix<type_>::operator- (const Matrix<type_>& _mat) const{
  assert(_mat.mCols == mCols || _mat.mRows == mRows);

  Matrix<type_> mat(mRows, mCols);

  for (int i = 0; i < mRows; i++){
    for (int j = 0; j < mCols; j++){
      mat(i, j) = (*this)(i, j) - _mat(i, j);
    }
  }

  return mat;
}

//-----------------------------------------------------------------------------
template<typename type_>
Matrix<type_> Matrix<type_>::operator* (const Matrix<type_>& _mat) const{
  assert(mCols == _mat.mRows);

  Matrix<type_> mat(mRows, _mat.mCols);

  for (int i = 0; i < mat.mRows; i++){
    for (int j = 0; j < mat.mCols; j++){
      mat(i, j) = 0;
      for (int k = 0; k < mCols; k++){
        mat(i, j) += (*this)(i, k) * _mat(k, j);
      }
    }
  }

  return mat;
}

//-----------------------------------------------------------------------------
template<typename type_>
Matrix<type_> Matrix<type_>::operator* (const type_ _scalar) const{

  Matrix<type_> mat(mRows, mCols);

  for (int i = 0; i < mRows; i++){
    for (int j = 0; j < mCols; j++){
      mat(i, j) = (*this)(i, j) * _scalar;
    }
  }

  return mat;
}

//-----------------------------------------------------------------------------
template<typename type_>
Matrix<type_>  Matrix<type_>::operator/(const type_ _scalar) const{    // Scalar division
  Matrix<type_> mat(mRows, mCols);

  for (int i = 0; i < mRows; i++){
    for (int j = 0; j < mCols; j++){
      mat(i, j) = (*this)(i, j) / _scalar;
    }
  }
  return mat;
}
//-----------------------------------------------------------------------------
template<typename type_>
Matrix<type_> Matrix<type_>::operator^(const double _exp) const{
  Matrix<type_> mat(*this);

  if (_exp < 0){
    mat = mat^-_exp;
    mat = mat.inverse();
  }
  else {
    for (int i = 0; i < mRows; i++){
      for (int j = 0; j < mCols; j++){
        mPtr[i*mCols + j] = pow(mPtr[i*mCols + j], _exp);
      }
    }
  }

  return mat;

}

//-----------------------------------------------------------------------------
//------------------------Other operators-------------------------------------
//-----------------------------------------------------------------------------
template<typename type_>
Matrix<type_> Matrix<type_>::operator&(const Matrix<type_>& _mat) const{
  // 666 TODO:
}

//-----------------------------------------------------------------------------
template<typename type_>
Matrix<type_> Matrix<type_>::transpose() {
  Matrix<type_> mat(mCols, mRows);

  for (int i = 0; i < mRows; i++){
    for (int j = 0; j < mCols; j++){
      mat(j, i) = (*this)(i, j);
    }
  }

  return mat;
}

//-----------------------------------------------------------------------------
template<typename type_>
type_ Matrix<type_>::determinant() {
  if (mCols == mRows){
    Matrix<type_> L(mRows, mCols), U(mRows, mCols);

    if (decompositionLU(L, U)){
      type_ det = U[0];
      for (int i = 1; i < mRows; i++){
        det *= U[i*mRows + i];
      }
      return det;
    }
  }

  return static_cast<type_>(0);
}

//-----------------------------------------------------------------------------
template<typename type_>
Matrix<type_> Matrix<type_>::block(int _i, int _j, int _rows, int _cols){
  Matrix<type_> res(_rows, _cols);
  for(unsigned i = _i ; i < _i+_rows; i++){
    for(unsigned j = _j; j< _j+_cols; j++){
      res(i-_i, j-_j) = (*this)(i,j);
    }
  }
  return res;
}

//-----------------------------------------------------------------------------
//-------------------------- Various algorithms -------------------------------
//------------------------------------------------------------------------------
template<typename type_>
double Matrix<type_>::norm(){   // 666 TODO: only true if vector, if not, is not max norm
  if (mRows != 1 && mCols != 1)
    assert(false);  // check dimensions

  int size = mRows > mCols ? mRows : mCols;

  double norm = 0;

  for (int i = 0; i < size; i++){
    norm += mPtr[i] * mPtr[i];
  }

  return sqrt(norm);
}

//------------------------------------------------------------------------------
template<typename type_>
bool Matrix<type_>::decompositionLU(Matrix& _L, Matrix& _U){
  if (_L.mCols != _U.mCols || _L.mCols != mCols ||
    _L.mRows != _U.mRows || _L.mRows != mRows){
    return false; // Bad matrix sizes
  }

  _U = Matrix<type_>(mPtr, mRows, mCols);

  for (int i = 0; i < mRows; i++){
    _L[i*mCols + i] = 1.0;  // Set de diagonals of L. Eye matrix
    for (int k = i + 1; k < mRows; k++){
      _L[k*mCols + i] = _U[k*mCols + i] / _U[i*mCols + i];
      for (int j = 0; j < mCols; j++){
        _U[k*mCols + j] = _U[k*mCols + j] - _U[i*mCols + j] * _L[k*mCols + i];
      }
    }
  }

  return true;
}

//-----------------------------------------------------------------------------
template<typename type_>
bool Matrix<type_>::decompositionQR_HH(Matrix<type_>& _Q, Matrix<type_>& _R){
  assert(mRows >= mCols);
  int t = 0;

  int dim = mRows > mCols ? mRows : mCols;
  _R = Matrix<type_>(getMatrixPtr(), mRows, mCols);
  _Q = createEye<type_>(dim);
  for(unsigned iter = 0;  iter < mCols; iter++){
    Matrix<type_> x = _R.block(0,iter,mRows,1);
    for (unsigned i = 0; i < iter; i++) {
      x(i,0) = 0;
    }
    Matrix<type_> ei(x.getHeight(),1);
    ei(iter,0) = 1;
    Matrix<type_> u = x + ei*x.norm()*(x(0,0)>0?-1:1);
    u = u/u.norm();
    Matrix<type_> Hu = createEye<type_>(mRows) - u*u.transpose()*2;
    _R = Hu*_R;
    _Q = _Q*Hu;
  }

  return true;
}
//-----------------------------------------------------------------------------
template<typename type_>
Matrix<type_> Matrix<type_>::inverse(){
  // 666 TODO: how to do inverse? try with gaussian elimination
  if (mCols != mRows)
    assert(false);


  Matrix<type_> matInv = createEye<type_>(mRows), mat(*this);

  // Inferior triangle elimination.
  for (int i = 0; i < mRows; i++){
    for (int k = i + 1; k < mRows; k++){
      double factor = mat(k, i) / mat(i, i);
      for (int j = 0; j < mCols; j++){
        mat(k, j) = mat(k, j) - mat(i, j) * factor;
        matInv(k, j) = matInv(k, j) - matInv(i, j) * factor;
      }
    }
  }

  // Superior triangle elimination.
  for (int i = mRows - 1; i > 0; i--){
    for (int k = i - 1; k >= 0; k--){
      double factor = mat(k, i) / mat(i, i);
      for (int j = mCols - 1; j >= 0; j--){
        mat(k, j) = (mat(k, j) - mat(i, j) * factor);
        matInv(k, j) = (matInv(k, j) - matInv(i, j) * factor);
      }
    }
  }

  for (int i = 0 ; i < mRows ; i++){
    for (int j = 0; j < mCols; j++){  // Unitarize the diagonal
      matInv(i, j) = matInv(i, j) / mat(i, i);
    }
  }

  return matInv;
}

//-----------------------------------------------------------------------------
template<typename type_>
Matrix<type_> Matrix<type_>::pinv(){
  assert(mRows >= mCols);

  Matrix Q,R;
  this->decompositionQR_HH(Q,R);
  Matrix R1(mCols, mCols);
  memcpy(R1.getMatrixPtr(), R.getMatrixPtr(), sizeof(type_)*mCols*mCols);
  R1 = R1.inverse();
  Matrix R2(mCols, mRows);
  for (unsigned i = 0; i < mCols; i++) {
    for (unsigned j = 0; j < mCols; j++) {
      R2(i,j) = R1(i,j);
    }
  }
  Matrix pinv=R2*Q.transpose();
  return pinv;
}

//-----------------------------------------------------------------------------
//---------------- Other functions --------------------------------------------
//-----------------------------------------------------------------------------
template<typename type_>
Matrix<type_> createEye(int _n){
  Matrix<type_> mat(_n, _n);

  for (int i = 0; i < _n; i++){
    mat[i * _n + i] = 1;
  }

  return mat;
}

#endif  // _BOVIL_CORE_MATH_MATRIX_H_
