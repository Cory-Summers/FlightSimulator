#pragma once
#include <memory>
#include <vector>
#include <initializer_list>
#include "Star.h"
#include "TimeControl.h"

namespace MVC {
  class Simulation
  {
    using object_ptr = std::shared_ptr<Kepler::ObjectBase>;
  public:
    Simulation();

  private:
    std::vector<object_ptr> m_natural_body;
    TimeController m_time;

  };
};

