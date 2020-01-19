#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "../Drawables/IDrawable.h"
constexpr glm::vec3 CENTER = glm::vec3(0.f, 0.f, 0.f);
template <typename T>
bool IsEmpty(std::weak_ptr<T> const& weak) {
  using wt = std::weak_ptr<T>;
  return !weak.owner_before(wt{}) && !wt{}.owner_before(weak);
}
OpenGL::Camera::Camera()
  : m_config({ 1920, 1080, 0, 90 })
  , UP(0.f, 1.f, 0.f)
  , m_transform(glm::vec3(0, 0, 4), glm::vec3(0.f, 0.f, glm::pi<float>() * 2 / 3))
  , m_target()
{
}

OpenGL::Camera::Camera(cfg::Window const& config) 
  : m_config(config)
  , UP(0.f, 1.f, 0.f)
  , m_transform(glm::vec3(0, 0, 4), glm::vec3(0.f, 0.f, glm::pi<float>() * 2 / 3))
  , m_target()
{
}

void OpenGL::Camera::LoadProjection(float const fov, float const aspect, float const near_unit, float const far_unit)
{
  m_projection = glm::perspective(fov, aspect, near_unit, far_unit);
  UpdateViewMat();
}



void OpenGL::Camera::UpdateViewMat()
{
  m_view_mat = GetWorldToViewMat();
}

glm::mat4 OpenGL::Camera::GetWorldToViewMat() const
{
  if(IsEmpty(m_target))
    return glm::lookAt(m_transform.position, glm::vec3(0.f, 0.f, 0.f),UP);
  else
    return glm::lookAt(
      m_transform.position + m_target.lock()->GetTransform().position, 
      m_target.lock()->GetTransform().position, 
      UP);
}

void OpenGL::Camera::Rotate(float degree, Axis axis)
{
  switch (axis) {
  case X_AXIS:
    m_transform.position = glm::rotateX(m_transform.position, glm::radians(degree));
    break;
  case Y_AXIS:
    m_transform.position = glm::rotateY(m_transform.position, glm::radians(degree));
    break;
  case Z_AXIS:
    m_transform.position = glm::rotateZ(m_transform.position, glm::radians(degree));
    break;
  }
  UpdateViewMat();
}

glm::mat4 OpenGL::Camera::GetMVP(glm::mat4 const& model_mat) const
{
  glm::mat4 mvp = m_projection * m_view_mat * model_mat;
  return mvp;
}

void OpenGL::Camera::SetTarget(std::weak_ptr<IDrawable> const& target)
{
  auto& new_center = target.lock()->GetTransform().position;
  if (IsEmpty(m_target))
    m_transform.position += new_center;
  else
    m_transform.position += new_center - m_target.lock()->GetTransform().position;
  m_target = target;
}

void OpenGL::Camera::Update()
{
  glm::vec3 lightPos = glm::vec3(0, 5, 0);
  UpdateViewMat();
  glUniform3f(m_light_id, lightPos.x, lightPos.y, lightPos.z);
  glUniformMatrix4fv(m_view_id, 1, GL_FALSE, &(m_view_mat[0][0]));
}

void OpenGL::Camera::MouseUpdate(const glm::vec2& mouse_pos)
{

}

void OpenGL::Camera::GetUniform(std::string uniform)
{
  this->m_matrix_id = glGetUniformLocation(m_program_id, "MVP");
  this->m_view_id   = glGetUniformLocation(m_program_id, "V");
  glUseProgram(m_program_id);
  this->m_light_id  = glGetUniformLocation(m_program_id, "LightPosition_worldspace");
}


