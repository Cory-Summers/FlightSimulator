#pragma once
#include "Simulation.h"
#include "Renderer.h"
#include "Controller.h"
#include "ConcurrencyController.h"
#include "Utility/config.h"
#include "OpenGL/Camera.h"
#include <thread>
#include <GLFW/glfw3.h>
#define PLANETS_FILE "Resources/planets.json"

class Application
{
public:
  Application();
  void Initialize();
  void Loop();
  void Poll();
  void MouseEvents();
  void RotateCamera(int direction);
  void ChangeCameraTarget();
  MVC::Simulation * m_simulation;
  MVC::Render::Renderer * m_renderer;
private:
  Timer m_timer;
  MVC::ConcurContr m_cncr_ctrl;
  std::string      m_dataFolder;
  std::thread      sim_thread;
  cfg::Master      m_config;
};

