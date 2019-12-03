#include "planet-class.h"
#include "TimeControl.h"
Kepler::Planet::Planet(std::string const& name,
  Physics::StateVector const& vector,
  Physics::RotationVector const& rotation,
  double const& radius, 
  double const& gm,
  ObjectBase* parent)
{
  m_name        = name;
  m_st_vector   = vector;
  m_rotation    = rotation;
  m_radius      = radius;
  m_parent_body = parent;
  mu = gm;
  Initialize();
}

void Kepler::Planet::Initialize() 
{
}
void Kepler::Planet::Update(double const dt) {
  CalculateRotation(dt);
  CalculateMovement(dt);
}