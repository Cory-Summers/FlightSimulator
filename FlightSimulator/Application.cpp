#include "application.h"
#include "Renderer.h"
Application::Application() 
  : m_simulation(new MVC::Simulation())
  , m_renderer  (new MVC::Render::Renderer())
  , m_config("config.json")
  , m_cncr_ctrl()
  , fps_timing(.1)
{
  m_simulation->SetCncrCtrl(m_cncr_ctrl);
  m_renderer->SetCncrCtrl(m_cncr_ctrl);
  m_simulation->BuildFromFile(std::string(PLANETS_FILE));
  fps_timing = 1000 / m_config.graphics.fps_limit;
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
    m_renderer->RenderScene(*m_simulation);
    Poll();

  } while (glfwWindowShouldClose(&(m_renderer->GetWindow())) == 0);
}

void Application::Poll()
{
  glm::vec2 mouse_pos;
  double x, y;
  glfwPollEvents();
  if (glfwGetKey(&(m_renderer->GetWindow()), GLFW_KEY_D) == GLFW_PRESS)
  {
    m_renderer->GetCamera().GetTransform().position.x += 3;
  }
  else if(glfwGetKey(&(m_renderer->GetWindow()), GLFW_KEY_A) == GLFW_PRESS)
  {
    m_renderer->GetCamera().GetTransform().position.x -= 3;
  }
  else if (glfwGetKey(&(m_renderer->GetWindow()), GLFW_KEY_W) == GLFW_PRESS)
  {
    m_renderer->GetCamera().GetTransform().position.z += 3;
  }
  else if (glfwGetKey(&(m_renderer->GetWindow()), GLFW_KEY_S) == GLFW_PRESS)
  {
    m_renderer->GetCamera().GetTransform().position.z -= 3;
  }
  else if (glfwGetKey(&(m_renderer->GetWindow()), GLFW_KEY_Q) == GLFW_PRESS)
  {
    m_renderer->GetCamera().GetTransform().position.y -= 3;
  }
  else if (glfwGetKey(&(m_renderer->GetWindow()), GLFW_KEY_E) == GLFW_PRESS)
  {
    m_renderer->GetCamera().GetTransform().position.y += 3;
  }
  glfwGetCursorPos(&(m_renderer->GetWindow()), &x, &y);
  mouse_pos = { static_cast<float>(x), static_cast<float>(y) };
  m_renderer->MouseMoveEvent(mouse_pos);
}

void Application::MouseEvents()
{
}
