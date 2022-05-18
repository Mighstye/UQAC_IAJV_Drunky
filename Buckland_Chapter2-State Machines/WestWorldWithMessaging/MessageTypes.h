#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_Threaten,
  Msg_Hello,
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 0:
    
    return "HiHoneyImHome"; 

  case 1:
    
    return "StewReady";

  case 2:

    return "Ugly Miner whatcha doin' in that saloon ! Retur' to ur land or imma hit you bad !";

  case 3:

    return "Howdi everyone !";

  default:

    return "Not recognized!";
  }
}

#endif