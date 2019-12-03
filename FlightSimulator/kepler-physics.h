#pragma once
#include <SFML/Window.hpp>
#include "StateElements.h"
#define _USE_MATH_DEFINES
#include <cmath>
namespace Physics {
  using double_ref = double const&;
  constexpr double TOLERANCE = 1.e-12;
  double StumpffS(double_ref arg);
  double StumpffC(double_ref arg);
  double UniversalKeplerEq(double_ref dt, double_ref position, double_ref velocity, double_ref rep_axis, double_ref mu);
  class LagrangeCoeff {
  public:
    LagrangeCoeff (double_ref anom, double_ref dt, double_ref pos, double_ref rep_axis, double_ref mu);
    void Calculate(double_ref anom, double_ref dt, double_ref pos, double_ref rep_axis, double_ref mu);
    void Derive   (double_ref anom, double_ref delta_p, double_ref init_pos, double_ref rep_axis, double_ref mu);
    double f, df;
    double g, dg;
  };
  struct OrbitState {
    OrbitState();
    OrbitState(StateElements const&);
    OrbitState(StateVector const&, double const&);
    void Calculate(StateElements const&);
    double apsis;
    double periapsis;
    double eccentricity;
    double inclination;
    double semi_major;
  private:
    double mu;
  };
}