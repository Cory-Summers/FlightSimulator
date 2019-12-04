#pragma once 
#include "cyrus-object.h"
#include <immintrin.h>
namespace cyrus
{
  enum class SectionType {
    unaviable = 0,
    star = 1,
    planet = 2,
    moon = 3,
    spacecraft = 4,
    misc   = 254,
    debris = 255
  };
  using object_ptr = std::shared_ptr<Object>;
  struct Section : public Data
  {
    Section() {}
    Section(string_ref name) : Data(name) {}
    std::list<object_ptr> objects;
    std::string name;
  };
  SectionType ParseSectionType(std::string const & name);
};