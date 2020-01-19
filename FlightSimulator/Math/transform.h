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
    const glm::vec3  ToEuler() const;
    const glm::quat& FromEuler(glm::vec3 const &);
    const glm::quat& FromEuler(cref_sp, cref_sp, cref_sp);
    inline void Translate(glm::vec3 const &);
    void Translate(cref_sp, cref_sp, cref_sp);
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
  private:

  };

}