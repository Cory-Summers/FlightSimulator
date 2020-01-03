#include "application.h"
#include "Renderer.h"
Application::Application() 
  : m_simulation(new MVC::Simulation()),
    m_renderer  (new MVC::Render::Renderer()),
    m_controller(new MVC::Controller()),
    m_cncr_ctrl()
{
  m_simulation->SetCncrCtrl(m_cncr_ctrl);
  m_renderer->SetCncrCtrl(m_cncr_ctrl);
  m_simulation->BuildFromFile(std::string(PLANETS_FILE));
}

void Application::Initialize()
{
  m_simulation->Initialize();
  m_renderer->Initialize();
}

void Application::Loop()
{
  sim_thread = std::thread(&MVC::Simulation::Main, m_simulation);
  do
  {
    m_renderer->RenderScene();
    Poll();
  } while (glfwWindowShouldClose(&(m_renderer->GetWindow())) == 0);
}

void Application::Poll()
{
  glm::vec2 mouse_pos;
  double x, y;
  glfwPollEvents();
  if (glfwGetKey(&(m_renderer->GetWindow()), GLFW_KEY_RIGHT) == GLFW_PRESS)
  {
    m_renderer->GetCamera().Rotate(1.5f);
  }
  else if(glfwGetKey(&(m_renderer->GetWindow()), GLFW_KEY_LEFT) == GLFW_PRESS)
  {
    m_renderer->GetCamera().Rotate(-1.5f);
  }
  else if (glfwGetKey(&(m_renderer->GetWindow()), GLFW_KEY_UP) == GLFW_PRESS)
  {
    m_renderer->GetCamera().Rotate(1.5f, OpenGL::Camera::Axis::Z_AXIS);
  }
  else if (glfwGetKey(&(m_renderer->GetWindow()), GLFW_KEY_DOWN) == GLFW_PRESS)
  {
    m_renderer->GetCamera().Rotate(-1.5f, OpenGL::Camera::Axis::Z_AXIS);

  }
  glfwGetCursorPos(&(m_renderer->GetWindow()), &x, &y);
  mouse_pos = { static_cast<float>(x), static_cast<float>(y) };
  m_renderer->MouseMoveEvent(mouse_pos);
}

void Application::MouseEvents()
{
}
