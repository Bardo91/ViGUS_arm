//////////////////////////////////////////////
//                                          //
//                                          //
//                                          //
//                                          //
//////////////////////////////////////////////

#ifndef VECTOR_H_
#define VECTOR_H_

#include <assert.h>
#include <math.h>

template<typename Type_>
class vector{
public:
  vector();
  vector(unsigned _size);

  Type_ operator[](unsigned _i) const;
  Type_ &operator[](unsigned _i);

  unsigned size() const {return mSize;};

  void push_back(Type_ _data);
private:
  Type_ *mData;
  unsigned mSize;
  unsigned mReservedSize;
};

//----------------------------------------------------------------------------
template<typename Type_>
vector<Type_>::vector(){
  mData = new Type_[10];
}

//----------------------------------------------------------------------------
template<typename Type_>
vector<Type_>::vector(unsigned _size){
  mData = new Type_[_size];
}

//----------------------------------------------------------------------------
template<typename Type_>
Type_ vector<Type_>::operator[](unsigned _i) const{
  assert(_i < mSize);
  return mData[_i];
}

//----------------------------------------------------------------------------
template<typename Type_>
Type_ &vector<Type_>::operator[](unsigned _i){
  assert(_i < mSize);
  return mData[_i];
}

//----------------------------------------------------------------------------
template<typename Type_>
void vector<Type_>::push_back(Type_ _data){
  if(mSize == mReservedSize){
    Type_ *newPtr = new Type_[int(mReservedSize*sqrt(2))];
    memcpy(newPtr, mData, mSize);
    delete mData;
    mData = newPtr;
    newPtr = NULL;
  }    
    
  mData[mSize] = _data;
  mSize ++;
}
#endif  //   VECTOR_H_
