#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
namespace OpenGL {
  class Entity
  {
  public:
    Entity(std::string const& name = "unnamed");
  protected:
    std::string m_name;
    uint64_t m_id;
    //Entity Component System
  };
}
