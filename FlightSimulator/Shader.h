#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace OpenGL::Shader
{
  GLuint LoadShaders(
    const char* vertex_file_path, 
    const char* fragment_file_path);

};

