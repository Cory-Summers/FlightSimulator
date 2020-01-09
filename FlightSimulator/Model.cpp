#include "Model.h"
#include <fstream>
/*
OpenGL::Model::Model()
  : obj_data()
  , m_texture_id()
  , m_vertex_id()
{
}

OpenGL::Model::Model(std::string const& obj, GLuint program_id)
{
}

GLuint const& OpenGL::Model::LoadOBJ(std::string const& obj)
{
  AssetImport(obj, *this);
  //LoadFromObj(obj, *this);
  CreateBuffer();
  return m_vertex_id;
}


OpenGL::BufferID const& OpenGL::Model::LoadDDS(std::string const& dds, GLuint program_id)
{
  this->m_texture = DDS::loadDDS(dds.c_str());
  this->m_texture_id = glGetUniformLocation(program_id, "myTextureSampler");
  return m_texture_id;
}

void OpenGL::Model::Initialize()
{
}

OpenGL::Model::Model(std::string const& obj, std::string const & dds, GLuint program_id)
  : obj_data()
  , m_texture_id()
  , m_vertex_id()
  , m_program_id()
{
  LoadDDS(dds, program_id);
  LoadOBJ(obj);
}

void OpenGL::Model::CreateBuffer()
{
  if (obj_data.vertices.size() > 0) 
  {
    m_vertex_id = OpenGL::CreateBuffer<glm::vec3>(obj_data.vertices);
    m_attributes.obj = true;
  }
  if (obj_data.uvs.size() > 0) 
  {
    m_uv_id = OpenGL::CreateBuffer<glm::vec2>(obj_data.uvs);
    m_attributes.obj = true;
  }
  if (obj_data.normals.size() > 0)
  {
    m_normal_id = OpenGL::CreateBuffer<glm::vec3>(obj_data.normals);
    m_attributes.norm = true;
  }
  if (obj_data.indices.size() > 0)
  {
    m_element_id = OpenGL::CreateBuffer<unsigned short>(obj_data.indices, GL_ELEMENT_ARRAY_BUFFER);
    m_attributes.elem = true;
  }
}

void OpenGL::Model::DestroyBuffer()
{
  glDeleteBuffers(1, &m_vertex_id);
  glDeleteBuffers(1, &m_uv_id);
}

void OpenGL::Model::Draw()
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_texture);
  glUniform1i(m_texture_id, 0);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  if (m_attributes.obj == true)
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_id);
    glVertexAttribPointer(
      0,                  // attribute
      3,                  // size
      GL_FLOAT,           // type
      GL_FALSE,           // normalized?
      0,                  // stride
      (void*)0            // array buffer offset
    );
  }
  if (m_attributes.uv == true)
  {
    // 2nd attribute buffer : UVs
    glBindBuffer(GL_ARRAY_BUFFER, m_uv_id);
    glVertexAttribPointer(
      1,                                // attribute
      2,                                // size
      GL_FLOAT,                         // type
      GL_FALSE,                         // normalized?
      0,                                // stride
      (void*)0                          // array buffer offset
    );
  }
  if (m_attributes.norm == true)
  {
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, m_normal_id);
    glVertexAttribPointer(
      2,                                // attribute
      3,                                // size
      GL_FLOAT,                         // type
      GL_FALSE,                         // normalized?
      0,                                // stride
      (void*)0                          // array buffer offset
    );
  }

  // Index buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_id);

  // Draw the triangles !
  glDrawElements(
    GL_TRIANGLES,      // mode
    obj_data.indices.size(),    // count
    GL_UNSIGNED_SHORT,   // type
    (void*)0           // element array buffer offset
  );
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}

OpenGL::Model::~Model()
{
}

*/