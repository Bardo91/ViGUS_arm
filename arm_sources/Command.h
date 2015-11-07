//////////////////////////////////////////////
//                                          //
//                                          //
//                                          //
//                                          //
//////////////////////////////////////////////

#ifndef COMMAND_H_
#define COMMAND_H_

#include <String.h>

class Command{
public:   // Public Interface
  enum eType {angles, global, special, error};
  enum eSpecialType {home, initialActionPose};

  Command();
  Command(String _rawCommand);

  void angles(int _t0, int _t1, int _t2, int _t3, int _t4, int _t5, int _t6);
  void global(float _x, float _y, float _z);
  void special(eSpecialType _cmd);

private:  // Private methods
  eType parse(String _raw);
  bool parseType(String _raw);
  bool parteAngles(String _raw);
  bool parteGlobal(String _raw);
  bool parseSpecial(String _raw);
  
private:  // Members
  eType mType;
  int mTheta0, mTheta1, mTheta2, mTheta3, mTheta4, mTheta5, mTheta6;
  float mX, mY, mZ;
};

#endif  //  COMMAND_H_
