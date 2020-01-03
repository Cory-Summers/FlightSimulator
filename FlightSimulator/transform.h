#pragma once
#include <glm/common.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
namespace OpenGL {
  class Transform
  {
    using cref_sp   = float const&;
    using vec3_cref = glm::vec3 const&;
  public:
    Transform();
    Transform(vec3_cref, vec3_cref, vec3_cref scale = glm::vec3(1.0f));
    Transform(vec3_cref, glm::quat const &, vec3_cref scale = glm::vec3(1.0f));
    glm::vec3& Position() { return m_position; }
    glm::quat& Rotation() { return m_rotation; }
    glm::vec3& Scale() { return m_scale; }

    const glm::vec3  ToEuler() const;
    const glm::quat& FromEuler(glm::vec3 const &);
    const glm::quat& FromEuler(cref_sp, cref_sp, cref_sp);

    inline void Translate(glm::vec3 const &);
    void Translate(cref_sp, cref_sp, cref_sp);
  protected:
    glm::vec3 m_position;
    glm::quat m_rotation;
    glm::vec3 m_scale;
  private:

  };

}