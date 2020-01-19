#pragma once
#include "RenderObject.h"
#include "../Simulation/planet-class.h"
#include "OrbitalPlane.h"
namespace MVC::Render {
  class PlanetRender :
    public OpenGL::RenderObject
  {
    public:
      PlanetRender();
      PlanetRender(GLuint const &, std::weak_ptr<Kepler::Planet>);
      void Draw(OpenGL::Camera&) override;
  protected:
    std::weak_ptr<Kepler::Planet> m_sim_obj;
    double render_scale = 1e-7;
    OpenGL::OrbitalPlane m_plane;
  };

};