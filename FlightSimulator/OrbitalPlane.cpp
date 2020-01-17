#include "OrbitalPlane.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/quaternion.hpp>
#define SIM_SCALE 1e7
OpenGL::OrbitalPlane::OrbitalPlane()
  : m_vertex()
  , m_planet()
  , m_elements()
  , m_transform()
{
}

OpenGL::OrbitalPlane::OrbitalPlane(GLuint prog_id, std::weak_ptr<Kepler::Planet>& planet, size_t segments)
  : m_vertex()
  , m_planet(planet)
  , m_segments(segments)
  , m_elements(planet.lock()->GetVector().ToStateElements(planet.lock()->GetParent()->GetMu()))
  , m_transform()
  , program_id(prog_id)
{
}

void OpenGL::OrbitalPlane::Initialize()
{
  CalcSegments();
  buffer_id = OpenGL::CreateBuffer<glm::vec3>(m_vertex);
  model_id = glGetUniformLocation(program_id, "M");
}

void OpenGL::OrbitalPlane::CalcSegments()
{
  std::vector<glm::vec3> circle_segment;
  Ellipse ellipse(m_elements);
  double rads = (2.0 * glm::pi<double>()) / static_cast<double>(m_segments);
  double theta = 0;
  double scale = ellipse.semi_major / ellipse.semi_minor;
  circle_segment.resize(m_segments);
  for (size_t i = 0; i < m_segments; ++i)
  {
    circle_segment[i] = { ellipse.semi_minor * cos(theta), 0.0f, ellipse.semi_minor * sin(theta) };
    theta += rads;
  }
  for (auto& seg : circle_segment)
    seg.x *= scale;
  m_vertex = circle_segment;
  //m_transform.scale = { ellipse.semi_major, 1.0f, ellipse.semi_minor };
  m_transform.position = { ellipse.perigee - ellipse.semi_major, 0.0f, 0.0f };
  m_transform.rotation = glm::eulerAngleYXZ<float>(
    static_cast<float>(m_elements.r_asc_node) + glm::pi<float>(), 
    static_cast<float>(m_elements.incl),
    0.0f
  );
}

/*
void OpenGL::OrbitalPlane::CalcAscendingNode()
{
  glm::vec3& vert = m_vertex[0];
  float theta = m_elements.r_asc_node - (glm::pi<float>() / 2.0f);
  for (size_t i = 0; i < m_segments; ++i)
  {
    vert = m_vertex[i];
    vert.x = vert.x * std::cosf(theta) - vert.z * std::sinf(theta);
    vert.z = vert.z * std::cosf(theta) + vert.x * std::sinf(theta);
  }
}

void OpenGL::OrbitalPlane::CalcInclination()
{

}

*/
void OpenGL::OrbitalPlane::Draw(Camera & camera)
{
  glm::mat4 model_mat(1.0f);
  model_mat =
    glm::scale(m_transform.scale) *
    glm::translate(model_mat, m_transform.position) *
    glm::toMat4(m_transform.rotation);
  glm::mat4 MVP = camera.GetMVP(model_mat);
  glUniformMatrix4fv((camera.GetMatrixID()), 1, GL_FALSE, &MVP[0][0]);
  glUniformMatrix4fv(model_id, 1, GL_FALSE, &model_mat[0][0]);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  glVertexAttribPointer(
    0,                  // attribute
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
  );
  glDrawArrays(GL_LINE_LOOP, 0, m_vertex.size());
  glDisableVertexAttribArray(0);
}

OpenGL::OrbitalPlane::Ellipse::Ellipse(Physics::StateElements const & elem)
  : semi_major(elem.semi_major / (SIM_SCALE))
  , semi_minor((elem.semi_major / (SIM_SCALE)) * std::sqrtf(1.f - static_cast<float>(elem.ecc)))
  , perigee((1.f - elem.ecc) * (elem.semi_major / (SIM_SCALE)))
  , apogee((1.f + elem.ecc)* (elem.semi_major / (SIM_SCALE)))
{
}
