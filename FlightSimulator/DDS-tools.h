#pragma once
#include <array>
#include <iostream>
#include <fstream>
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <GL\GL.h>
#include <sstream>
#include <vector>

namespace OpenGL::DDS
{
  struct Header
  {
    unsigned int height;
    unsigned int width;
    unsigned int linear_size;
    unsigned int mip_map_count;
    unsigned int four_cc;
  };
  GLuint Loader(std::string const&);
  GLuint loadDDS(const char* imagepath);
};