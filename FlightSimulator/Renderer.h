#pragma once
#include <vector>

#include "ConcurrencyController.h"
#include "Utility/config.h"
#include "OpenGL/Camera.h"
#include "Drawables/RenderObject.h"
#include "Simulation.h"
#include "Drawables/PlanetRender.h"
namespace MVC::Render {
  using VerticeVector = std::vector<glm::vec3>;
  class Renderer
  {
  public:
    Renderer();
    void Initialize(MVC::Simulation &);
    void SetCncrCtrl(ConcurContr& obj) { cncr_ctrl = &obj; }
    GLFWwindow& GetWindow();
    OpenGL::Camera& GetCamera() { return m_camera; }
    void MouseMoveEvent(glm::vec2 mouse_pos);
    void RenderScene(MVC::Simulation & sim);
    std::vector<std::shared_ptr<Render::PlanetRender>> const& GetPlanets() { return planets; }
    void ClearBuffer();
  protected:
    ConcurrencyController* cncr_ctrl = nullptr;
    GLFWwindow* m_window;

    //ObjectPool<sf::CircleShape> m_sphere;
    std::vector<VerticeVector> objs;
    GLuint ProgramID;
    GLuint vertexbuffer;
    OpenGL::Camera m_camera;
    std::vector<std::shared_ptr<Render::PlanetRender>> planets;
    OpenGL::RenderObject center, north;
    cfg::Master m_config;
  private:
    int CreateContext() noexcept;
    void InitGLSettings() noexcept;
  };

}
