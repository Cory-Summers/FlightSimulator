#pragma once
#include "cyrus-data.h"

namespace cyrus
{
  struct Object : public Data
  {
    Object() {}
    Object(string_ref id) : Data(id) {}
    std::list<std::shared_ptr<Data>> data;
  };
};