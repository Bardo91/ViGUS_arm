//////////////////////////////////////////////
//                                          //
//                                          //
//                                          //
//                                          //
//////////////////////////////////////////////

#include "Command.h"
#include <Arduino.h>
//--------------------------------------------------------------------------------
Command::Command(){
  
}

//--------------------------------------------------------------------------------
Command::Command(String _rawCommand){
  
}

//--------------------------------------------------------------------------------
bool Command::parse(String _raw){
  if(_raw[0] != '{')
    return false;
    
  _raw.toLowerCase();
  _raw = _raw.substring(1);  // Remove initial '{'
  eType type = parseType(_raw);
  switch(type){
    case cmdAngles:
      return parseAngles(_raw);
      break;
    case cmdGlobal:
      return parseGlobal(_raw);
      break;
    case cmdSpecial:
      return parseSpecial(_raw);
      break;
    case cmdError:
    default:
      return false;
      break;
  }
}

//--------------------------------------------------------------------------------
void Command::angles(int _t0, int _t1, int _t2, int _t3, int _t4, int _t5, int _t6){
  
}

//--------------------------------------------------------------------------------
void Command::global(float _x, float _y, float _z){
  
}

//--------------------------------------------------------------------------------
void Command::special(Command::eSpecialType _cmd){
  
}
//--------------------------------------------------------------------------------
const int* Command::angles() const{
  return mThetas;
}

//--------------------------------------------------------------------------------
// Private methods
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
Command::eType Command::parseType(String &_raw){
  String type = _raw.substring(0,_raw.indexOf(','));
  _raw = _raw.substring(_raw.indexOf(',')+1);
  if(type.equals("angles")){
    return cmdAngles;
  } else if(type.equals("global")){
    return cmdGlobal;
  } else if(type.equals("special")){
    return cmdSpecial;
  } else {
    return cmdError;
  }
}

//--------------------------------------------------------------------------------
bool Command::parseAngles(String &_raw){
  int nextComa;
  while((nextComa =_raw.indexOf(',')) != -1){
    String pair = _raw.substring(0, nextComa);
    String key = pair.substring(0,pair.indexOf(':'));
    String value = pair.substring(pair.indexOf(':')+1);
    _raw = _raw.substring(nextComa+1);
    if(key.toInt()>0 && key.toInt() < 8){
      mThetas[key.toInt() -1] = value.toInt();
    }else{
      mType = cmdError;
      return false;
    }
  }
}

//--------------------------------------------------------------------------------
bool Command::parseGlobal(String &_raw){
  int nextComa;
  while((nextComa =_raw.indexOf(',')) != -1){
    String pair = _raw.substring(0, nextComa);
    String key = pair.substring(0,pair.indexOf(':'));
    String value = pair.substring(pair.indexOf(':')+1);
    if(key.equals("x")){
      mX = value.toFloat();
    }else if(key.equals("y")){
      mY = value.toFloat();
    }else if(key.equals("z")){
      mZ = value.toFloat();
    }else{
      mType = cmdError;
      return false;
    }
  }
}

//--------------------------------------------------------------------------------
bool Command::parseSpecial(String &_raw){
  String specialCmd =_raw.substring(0,_raw.indexOf('}'));
  if(specialCmd.equals("home")){
    mSpecialType = espHome;
    return true;
  } else if(specialCmd.equals("initPos")){
    mSpecialType = espInitPos;
    return true;
  } else {
    mType = cmdError;
    return false;
  }
}

//--------------------------------------------------------------------------------
