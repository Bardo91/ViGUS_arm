//////////////////////////////////////////////
//                                          //
//                                          //
//                                          //
//                                          //
//////////////////////////////////////////////

#ifndef COMMAND_H_
#define COMMAND_H_

#include <Arduino.h>

class Command{
public:   // Public Interface
  enum eType {cmdAngles, cmdGlobal, cmdSpecial, cmdError};
  enum eSpecialType {espHome, espInitPos};

  Command();
  Command(String _rawCommand);

  bool parse(String _raw);
  
  void angles(int _t0, int _t1, int _t2, int _t3, int _t4, int _t5, int _t6);
  void global(float _x, float _y, float _z);
  void special(eSpecialType _cmd);

  const int* angles() const;
  Command::eType type();
  Command::eSpecialType specialType();
  
private:  // Private methods
  eType parseType(String &_raw);
  bool parseAngles(String &_raw);
  bool parseGlobal(String &_raw);
  bool parseSpecial(String &_raw);
  
private:  // Members
  eType mType;
  eSpecialType mSpecialType;
  int mThetas[7];
  float mX, mY, mZ;
};

#endif  //  COMMAND_H_
