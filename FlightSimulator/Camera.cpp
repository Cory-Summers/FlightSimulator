#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
constexpr glm::vec3 CENTER = glm::vec3(0.f, 0.f, 0.f);
OpenGL::Camera::Camera()
  : m_config({1920, 1080, 0, 90})
  , UP(0.f, 1.f, 0.f)
{
  m_position = { 4.0f,   3.0f, 3.0f };
  FromEuler(0.0f, -0.05f, -1.0f);
}

OpenGL::Camera::Camera(cfg::Window const& config) 
  : m_config(config)
  , UP(0.f, 1.f, 0.f)
{
  m_position = { 4.0f,  3.0f, 3.0f };
  FromEuler(0.0f, -.045f, -1.0f);
}

void OpenGL::Camera::LoadProjection(float const fov, float const aspect, float const near_unit, float const far_unit)
{
  m_projection = glm::perspective(fov, aspect, near_unit, far_unit);
  UpdateViewMat();
}



void OpenGL::Camera::UpdateViewMat()
{
  m_view_mat = glm::lookAt(m_position, CENTER, UP);
  m_model_mat = glm::mat4(1.0f);
  m_mvp = m_projection * m_view_mat * m_model_mat;
}

glm::mat4 OpenGL::Camera::GetWorldToViewMat() const
{
  return glm::lookAt(m_position, m_position + m_view_direction, glm::vec3(0,1,0));
}

void OpenGL::Camera::Rotate(float degree, Axis axis)
{
  switch (axis) {
  case X_AXIS:
    m_position = glm::rotateX(m_position, glm::radians(degree));
    break;
  case Y_AXIS:
    m_position = glm::rotateY(m_position, glm::radians(degree));
    break;
  case Z_AXIS:
    m_position = glm::rotateZ(m_position, glm::radians(degree));
    break;
  }
  UpdateViewMat();
}

void OpenGL::Camera::Update()
{
  glm::vec3 lightPos = glm::vec3(4, 4, 4);
  glUniform3f(m_light_id, lightPos.x, lightPos.y, lightPos.z);
  glUniformMatrix4fv(m_matrix_id, 1, GL_FALSE, &(m_mvp[0][0]));
  glUniformMatrix4fv(m_model_id,  1, GL_FALSE, &(m_model_mat[0][0]));
  glUniformMatrix4fv(m_view_id,   1, GL_FALSE, &(m_view_mat[0][0]));
}

void OpenGL::Camera::MouseUpdate(const glm::vec2& mouse_pos)
{
  glm::vec2 mouse_delta = mouse_pos - old_mouse_pos;
  m_view_direction = glm::mat3(glm::rotate(mouse_delta.x, UP)) * m_view_direction;

  old_mouse_pos = mouse_pos;
}

void OpenGL::Camera::GetUniform(std::string uniform)
{
  this->m_matrix_id = glGetUniformLocation(m_program_id, uniform.c_str());
  this->m_view_id   = glGetUniformLocation(m_program_id, "V");
  this->m_model_id  = glGetUniformLocation(m_program_id, "M");

  glUseProgram(m_program_id);
  this->m_light_id  = glGetUniformLocation(m_program_id, "LightPosition_worldspace");
}


