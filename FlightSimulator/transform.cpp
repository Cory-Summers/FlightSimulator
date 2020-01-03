#include "transform.h"
#include <glm/gtx/euler_angles.hpp>
namespace OpenGL {
  Transform::Transform()
    : m_position(0.f)
    , m_rotation()
    , m_scale(1.0f)
  {
  }

  Transform::Transform(
    vec3_cref position,
    vec3_cref euler,
    vec3_cref scale)
    : m_position(position)
    , m_rotation(FromEuler(euler))
    , m_scale(scale)
  {
  }

  Transform::Transform(
    vec3_cref position,
    glm::quat const & rotation,
    vec3_cref scale)
    : m_position(position)
    , m_rotation(rotation)
    , m_scale(scale)
  {
  }

  const glm::vec3 Transform::ToEuler() const
  {
    return glm::vec3(glm::eulerAngles(m_rotation));
  }

  glm::quat const& Transform::FromEuler(glm::vec3 const& euler)
  {
    m_rotation = glm::eulerAngleXYZ(euler.x, euler.y, euler.z);
    return m_rotation;
  }

  glm::quat const& Transform::FromEuler(cref_sp x, cref_sp y, cref_sp z)
  {
    m_rotation = glm::eulerAngleXYZ(x, y, z);
    return m_rotation;
  }

  void Transform::Translate(glm::vec3 const& vector)
  {
    m_position += vector;
  }

  void Transform::Translate(cref_sp x, cref_sp y, cref_sp z)
  {
    this->Translate(glm::vec3(x, y, z));
  }
}