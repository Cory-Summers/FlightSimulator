#include "RenderObject.h"

OpenGL::RenderObject::RenderObject()
{
}

OpenGL::RenderObject::RenderObject(
  GLuint prog_id, 
  std::string const& mesh_file, 
  std::string const& texture_file, 
  std::string const& mesh_uniform, 
  std::string const& texture_uniform)
  : m_buffer()
  , m_texture(std::make_shared<OpenGL::Texture>(texture_file, texture_uniform, prog_id))
  , m_mesh(std::make_shared<OpenGL::Mesh>(mesh_file, mesh_uniform, prog_id))
{
  m_transform = OpenGL::Transform();
  m_buffer.fill(-1);
  Initialize(prog_id);
}

void OpenGL::RenderObject::Initialize(GLuint const & prog_id)
{
  m_buffer[OB_MODEL_ID] = glGetUniformLocation(prog_id, "M");
}

void OpenGL::RenderObject::Draw(Camera& camera)
{
  glm::mat4 model_mat = this->ModelMatrix();
  glm::mat4 MVP       = camera.GetMVP(model_mat);
  glUniformMatrix4fv((camera.GetMatrixID()), 1, GL_FALSE, &MVP[0][0]);
  glUniformMatrix4fv(m_buffer[OB_MODEL_ID], 1, GL_FALSE, &model_mat[0][0]);
  if (m_texture) m_texture->Bind();
  m_mesh->Draw();
}

void OpenGL::RenderObject::Destroy()
{
}

OpenGL::RenderObject::~RenderObject()
{
}

glm::mat4 OpenGL::RenderObject::ModelMatrix()
{
  glm::mat4 model_mat(1.f);
  model_mat = 
    //glm::scale(m_transform.scale) * 
    glm::translate(model_mat, m_transform.position) * 
    glm::toMat4(m_transform.rotation);
  return model_mat;
}
