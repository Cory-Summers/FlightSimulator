#pragma once
#include "opengl-tools.h"
#include "transform.h"
#include <glm/glm.hpp>
#include <vector>
#include <list>
namespace OpenGL {
  enum class BufferIdx
  {
    PROGRAM_ID = 0,
    VERTEX_ID,
    NORMAL_ID,
    UV_ID,
    ELEMENT_ID,
    TEXTURE_ID
  };
  class Mesh : public Transform
  {
    struct Attributes {
      GLuint dds : 1;
      GLuint obj : 1;
      GLuint norm : 1;
      GLuint elem : 1;
      GLuint uv : 1;
      GLuint unused : 3;
    };
  public:
    Mesh();
    Mesh(std::string const& obj, GLuint program_id);
  protected:
    glm::mat4 m_mvp;
  private:
    GLuint  m_texture;
    OBJData m_obj_data;
    MeshIDs m_IDs;
  };
};