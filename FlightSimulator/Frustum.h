#pragma once
#include <array>
#include <glm/glm.hpp>
//Stolen from Hopson97 on Github
namespace OpenGL {
  struct Plane
  {
    float DistanceToPoint(glm::vec3 const& point) const;
    float DistanceToOrigin;
    glm::vec3 normal;
  };
  class Frustum
  {
  public:
    void Update(const glm::mat4& projViewMatrix) noexcept;
  private:
    std::array<Plane, 6> m_planes;
  };

}

