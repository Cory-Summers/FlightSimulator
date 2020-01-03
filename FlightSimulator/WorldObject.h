#pragma once
#include <memory>
#include "kepler-physics.h"
#include "planet-class.h"
namespace MVC::Render {
  class WorldObjectBase
  {
  public:
    WorldObjectBase() {}
    virtual void Initialize() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual ~WorldObjectBase() = 0;
  protected:
    std::weak_ptr<Kepler::ObjectBase> m_object;
    Physics::StateVector m_stVector;
  };
}
