#include "SimMessage.h"

SimMessage::SimMessage()
  : type(MsgType::MT_NULL)
  , hparam(0)
  , lparam(0)
  , data(nullptr)
{
}

SimMessage::SimMessage(TYPE type, HPARAM hparam, LPARAM lparam, DATPTR ptr)
  : type(type)
  , hparam(hparam)
  , lparam(lparam)
  , data(ptr)
{
}
