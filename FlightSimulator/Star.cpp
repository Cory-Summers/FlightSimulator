#include "Star.h"

Kepler::Star::Star(std::string const & name, 
  Physics::StateVector const& vector, 
  Physics::StateElements const& elements, 
  Physics::RotationVector const& rotation,
  double const & mass, double const& radius, 
  double const & gm)
{ 
  m_st_vector   = vector;
  m_rotation    = rotation;
  m_radius = radius;
  m_mass   = mass;
  m_name   = name;
  this->mu = gm;
  
}

void Kepler::Star::Initialize()
{

}

void Kepler::Star::Update(double const dt)
{
  CalculateRotation(dt);
  
}
