#include "Controller.h"
#include "application.h"
Application* MVC::Controller::m_app = nullptr;
void MVC::Controller::Initialize(GLFWwindow & window)
{
  glfwSetKeyCallback(&window, KBCallBack);
}

void MVC::Controller::KBCallBack(GLFWwindow* window, KEY key, CODE code, ACTION action, MOD mod)
{
  switch (key)
  {
  case GLFW_KEY_A:
  case GLFW_KEY_D:
  case GLFW_KEY_W:
  case GLFW_KEY_S:
  case GLFW_KEY_Q:
  case GLFW_KEY_E:
    Controller::m_app->RotateCamera(key);
    break;
  case GLFW_KEY_MINUS:
  case GLFW_KEY_EQUAL:
    if (action == GLFW_PRESS) {
      m_app->m_simulation->SendMessage(SimMessage(MT_TIME, (key == GLFW_KEY_EQUAL) ? TP_INCR_SP : TP_DECR_SP));
    }
    break;
  case GLFW_KEY_TAB:
    if (action == GLFW_PRESS)
      m_app->ChangeCameraTarget();
    break;
  }
}
