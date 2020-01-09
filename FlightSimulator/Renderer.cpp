#include "Renderer.h"
#include <fstream>
#include <string>
#include <cstdio>
#include "nlohmann/json.hpp"
#include "opengl-tools.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
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
  m_config(std::string(CONFIG_FILE)),
  m_camera(),
  m_cube(),
  m_timer(m_config.graphics.fps_limit)
{
  m_camera.SetConfig(m_config.window);
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
  glViewport(0, 0, m_config.window.x, m_config.window.y);
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
  OpenGL::CreateWindow(&m_window, m_config.window.x, m_config.window.y, "View Port");
  CreateContext();
  InitGLSettings();
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);
  ProgramID = OpenGL::Shader::LoadShaders("resources/StandardShading.vertexshader", "resources/StandardShading.fragmentshader");
  m_camera.SetProgramID(ProgramID);
  m_camera.GetUniform();
  m_camera.LoadProjection();
  m_obj = OpenGL::RenderObject(ProgramID, "resources/Sphere.obj", "resources/uvmap.DDS");
  jupiter = m_cube = m_obj;
  
  m_obj.GetTransform().position = glm::vec3(5, 0, 0);
  m_obj.GetTransform().FromEuler(0.f, 45.f, .0f);
  m_camera.m_transform.position = { 0, 0, -15 };
}

GLFWwindow& MVC::Render::Renderer::GetWindow()
{
  return *m_window;
}

void MVC::Render::Renderer::MouseMoveEvent(glm::vec2 mouse_pos)
{
  m_camera.MouseUpdate(mouse_pos);
}


void MVC::Render::Renderer::RenderScene(MVC::Simulation & sim)
{
  const float rot_incr= M_PI / 128.f;
  float rot = 0.f;
  Vector3D vec = sim.GetBody(0).GetVector().p;
  vec /= 1e7;
  m_obj.GetTransform().position = { vec.x, vec.y, vec.z };
  vec = sim.GetBody(1).GetVector().p;
  vec /= 1e7;
  m_cube.GetTransform().position = { vec.x, vec.y, vec.z };
  vec = sim.GetBody(2).GetVector().p;
  vec /= 1e7;
  jupiter.GetTransform().position = { vec.x, vec.y, vec.z };
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(ProgramID);
  m_camera.Update();
  m_obj.Draw(m_camera);
  m_cube.Draw(m_camera);
  jupiter.Draw(m_camera);
  glfwSwapBuffers(m_window);
  m_timer.Stop();
  m_timer.Start();
}

void MVC::Render::Renderer::ClearBuffer()
{

  // Cleanup VBO
  glDeleteVertexArrays(1, &VertexArrayID);
  glDeleteProgram(ProgramID);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();
}