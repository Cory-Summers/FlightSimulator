#include "Frustum.h"
using namespace OpenGL;
enum Planes
{
  Near,
  Far,
  Left,
  Right,
  Top,
  Bottom,
};

float Plane::DistanceToPoint(const glm::vec3& point) const
{
  return glm::dot(point, normal) + DistanceToOrigin;
}

void Frustum::Update(const glm::mat4& mat) noexcept
{
  // left
  m_planes[Planes::Left].normal.x = mat[0][3] + mat[0][0];
  m_planes[Planes::Left].normal.y = mat[1][3] + mat[1][0];
  m_planes[Planes::Left].normal.z = mat[2][3] + mat[2][0];
  m_planes[Planes::Left].DistanceToOrigin = mat[3][3] + mat[3][0];

  // right
  m_planes[Planes::Right].normal.x = mat[0][3] - mat[0][0];
  m_planes[Planes::Right].normal.y = mat[1][3] - mat[1][0];
  m_planes[Planes::Right].normal.z = mat[2][3] - mat[2][0];
  m_planes[Planes::Right].DistanceToOrigin = mat[3][3] - mat[3][0];

  // bottom
  m_planes[Planes::Bottom].normal.x = mat[0][3] + mat[0][1];
  m_planes[Planes::Bottom].normal.y = mat[1][3] + mat[1][1];
  m_planes[Planes::Bottom].normal.z = mat[2][3] + mat[2][1];
  m_planes[Planes::Bottom].DistanceToOrigin = mat[3][3] + mat[3][1];

  // top
  m_planes[Planes::Top].normal.x = mat[0][3] - mat[0][1];
  m_planes[Planes::Top].normal.y = mat[1][3] - mat[1][1];
  m_planes[Planes::Top].normal.z = mat[2][3] - mat[2][1];
  m_planes[Planes::Top].DistanceToOrigin = mat[3][3] - mat[3][1];

  // near
  m_planes[Planes::Near].normal.x = mat[0][3] + mat[0][2];
  m_planes[Planes::Near].normal.y = mat[1][3] + mat[1][2];
  m_planes[Planes::Near].normal.z = mat[2][3] + mat[2][2];
  m_planes[Planes::Near].DistanceToOrigin = mat[3][3] + mat[3][2];

  // far
  m_planes[Planes::Far].normal.x = mat[0][3] - mat[0][2];
  m_planes[Planes::Far].normal.y = mat[1][3] - mat[1][2];
  m_planes[Planes::Far].normal.z = mat[2][3] - mat[2][2];
  m_planes[Planes::Far].DistanceToOrigin = mat[3][3] - mat[3][2];

  for (auto& plane : m_planes)
  {
    float length = glm::length(plane.normal);
    plane.normal /= length;
    plane.DistanceToOrigin /= length;
  }

}