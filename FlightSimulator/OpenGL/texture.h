#pragma once
#include "opengl-tools.h"
namespace OpenGL {
  class Texture
  {
  public:
    Texture();
    Texture(
      std::string const& file_name, 
      std::string const & texture_id, 
      GLuint program_id);
    void Bind(GLuint unit_num = 0, GLuint unit_id = GL_TEXTURE0);
    void SetProgramID(GLuint const& id) { m_program_id = id; }
    void SetTextureID(std::string const&);
    void LoadTexture(std::string const&);
  protected:
    GLuint m_program_id;
    GLuint m_texture_id;
    GLuint m_texture;
  private:
  };
}