#include "Renderer.h"
#include <fstream>
#include <string>
#include <cstdio>
#include "nlohmann/json.hpp"
#include "opengl-tools.h"

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
static const GLfloat g_vertex_buffer_data[] = {
   -.5f, -.5f, 0.0f,
   0.5f, -.5f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

static GLuint VertexArrayID;
MVC::Render::Renderer::Renderer() :
  m_window(),
  m_config(cfg::LoadWindowConfig(std::string(CONFIG_FILE))),
  m_camera()
{
  m_camera.SetConfig(m_config);
}

int MVC::Render::Renderer::CreateContext() noexcept
{
  glfwMakeContextCurrent(m_window);
  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;
  }
  glViewport(0, 0, m_config.x, m_config.y);
  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
}

void MVC::Render::Renderer::InitGLSettings() noexcept
{
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  // Cull triangles which normal is not towards the camera
  glEnable(GL_CULL_FACE);
}

void MVC::Render::Renderer::Initialize()
{
  OpenGL::InitGLFW();
  OpenGL::CreateWindow(&m_window, m_config.x, m_config.y, "View Port");
  CreateContext();
  InitGLSettings();
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);
  ProgramID = OpenGL::Shader::LoadShaders("resources/StandardShading.vertexshader", "resources/StandardShading.fragmentshader");
  m_camera.SetProgramID(ProgramID);
  m_camera.GetUniform();
  m_camera.LoadProjection();
  m_model   = OpenGL::Model("resources/suzanne.obj", "resources/uvmap.DDS", ProgramID);
  
}

GLFWwindow& MVC::Render::Renderer::GetWindow()
{
  return *m_window;
}

void MVC::Render::Renderer::MouseMoveEvent(glm::vec2 mouse_pos)
{
  m_camera.MouseUpdate(mouse_pos);
}


void MVC::Render::Renderer::RenderScene()
{
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Use our shader

  glUseProgram(ProgramID);
  m_camera.Update();
  m_model.Draw();
  glfwSwapBuffers(m_window);
}

void MVC::Render::Renderer::ClearBuffer()
{

  // Cleanup VBO
  glDeleteVertexArrays(1, &VertexArrayID);
  glDeleteProgram(ProgramID);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();
}