#include "Renderer.h"
#include <fstream>
#include <string>
#include <cstdio>
#include "nlohmann/json.hpp"
#include "OpenGL/opengl-tools.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
  m_camera()
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
  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  glfwSwapInterval(1);
}

void MVC::Render::Renderer::InitGLSettings() noexcept
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  // Cull triangles which normal is not towards the camera
  glEnable(GL_CULL_FACE);
}

void MVC::Render::Renderer::Initialize(MVC::Simulation & simulation)
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
  center = std::make_shared<OpenGL::RenderObject>(ProgramID, "resources/Sphere.obj", "resources/uvmap2.DDS");
  m_camera.SetTarget(center);
  {
    std::unique_lock<std::mutex> lock(cncr_ctrl->natural_mutex);
    for (auto& p : simulation.m_natural_body)
    {
      planets.push_back(std::make_shared<PlanetRender>(ProgramID, std::weak_ptr<Kepler::Planet>(std::static_pointer_cast<Kepler::Planet>(p))));
      /*
      m_obj.GetTransform().position = glm::vec3(5, 0, 0);
      m_obj.GetTransform().FromEuler(0.f, 45.f, .0f);
      m_camera.m_transform.position = { 0, 0, -15 };
      */
    }
  }
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
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(ProgramID);
  m_camera.Update();
  {
    std::unique_lock<std::mutex> lock(cncr_ctrl->natural_mutex);
    for (auto& p : planets)
      p->Draw(m_camera);
  }
  center->Draw(m_camera);
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