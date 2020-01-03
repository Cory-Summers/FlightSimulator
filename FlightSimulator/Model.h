#pragma once
#include "opengl-tools.h"
#include <glm/glm.hpp>
#include <vector>
#include <string>
namespace OpenGL {
  class Model
  {

  public:
    Model();
    Model(std::string const & obj, GLuint program_id);
    Model(std::string const&, std::string const & texture, GLuint program_id);
    BufferID const& LoadOBJ(std::string const&);
    BufferID const& LoadDDS(std::string const&, GLuint program_id);
    void Initialize();
    void CreateBuffer();
    void DestroyBuffer();
    void Draw();
    OBJData  obj_data;

    GLuint m_texture;
    ~Model();
  protected:
    BufferID m_program_id;
    BufferID m_texture_id;
    BufferID m_vertex_id;
    BufferID m_normal_id;
    BufferID m_element_id;
    BufferID m_uv_id;
    Attributes m_attributes;
  };
};
