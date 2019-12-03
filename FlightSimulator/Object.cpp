#include "Object.h"
#include <cmath>
#include <immintrin.h>
#include "kepler-physics.h"
#define _USE_MATH_DEFINES
Kepler::ObjectBase::ObjectBase() 
  : m_st_vector(),
    m_rotation(),
    m_mass(0.0)
{
}

Kepler::ObjectBase::ObjectBase(std::string const & name,Physics::StateVector const& vector, double const& mass) :
  m_name(name),
  m_st_vector(vector),
  m_mass(mass)
{

}

void Kepler::ObjectBase::CalculateRotation(double const & dt)
{
  m_rotation.r *= dt / m_radius;
  m_rotation.r  = { fmod(m_rotation.r[0], 1.0), fmod(m_rotation.r[1], 1.0), fmod( m_rotation.r[2], 1.0) };
}
void Kepler::ObjectBase::CalculateMovement(double const& dt)
{ 
  Physics::StateVector temp;
  double init_position = m_st_vector.p.Normalize();
  double init_velocity = m_st_vector.v.Normalize();
  double rad_velocity  = Vector3D::Dot(m_st_vector.p, m_st_vector.v) / init_position;
  double alpha = 2.0 / init_position - init_velocity * init_velocity / m_parent_body->mu;
  double uni_anom = Physics::UniversalKeplerEq(dt, init_position, rad_velocity, alpha, m_parent_body->mu);
  Physics::LagrangeCoeff coeff(uni_anom, dt, init_position, alpha, m_parent_body->mu);
  temp.p = coeff.f * m_st_vector.p + m_st_vector.v * coeff.g;
  coeff.Derive(uni_anom, temp.p.Normalize(), init_position, alpha, m_parent_body->mu);
  temp.v = coeff.df * m_st_vector.p + coeff.dg * m_st_vector.v;
  this->m_st_vector = temp;
}
void Kepler::CalculateMovement(Kepler::ObjectBase * obj, double const& dt)
{
  Physics::StateVector temp;
  Physics::StateVector m_st_vector = obj->GetVector();
  double mu = obj->GetParent()->GetMu();
  double init_position = m_st_vector.p.Normalize();
  double init_velocity = m_st_vector.v.Normalize();
  double rad_velocity = Vector3D::Dot(m_st_vector.p, m_st_vector.v) / init_position;
  double alpha = 2.0 / init_position - init_velocity * init_velocity / mu;
  double uni_anom = Physics::UniversalKeplerEq(dt, init_position, rad_velocity, alpha, mu);
  Physics::LagrangeCoeff coeff(uni_anom, dt, init_position, alpha, mu);
  temp.p = coeff.f * m_st_vector.p + m_st_vector.v * coeff.g;
  coeff.Derive(uni_anom, temp.p.Normalize(), init_position, alpha, mu);
  temp.v = coeff.df * m_st_vector.p + coeff.dg * m_st_vector.v;
  obj->SetVector(m_st_vector);
}
