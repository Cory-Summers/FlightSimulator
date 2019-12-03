#pragma once
#include "Object.h"
#include <vector>

namespace Kepler {
  class Planet :
    public ObjectBase
  {
  public:
    Planet();
    Planet(std::string const&, Physics::StateVector const&, Physics::RotationVector const &,
      double const&, double const &, ObjectBase *);
    void Initialize() override;
    void Update(double const) override;
  protected:
  };

}