//////////////////////////////////////////////
//                                          //
//                                          //
//                                          //
//                                          //
//////////////////////////////////////////////

#include "Command.h"

//--------------------------------------------------------------------------------
Command::Command(){
  
}

//--------------------------------------------------------------------------------
Command::Command(String _rawCommand){
  
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
// Private methods
//--------------------------------------------------------------------------------
bool Command::parse(String _raw){
  eType type;
  if((type = parseType(_raw)) != error){
    switch(type){
      case angles:
        return parseAngles(_raw);
        break;
      case global:
        return parteGlobal(_raw);
        break;
      case special:
        return parseSpecial(_raw);
        break;
      case error:
      default:
        return false;
        break;
    }
  } else{
    return false;
  }
}

//--------------------------------------------------------------------------------
Command::eType Command::parseType(String &_raw){
  
}

//--------------------------------------------------------------------------------
bool Command::parteAngles(String &_raw){
  
}

//--------------------------------------------------------------------------------
bool Command::parteGlobal(String &_raw){
  
}

//--------------------------------------------------------------------------------
bool parseSpecial(String &_raw){
  
}

//--------------------------------------------------------------------------------
