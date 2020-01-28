#pragma once
#include "DDS-tools.h"
#include "object-loader.h"
#include "Shader.h"
#include <cstdint>
namespace OpenGL
{
  //Defines
  class Model;
  using BufferID = GLuint;
  using Vertex = glm::vec3;
  using VertexBuffer = std::vector<Vertex>;
  using UVBuffer = std::vector<glm::vec2>;
  using NormalBuffer = std::vector <glm::vec3>;
 
  void LoadFromObj(
    std::string const& file_name,
    OBJData&
  );
  bool loadOBJ(
    const char* path,
    std::vector<glm::vec3>& out_vertices,
    std::vector<glm::vec2>& out_uvs,
    std::vector<glm::vec3>& out_normals
  );
  int InitGLFW(int64_t unused = 0);
  int CreateWindow(
    GLFWwindow  ** output,
    const uint32_t x,
    const uint32_t y,
    std::string const& name,
    GLFWmonitor* monitor = nullptr,
    GLFWwindow* shared = nullptr);
  template<typename T>
  GLuint CreateBuffer(std::vector<T> & buffer, GLenum buffer_type = GL_ARRAY_BUFFER, GLenum option = GL_STATIC_DRAW);
  template<typename T>
  GLuint CreateBuffer(std::vector<T> & buffer, GLenum buffer_type, GLenum option)
  {
    GLuint id;
    glGenBuffers(1, &id);
    glBindBuffer(buffer_type, id);
    glBufferData(buffer_type, (buffer.size()) * sizeof(T), &(buffer[0]), option);
    return id;
  }
  glm::vec3 RotateUp(glm::vec3, float);
};