#pragma once
#include <chrono>
#include <iostream>
#include "Vector3.h"
namespace Physics {
  class StateVector;
  struct StateElements
  {
  public:
    StateElements();
    double ang_momen = 0; /*angular momentum (km2/s)*/
    double ecc = 0;
    double r_asc_node = 0; /* right ascension of the ascending node (rad)*/
    double incl = 0; /*inclination of orbit (rad)*/
    double arg_peri = 0; /* argument of perigee (rad)*/
    double true_anom = 0; /* true anomaly (rad)*/
    double semi_major = 0; /*semimajor-axis (km)*/
    StateVector ToStateVector(double const&) const;
  protected:
  };
  typedef std::chrono::duration<double> TimePoint;

  class StateVector {
  public:
    StateVector();
    StateVector(Vector3D const&, Vector3D const&);
    StateVector(StateVector const&);
    ~StateVector();
    StateElements ToStateElements(double const &) const;
    Vector3D v; //Velocity
    Vector3D p; //Position km
  protected:
    void Copy(StateVector const&);
  };
  
  class RotationVector {
  public:
    RotationVector();
    RotationVector(Vector3D const&, Vector3D const&);
    Vector3D r; //Rotation 
    Vector3D w; //Rotational Speed km/s
    static inline Vector3D ToDegrees(Vector3D const&);
  };
}
std::ostream& operator<< (std::ostream& os, Physics::StateVector& vec);