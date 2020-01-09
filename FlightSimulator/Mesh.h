#pragma once
#include "opengl-tools.h"
#include <glm/glm.hpp>
#include <array>
namespace OpenGL {
  enum MeshBufIdx : size_t
  {
    MB_PROGRAM_ID = 0,
    MB_MODEL_ID,
    MB_VERTEX_ID,
    MB_NORMAL_ID,
    MB_UV_ID,
    MB_ELEMENT_ID,
    MB_TEXTURE_ID,
    MB_IDX_SIZE = 7
  };
  class Mesh
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
    Mesh(
      std::string const& obj, 
      std::string const & uniform_name, 
      GLuint program_id
    );
    void LoadMesh(std::string const&);
    void SetUniformVariableName(std::string const& var);
    void LoadBuffers();
    void Draw();
    ~Mesh();
  protected:
    void LoadModelMatrixID();
    void DestroyBuffers();
  private:
    std::string gl_var_name; //uniform variable name
    OBJData m_objdata;
    Attributes m_attr;
    std::array<GLuint, MB_IDX_SIZE> m_buffers;
  };
};