#include "application.h"
#include "Renderer.h"
Application::Application()
  : m_simulation(new MVC::Simulation())
  , m_renderer(new MVC::Render::Renderer())
  , m_config("config.json")
  , m_cncr_ctrl()
  , fps_timing(.1)
  , m_timer()
{
  m_simulation->SetCncrCtrl(m_cncr_ctrl);
  m_renderer->SetCncrCtrl(m_cncr_ctrl);
  m_simulation->BuildFromFile(std::string(PLANETS_FILE));
  fps_timing = 1000 / m_config.graphics.fps_limit;
}

void Application::Initialize()
{
  m_simulation->Initialize();
  m_renderer->Initialize(*m_simulation);
  MVC::Controller::Initialize(m_renderer->GetWindow());
  MVC::Controller::SetApp(*this);
}

void Application::Loop()
{
  sim_thread = std::thread(&MVC::Simulation::Main, m_simulation);
  do
  {
    m_timer.Stop();
    m_timer.Start();
    m_renderer->RenderScene(*m_simulation);
    Poll();

  } while (glfwWindowShouldClose(&(m_renderer->GetWindow())) == 0);
}

void Application::Poll()
{
  glm::vec2 mouse_pos;
  double x, y;
  GLFWwindow* window = &(m_renderer->GetWindow());
  glfwPollEvents();
  //glfwWaitEvents();
  glfwGetCursorPos(window, &x, &y);
  mouse_pos = { static_cast<float>(x), static_cast<float>(y) };
  m_renderer->MouseMoveEvent(mouse_pos);
}

void Application::MouseEvents()
{
}

void Application::RotateCamera(int direction)
{
  if (m_renderer == nullptr)
    return;
  switch(direction)
  {
  case GLFW_KEY_A:
    m_renderer->GetCamera().GetTransform().position.x += 10.0 * m_timer.GetCount();
    break;
  case GLFW_KEY_D:
    m_renderer->GetCamera().GetTransform().position.x -= 10.0 * m_timer.GetCount();
    break;
  case GLFW_KEY_W:
    m_renderer->GetCamera().GetTransform().position.z += 10.0 * m_timer.GetCount();
    break;
  case GLFW_KEY_S:
    m_renderer->GetCamera().GetTransform().position.z -= 10.0 * m_timer.GetCount();
    break;
  case GLFW_KEY_Q:
    m_renderer->GetCamera().GetTransform().position.y -= 10.0 * m_timer.GetCount();
    break;
  case GLFW_KEY_E:
    m_renderer->GetCamera().GetTransform().position.y += 10.0 * m_timer.GetCount();
    break;
  }
}

void Application::ChangeCameraTarget()
{
  OpenGL::Camera& camera = m_renderer->GetCamera();
  auto target = camera.GetTarget();
  auto & planets = m_renderer->GetPlanets();
  if (!target.lock())
  {
    camera.SetTarget(planets[0]);
    std::cout << "Target: " << camera.GetTarget().lock()->GetName() << '\n';
  }
  else
  {
    auto it = std::find(planets.begin(), planets.end(), target.lock());
    if (*it != planets.back()) {
      camera.SetTarget(*(++it));
      std::cout << "Target: " << camera.GetTarget().lock()->GetName() << '\n';
    }
    else
      camera.ReleaseTarget();
  }
}

