#pragma once
#include "ConcurrencyController.h"
#include "RendererView.h"
#include "ObjectPool.h"
#include "config.h"
#include "Camera.h"
#include "RenderObject.h"
#include "FrameTimer.h"
#include "Simulation.h"
#include <vector>
namespace MVC::Render {
  using VerticeVector = std::vector<glm::vec3>;
  class Renderer
  {
  public:
    Renderer();
    void Initialize();
    void SetCncrCtrl(ConcurContr& obj) { cncr_ctrl = &obj; }
    GLFWwindow& GetWindow();
    OpenGL::Camera& GetCamera() { return m_camera; }
    void MouseMoveEvent(glm::vec2 mouse_pos);
    void RenderScene(MVC::Simulation & sim);
    void ClearBuffer();
  protected:
    ConcurrencyController* cncr_ctrl = nullptr;
    GLFWwindow* m_window;

    //ObjectPool<sf::CircleShape> m_sphere;
    std::vector<VerticeVector> objs;
    GLuint ProgramID;
    GLuint vertexbuffer;
    OpenGL::Camera m_camera;
    OpenGL::RenderObject m_cube, m_obj, jupiter;
    cfg::Master m_config;
    FrameTimer m_timer;
  private:
    int CreateContext() noexcept;
    void InitGLSettings() noexcept;
  };

}
