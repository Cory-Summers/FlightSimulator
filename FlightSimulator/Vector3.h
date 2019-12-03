#pragma once
#include <immintrin.h>
#include <initializer_list>
#include <iostream>
#define _ENABLE_EXTENDED_ALIGNED_STORAGE
class Vector3D
{
  using double_ref = double const&;
  using vector_ref = Vector3D const&;
public:
  Vector3D();
  Vector3D(double_ref, double_ref, double_ref);
  Vector3D(std::initializer_list<double>);
  Vector3D(__m256d const&);
  double & operator[] (size_t const&);
  double Normalize() const;
  Vector3D operator * (double_ref);
  
  Vector3D operator * (Vector3D const&) const;
  Vector3D & operator *= (double const&);

  Vector3D operator - (double const&) const;
  Vector3D operator - (Vector3D const&) const;
  Vector3D& operator -= (double const&);

  Vector3D operator + (double const&) const;
  Vector3D operator + (Vector3D const&) const;
  Vector3D& operator += (double const&);

  Vector3D operator / (double const&) const;
  Vector3D operator / (Vector3D const&) const;
  Vector3D& operator /= (double const&);

  Vector3D& operator = (Vector3D const&);
  Vector3D& operator = (double const&);

  friend Vector3D operator* (double, Vector3D);

  static double   Dot(Vector3D const&, Vector3D const&);
  static Vector3D Cross(Vector3D const&, Vector3D const&);
  union {
    __m256d vector;
    double quad_arr[4];
    struct __declspec(align(32)) {
      double x;
      double y;
      double z;
      double a; //unused
    };
  };
protected:

};

std::ostream & operator<<(std::ostream& os, Vector3D& vec);