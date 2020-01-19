#pragma once
#include "OpenGL/opengl-tools.h"
class Application;
namespace MVC {
  class Controller
  {
    using KEY = int;
    using CODE = int;
    using ACTION = int;
    using MOD = int;
  public:
    Controller() {}
    static void SetApp(Application& app) { m_app = &app; }
    static void Initialize(GLFWwindow&);
    static void KBCallBack(GLFWwindow *, KEY, CODE, ACTION, MOD);
  private:
    static Application* m_app;
  };
}

