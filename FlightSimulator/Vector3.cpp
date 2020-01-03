#include "Vector3.h"
#define _USE_MATH_DEFINES
#include <cmath>
#define _ENABLE_EXTENDED_ALIGNED_STORAGE
const double zero = 0.0;
Vector3D::Vector3D() :
  vector(_mm256_broadcast_sd(&zero))
{
}

Vector3D::Vector3D(double_ref x, double_ref y, double_ref z) :
  x(x),
  y(y),
  z(z)

{
}

Vector3D::Vector3D(std::initializer_list<double> list) :
  quad_arr()
{
  int index = 0;
  for (auto & i : list) {
    quad_arr[index++] = i; 
  }
}

Vector3D::Vector3D(__m256d const& vec) :
  vector(vec)
{
}

Vector3D::Vector3D(std::array<double, 3> const& arr) :
  quad_arr()
{
  int index = 0;
  for (auto& it : arr)
    quad_arr[index++] = it;
}

double& Vector3D::operator[](size_t const& pos)
{
  return quad_arr[pos];
}

double Vector3D::Normalize() const
{
  return (sqrt(fabs((x * x) + (y * y) + (z * z))));

}

Vector3D Vector3D::operator* (double_ref rhs)
{
  __m256d buffer = _mm256_broadcast_sd(&rhs);
  __m256d lhs    = _mm256_mul_pd(this->vector, buffer);
  return  Vector3D(lhs);
}

Vector3D Vector3D::operator*(Vector3D const& rhs) const
{
  return Vector3D(_mm256_mul_pd(this->vector, rhs.vector));
}

Vector3D & Vector3D::operator*=(double const& rhs)
{
  __m256d buffer = _mm256_broadcast_sd(&rhs);
  this->vector   = _mm256_mul_pd(this->vector, buffer);
  return *this;
}


Vector3D Vector3D::operator-(double const& rhs) const
{
  __m256d buffer = _mm256_broadcast_sd(&rhs);
  __m256d lhs = _mm256_sub_pd(this->vector, buffer);
  return  Vector3D(lhs);
}

Vector3D Vector3D::operator-(Vector3D const& rhs) const
{
  return Vector3D(_mm256_sub_pd(this->vector, rhs.vector));
}

Vector3D& Vector3D::operator-=(double const& rhs)
{
  __m256d buffer = _mm256_broadcast_sd(&rhs);
  this->vector = _mm256_sub_pd(this->vector, buffer);
  return *this;
}

Vector3D Vector3D::operator+(double const& rhs) const
{
  __m256d buffer = _mm256_broadcast_sd(&rhs);
  __m256d lhs = _mm256_add_pd(this->vector, buffer);
  return  Vector3D(lhs);
}

Vector3D Vector3D::operator+(Vector3D const& rhs) const
{
  return Vector3D(_mm256_add_pd(this->vector, rhs.vector));
}

Vector3D& Vector3D::operator+=(double const& rhs)
{
  __m256d buffer = _mm256_broadcast_sd(&rhs);
  this->vector = _mm256_add_pd(this->vector, buffer);
  return *this;
}

Vector3D Vector3D::operator/(double const& rhs) const
{
  __m256d buffer = _mm256_broadcast_sd(&rhs);
  __m256d lhs = _mm256_div_pd(this->vector, buffer);
  return  Vector3D(lhs);
}

Vector3D Vector3D::operator/(Vector3D const& rhs) const
{
  return Vector3D(_mm256_div_pd(this->vector, rhs.vector));
}

Vector3D& Vector3D::operator/=(double const& rhs)
{
  __m256d buffer = _mm256_broadcast_sd(&rhs);
  this->vector = _mm256_div_pd(this->vector, buffer);
  return *this;
}

Vector3D& Vector3D::operator=(Vector3D const& rhs)
{
  this->vector = rhs.vector;
  return *this;
}

Vector3D& Vector3D::operator=(double const& rhs)
{
  this->vector = _mm256_broadcast_sd(&rhs);
}

double Vector3D::Dot(Vector3D const& lhs, Vector3D const& rhs)
{
  return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
}

Vector3D Vector3D::Cross(Vector3D const& u, Vector3D const& v)
{
  return Vector3D(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

Vector3D operator*(double rhs, Vector3D lhs)
{
  __m256d buffer = _mm256_broadcast_sd(&rhs);
  __m256d result = _mm256_mul_pd(lhs.vector, buffer);
  return Vector3D(result);
}

Vector3D operator*(Vector3D lhs, double rhs)
{
  return lhs.operator*(rhs);
}

std::ostream & operator<<(std::ostream& os, Vector3D& vec)
{
  os << "( " << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return os;
}
