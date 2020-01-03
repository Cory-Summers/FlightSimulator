#pragma once
#include "Object.h"
#include "planet-class.h"
#include "Star.h"
#include <nlohmann/json.hpp>

using JSON = nlohmann::json;
namespace Kepler {

    using object_ptr = std::shared_ptr<Kepler::ObjectBase>;
    using planet_ptr = std::shared_ptr<Kepler::Planet>;
    using star_ptr   = std::shared_ptr<Kepler::Star>;
    using object_vec = std::vector<object_ptr>;
  class ObjectFactory
  {
  public:

    static star_ptr   StarFactory(JSON &);
    static planet_ptr PlanetFactory(JSON &);
  };
};

