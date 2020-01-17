#pragma once
#include "Message.h"
#include "MessageTypes.h"
#include <cstdint>
enum MsgType : uint32_t
{
  MT_NULL = 0,
  MT_TIME,
  MT_CREATE,
  MT_DESTROY
};

struct SimMessage : public IMessage
{
private:
  using TYPE = MsgType;
  using HPARAM = uint16_t;
  using LPARAM = uint16_t;
  using DATPTR = void*;
public:
  SimMessage();
  SimMessage(TYPE, HPARAM = 0, LPARAM = 0, DATPTR = nullptr);
  TYPE type;
  HPARAM hparam;
  LPARAM lparam;
  DATPTR data;
};

