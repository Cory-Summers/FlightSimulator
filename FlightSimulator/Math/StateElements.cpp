#include "StateElements.h"
#include "kepler-physics.h"

#define _USE_MATH_DEFINES // for C++
#include <math.h>
#include <cmath>
Physics::StateVector::StateVector()
  : v(),
    p()
{

}

Physics::StateVector::StateVector(Vector3D const& velocity, 
                                  Vector3D const& position)
  : v(velocity),
    p(position)
{

}

Physics::StateVector::StateVector(StateVector const& rhs)
{
  Copy(rhs);
}

Physics::StateVector::~StateVector()
{
}

Physics::StateElements Physics::StateVector::ToStateElements(double const & mu) const
{
  StateElements temp;
  double init_position = this->p.Normalize();
  double init_velocity = this->v.Normalize();
  double vr = Vector3D::Dot(p, v) / init_position;
  Vector3D H = Vector3D::Cross(p, v);
  double h = H.Normalize();
  temp.incl = acos(H.z / h); // Calculates inclination of Orbit
  Vector3D N = Vector3D::Cross(Vector3D(0, 0, 1), H);
  double n = N.Normalize();
  if (n != 0) {
    temp.r_asc_node = acos(N.x / n);
    if (N.y < 0) {
      temp.r_asc_node = 2.0 * M_PI - temp.r_asc_node;
    }
  }
  else {
    temp.r_asc_node = 0;
  }

  Vector3D E = (1.0 / mu) * (((init_velocity * init_velocity) - mu / init_position) 
    * p - (init_position * vr * v));
  temp.ecc = E.Normalize();
  if (n != 0) {
    if (temp.ecc > 1e-10) {
      temp.arg_peri = acos(Vector3D::Dot(N, E) / n / temp.ecc);
      if (E.z < 0) {
        temp.arg_peri = 2.0 * M_PI - temp.arg_peri;
      }
    }
    else {
      temp.arg_peri = 0;
    }

  }
  else {
    temp.arg_peri = 0;
  }
  if (temp.ecc > 1e-10) {
    temp.true_anom = acos(Vector3D::Dot(E, p) / temp.ecc / init_position);
    if (vr < 0) {
      temp.true_anom = 2 * M_PI - acos(Vector3D::Dot(N, p));
    }
  }
  else {
    Vector3D CP = Vector3D::Cross(N, p);
    if (CP.z >= 0) {
      temp.true_anom = acos(Vector3D::Dot(N, p) / n / init_position);
    }
    else {
      temp.true_anom = 2 * M_PI - acos(Vector3D::Dot(N, p) / n / init_position);
    }
  }
  temp.semi_major = (h * h) / mu / (1 - (temp.ecc * temp.ecc));
  temp.ang_momen = h;
  return temp;
}

void Physics::StateVector::Copy(StateVector const& rhs)
{
  this->v = rhs.v;
  this->p = rhs.p;
}

Physics::StateElements::StateElements() :
  ang_momen(0.0),
  ecc(0.0),
  r_asc_node(0.0),
  incl(0.0),
  arg_peri(0.0),
  true_anom(0.0),
  semi_major(0.0)
{
}

Physics::StateVector Physics::StateElements::ToStateVector(double const & mu) const
{
  Vector3D rp = ((ang_momen * ang_momen) / mu) * (1 / (1 + ecc * cos(true_anom))) *
    ((cos(true_anom) * Vector3D(1.0, 0, 0)) + sin(true_anom) * Vector3D(0, 1, 0));

  Vector3D vp = (mu / ang_momen) * (-1 * sin(true_anom) * Vector3D(1, 0, 0)
    + ((ecc + cos(true_anom)) * Vector3D(0, 1, 0)));
  /* I hate matrix */
  /* Purpse of these defines is for better readability of code without them the array becomes incrediably long and hard to read
  I would use greek letters for even better read ability to but due potential unicode issues I will not*/
#define OMEGA r_asc_node // Ω upper case omega 
#define _omega arg_peri // ω lower case omega because physicists hate making things constistant
#define _i incl //inclination
  double Q_pX[3][3] = {
    {cos(OMEGA) * cos(_omega) - sin(OMEGA) * sin(_omega) * cos(_i),
     -1 * cos(OMEGA) * sin(_omega) - sin(OMEGA) * cos(_i) * cos(_omega),
     sin(_i) * sin(OMEGA) },

    {sin(OMEGA) * cos(_omega) + cos(OMEGA) * cos(_i) * sin(_omega),
     -1 * sin(OMEGA) * sin(_omega) + cos(OMEGA) * cos(_i) * cos(_omega),
     -1 * cos(OMEGA) * sin(_i)},
    {
      sin(_i) * sin(_omega),
      sin(_i) * cos(_omega),
      cos(_i)
    }
  };
  /* Translates the above matrix into these two Vectors*/
  Vector3D R(Q_pX[0][0] * rp.x + Q_pX[0][1] * rp.y + Q_pX[0][2] * rp.z,
    Q_pX[1][0] * rp.x + Q_pX[1][1] * rp.y + Q_pX[1][2] * rp.z,
    Q_pX[2][0] * rp.x + Q_pX[2][1] * rp.y + Q_pX[2][2] * rp.z);
  Vector3D V(Q_pX[0][0] * vp.x + Q_pX[0][1] * vp.y + Q_pX[0][2] * vp.z,
    Q_pX[1][0] * vp.x + Q_pX[1][1] * vp.y + Q_pX[1][2] * vp.z,
    Q_pX[2][0] * vp.x + Q_pX[2][1] * vp.y + Q_pX[2][2] * vp.z);
  return StateVector(V, R);
}

Physics::RotationVector::RotationVector() 
  : r(),
    w()
{
}

Physics::RotationVector::RotationVector(Vector3D const& rotation, Vector3D const& speed)
  : r(rotation),
    w(speed)
{
}

Vector3D Physics::RotationVector::ToDegrees(Vector3D const& vector)
{
  return Vector3D(180.0 * vector);
}

std::ostream& operator<< (std::ostream& os, Physics::StateVector& vec)
{
  os << "( " << vec.p << ", " << vec.v << ")";
  return os;
}