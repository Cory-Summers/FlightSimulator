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
/* Application is the main driver class for the program composing the rendering half and the 
 * simulation half of the program.
 */
class Application
{
public:
  Application();
  void Initialize();
  //Runs main loop of program and starts simulation thread
  void Loop();
  void Poll();
  //Needs work for better encapsulation
  void RotateCamera(int direction);
  void ChangeCameraTarget();
  MVC::Simulation * m_simulation;
  MVC::Render::Renderer * m_renderer;
private:
  //FOr Camera translation. Needs rework for better flow.
  Timer m_timer;
  //For concurency between both threads
  MVC::ConcurContr m_cncr_ctrl;
  std::string      m_dataFolder;
  std::thread      sim_thread;
  cfg::Master      m_config;
};

