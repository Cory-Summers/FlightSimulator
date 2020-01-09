#include "texture.h"

OpenGL::Texture::Texture()
  : m_texture_id()
  , m_texture()
  , m_program_id(0)
{
}

OpenGL::Texture::Texture(std::string const& file_name,
  std::string const& texture_id,
  GLuint program_id)
  : Texture()
{
  m_program_id = program_id;
  LoadTexture(file_name);
  SetTextureID(texture_id);
}

void OpenGL::Texture::Bind(GLuint unit_num, GLuint unit_id)
{
  glActiveTexture(unit_id);
  glBindTexture(GL_TEXTURE_2D, m_texture);
  glUniform1d(m_texture_id, unit_num);
}

void OpenGL::Texture::SetTextureID(std::string const& id_name)
{
  m_texture_id = glGetUniformLocation(m_program_id, id_name.c_str());
  if (m_texture_id == -1)
    throw ("Failure to load " + id_name + " Uniform Variable for Texture!");
}

void OpenGL::Texture::LoadTexture(std::string const& file_name)
{
  if (m_program_id == -1)
    throw "No program_id to load texture to!";
  this->m_texture = DDS::loadDDS(file_name.c_str());

}
