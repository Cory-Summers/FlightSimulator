#pragma once
#include <list>
#include <memory>
#include "cyrus-section.h"

namespace cyrus{
  using section_ptr = std::shared_ptr<Section>;

  struct Container
  {
    Container() : sections() {}
    std::list<section_ptr> sections;
    
  };
};