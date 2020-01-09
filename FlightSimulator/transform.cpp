#include "transform.h"
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
namespace OpenGL {
  Transform::Transform()
    : position(0.f)
    , rotation()
    , scale(1.0f)
  {
  }

  Transform::Transform(
    vec3_cref position,
    vec3_cref euler,
    vec3_cref scale)
    : position(position)
    , rotation(FromEuler(euler))
    , scale(scale)
  {
  }

  Transform::Transform(
    vec3_cref position,
    glm::quat const & rotation,
    vec3_cref scale)
    : position(position)
    , rotation(rotation)
    , scale(scale)
  {
  }
  const glm::vec3 Transform::ToEuler() const
  {
    return glm::vec3(glm::eulerAngles(rotation));
  }

  glm::quat const& Transform::FromEuler(glm::vec3 const& euler)
  {
    rotation = glm::eulerAngleXYZ(euler.x, euler.y, euler.z);
    return rotation;
  }

  glm::quat const& Transform::FromEuler(cref_sp x, cref_sp y, cref_sp z)
  {
    rotation = glm::eulerAngleXYZ(x, y, z);
    return rotation;
  }

  void Transform::Translate(glm::vec3 const& vector)
  {
    position += vector;
  }

  void Transform::Translate(cref_sp x, cref_sp y, cref_sp z)
  {
    this->Translate(glm::vec3(x, y, z));
  }
}