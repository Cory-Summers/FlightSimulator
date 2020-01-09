#pragma once
#include "Simulation.h"
#include "Renderer.h"
#include "Controller.h"
#include "ConcurrencyController.h"
#include "config.h"
#include "Camera.h"
#include <thread>
#include <GLFW/glfw3.h>
#define PLANETS_FILE "planets.json"

class Application
{
public:
  Application();
  void Initialize();
  void Loop();
  void Poll();
  void MouseEvents();
  MVC::Simulation * m_simulation;
  MVC::Render::Renderer * m_renderer;
private:
  MVC::ConcurContr m_cncr_ctrl;
  std::string      m_dataFolder;
  OpenGL::Camera   m_camera;
  std::thread      sim_thread;
  cfg::Master      m_config;
  float fps_timing;
};

