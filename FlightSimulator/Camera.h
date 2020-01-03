#pragma once
#include "Frustum.h"
#include "entity.h"
#include "transform.h"
#include "config.h"
namespace MVC::Render {
  class Renderer;
};
namespace OpenGL {
  class Camera : public Entity, public Transform
  {
    using const_ref = glm::mat4 const&;
  public:
    friend class MVC::Render::Renderer;
    enum Axis {
      X_AXIS = 0,
      Y_AXIS = 1,
      Z_AXIS = 2
    };
    Camera();
    Camera(cfg::Window const&);
    void LoadProjection(
      float const fov = glm::radians(45.f), 
      float const aspect = 16.f / 9.f,
      float const near_unit = .1f,
      float const far_unit = 100.f);
    void SetProgramID(GLuint const& id) noexcept { m_program_id = id; }
    void SetConfig(cfg::Window const& con) { m_config = con; }
    void UpdateViewMat();
    glm::mat4 GetWorldToViewMat() const;
    void Rotate(float, Axis axis = Y_AXIS);
    void Update();
    void MouseUpdate(const glm::vec2& mouse_pos);
    
  private:
    void GetUniform(std::string = std::string("MVP"));

  protected:
    GLuint m_program_id;
    GLuint m_matrix_id;
    GLuint m_model_id;
    GLuint m_view_id;
    GLuint m_light_id;
    glm::mat4 m_projection;
    glm::mat4 m_view_mat;
    glm::mat4 m_model_mat;
    glm::mat4 m_mvp;
    glm::vec3 m_view_direction;
    cfg::Window m_config;
    glm::vec2 old_mouse_pos;
    const glm::vec3 UP;
  };

}
