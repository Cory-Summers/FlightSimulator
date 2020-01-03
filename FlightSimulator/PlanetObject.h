#pragma once
#include "WorldObject.h"
namespace MVC::Render {
  class PlanetObject :
    public WorldObjectBase
  {
    using planet_ptr = std::shared_ptr<Kepler::Planet>;
  public:
    PlanetObject() {}
    PlanetObject(planet_ptr);
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    ~PlanetObject() override;
  };
};

