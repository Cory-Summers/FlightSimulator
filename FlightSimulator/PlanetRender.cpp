#include "PlanetRender.h"

MVC::Render::PlanetRender::PlanetRender()
{
}

MVC::Render::PlanetRender::PlanetRender(GLuint const& prog_id, std::weak_ptr<Kepler::Planet> planet)
  : m_sim_obj(planet)
  , RenderObject(prog_id, "resources/Sphere.obj", "resources/uvmap.DDS")
  , m_plane(prog_id, planet)
{
  m_name = planet.lock()->GetName();
  m_transform = OpenGL::Transform();
  m_buffer.fill(-1);
  Initialize(prog_id);
  m_plane.Initialize();
}

void MVC::Render::PlanetRender::Draw(OpenGL::Camera& camera)
{
  Vector3D vec = m_sim_obj.lock()->GetVector().p;
  vec *= render_scale;
  m_transform.position = { vec.x, vec.z, vec.y };
  glm::mat4 model_mat = this->ModelMatrix();
  glm::mat4 MVP = camera.GetMVP(model_mat);
  glUniformMatrix4fv((camera.GetMatrixID()), 1, GL_FALSE, &MVP[0][0]);
  glUniformMatrix4fv(m_buffer[OpenGL::OB_MODEL_ID], 1, GL_FALSE, &model_mat[0][0]);
  if (m_texture) m_texture->Bind();
  m_mesh->Draw();
  m_plane.Draw(camera);
}
