#include "Mesh.h"

OpenGL::Mesh::Mesh()
  : m_objdata()
  , m_attr()
  , m_buffers()
  , gl_var_name("M")
{
}

OpenGL::Mesh::Mesh(
  std::string const& obj,
  std::string const& uniform_name, 
  GLuint program_id)
  : m_objdata()
  , m_attr()
  , m_buffers()
  , gl_var_name(uniform_name)
{
  m_buffers.fill(-1);
  m_buffers[MB_PROGRAM_ID] = program_id;
  LoadMesh(obj);
  LoadBuffers();
}

void OpenGL::Mesh::LoadMesh(std::string const& file)
{
  AssetImport(file, m_objdata);
}

void OpenGL::Mesh::SetUniformVariableName(std::string const& var)
{
  gl_var_name = var;
  LoadModelMatrixID();
}

void OpenGL::Mesh::Draw()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[MB_VERTEX_ID]);
  glVertexAttribPointer(
    0,                  // attribute
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
  );
  // 2nd attribute buffer : UVs
  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[MB_UV_ID]);
  glVertexAttribPointer(
    1,                                // attribute
    2,                                // size
    GL_FLOAT,                         // type
    GL_FALSE,                         // normalized?
    0,                                // stride
    (void*)0                          // array buffer offset
  );
  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[MB_NORMAL_ID]);
  glVertexAttribPointer(
    2,                                // attribute
    3,                                // size
    GL_FLOAT,                         // type
    GL_FALSE,                         // normalized?
    0,                                // stride
    (void*)0                          // array buffer offset
  );

  // Index buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[MB_ELEMENT_ID]);

  // Draw the triangles !
  glDrawElements(
    GL_TRIANGLES,      // mode
    static_cast<GLsizei>(m_objdata.indices.size()),    // count
    GL_UNSIGNED_SHORT,   // type
    (void*)0           // element array buffer offset
  );
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}

OpenGL::Mesh::~Mesh()
{
  DestroyBuffers();
}

void OpenGL::Mesh::LoadBuffers()
{
  if (m_buffers[MB_MODEL_ID] == 0)
    LoadModelMatrixID();
  if (m_objdata.vertices.size() > 0)
  {
    m_buffers[MeshBufIdx::MB_VERTEX_ID] = OpenGL::CreateBuffer<glm::vec3>(m_objdata.vertices);
    m_attr.obj = true;
  }
  if (m_objdata.uvs.size() > 0)
  {
    m_buffers[MeshBufIdx::MB_UV_ID] = OpenGL::CreateBuffer<glm::vec2>(m_objdata.uvs);
    m_attr.uv = true;
  }
  if (m_objdata.normals.size() > 0)
  {
    m_buffers[MeshBufIdx::MB_NORMAL_ID] = OpenGL::CreateBuffer<glm::vec3>(m_objdata.normals);
    m_attr.norm = true;
  }
  if (m_objdata.indices.size() > 0)
  {
    m_buffers[MeshBufIdx::MB_ELEMENT_ID] = OpenGL::CreateBuffer<uint16_t>(m_objdata.indices, GL_ELEMENT_ARRAY_BUFFER);
    m_attr.elem = true;
  }
}

void OpenGL::Mesh::LoadModelMatrixID()
{
  GLuint id = glGetUniformLocation(m_buffers[MB_PROGRAM_ID], gl_var_name.c_str());
  if (id == -1)
    throw "Invalid Uniform Variable name!";
  m_buffers[MB_MODEL_ID] = id;
}

void OpenGL::Mesh::DestroyBuffers()
{
  for (auto & id : m_buffers)
    if (id != 0) { glDeleteBuffers(1, &id); }
}
