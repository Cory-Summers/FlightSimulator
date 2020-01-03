#pragma once
#include "Object.h"
#include <vector>

namespace Kepler {
  class Planet :
    public ObjectBase
  {
    friend class ObjectFactory;
  public:
    Planet() {}
    Planet(std::string const&, Physics::StateVector const&, Physics::RotationVector const &,
      double const&, double const &, ObjectBase *);
    void Initialize() override;
    void Update(double const) override;
    virtual ObjectType GetType() const override { return ObjectType::planet; }
  protected:
  };

}