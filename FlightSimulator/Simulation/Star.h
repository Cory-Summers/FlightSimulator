#pragma once
#include "Object.h"
#include "TimeControl.h"

namespace Kepler{
  class Star :
    public Kepler::ObjectBase
  {
    friend class ObjectFactory;
  public:
    Star() {}
    Star(
      std::string const&,
      Physics::StateVector   const&,
      Physics::StateElements const&,
      Physics::RotationVector const&,
      double const& mass,
      double const & radius,
      double const & gm
    );
    void Initialize() override;
    void Update(double const dt) override;
    ObjectType GetType() const override  {
      return ObjectType::star;
    }
    ~Star() override {}
  };
}

