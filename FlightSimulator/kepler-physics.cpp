#include "kepler-physics.h"
double Physics::StumpffS(double_ref arg)
{
  if (arg > 0) {
    return ((sqrt(arg) - sin(sqrt(arg))) / pow(sqrt(arg), 3.0));
  }
  else if (arg < 0) {
    return ((sinh(sqrt(arg * -1.0)) - sqrt(arg * -1.0)) / pow((sqrt(arg * -1.0)), 3));
  }
  else {
    return (1.0 / 6.0);
  }
}
double Physics::StumpffC(double_ref arg)
{
  if (arg > 0) {
    return ((1 - cos(sqrt(arg))) / arg);
  }
  else if (arg < 0) {
    return ((cosh(sqrt(arg * -1.0)) - 1) / (arg * -1.0));
  }
  else {
    return (1.0 / 2.0);
  }
}

double Physics::UniversalKeplerEq(double_ref dt, double_ref position, double_ref velocity, double_ref rep_axis, double_ref mu)
{
  const int N_MAX = 1000;
  double universal_anom = sqrt(mu) * fabs(rep_axis) * dt;
  double ratio = 1.0;
  double stumpff_c = 0.0, stumpff_s = 0.0;
  int n = 0;
  while(n <= N_MAX && (fabs(ratio) > TOLERANCE)) {
    n++;
    stumpff_c = StumpffC(rep_axis * pow(universal_anom, 2.0));
    stumpff_s = StumpffS(rep_axis * pow(universal_anom, 2.0));
    ratio = position * velocity / sqrt(mu) * pow(universal_anom, 2.0) * stumpff_c + (1.0 - rep_axis * position) * pow(universal_anom, 3.0) * stumpff_s +
      position * universal_anom - sqrt(mu) * dt;
    ratio /= position * velocity / sqrt(mu) * universal_anom * (1.0 - rep_axis * pow(universal_anom, 2.0) * stumpff_s) + (1.0 - rep_axis * position) *
      pow(universal_anom, 2.0) * stumpff_c + position;
    universal_anom -= ratio;
  }
  return universal_anom;
}
Physics::LagrangeCoeff::LagrangeCoeff(double_ref anom, double_ref dt, double_ref pos, double_ref rep_axis, double_ref mu) :
  f(0),
  g(0)
{
  Calculate(anom, dt, pos, rep_axis, mu);
}

void Physics::LagrangeCoeff::Calculate(double_ref anom, double_ref dt, double_ref pos, double_ref rep_axis, double_ref mu)
{
  double anom_sqr = anom * anom;
  double stumpff_num = rep_axis * anom_sqr;
  this->f = 1.0 - (anom_sqr / pos) * StumpffC(stumpff_num);
  this->g = dt - 1.0 / sqrt(mu) * (anom_sqr * anom) * StumpffS(stumpff_num);
}

void Physics::LagrangeCoeff::Derive(double_ref anom, double_ref delta_p, double_ref init_pos, double_ref rep_axis, double_ref mu)
{
  double anom_sqr = anom * anom;
  double stumpff_num = rep_axis * anom_sqr;
  df = sqrt(mu) / delta_p / init_pos * (stumpff_num * StumpffS(stumpff_num) - 1.0) * anom;
  dg = 1.0 - anom_sqr / delta_p * StumpffC(stumpff_num);
}

Physics::OrbitState::OrbitState() :
  apsis(0.0),
  periapsis(0.0),
  eccentricity(0.0),
  inclination(0.0),
  semi_major(0.0)
{
}

Physics::OrbitState::OrbitState(StateElements const& elements) :
  eccentricity(elements.ecc),
  inclination(elements.incl),
  semi_major(elements.semi_major)
{
  Calculate(elements);
}

Physics::OrbitState::OrbitState(StateVector const& vector, double const& mu)
  : OrbitState(vector.ToStateElements(mu))
{
}

void Physics::OrbitState::Calculate(StateElements const& elem)
{
  apsis     = semi_major * (1 + elem.ecc);
  periapsis = semi_major * (1 - elem.ecc);
}
