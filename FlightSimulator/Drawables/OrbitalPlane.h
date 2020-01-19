#pragma once
#include "../Simulation/planet-class.h"
#include "../OpenGL/opengl-tools.h"
#include "../OpenGL/Camera.h"
#include "../Math/transform.h"
namespace OpenGL {
  class OrbitalPlane
  {
    struct Ellipse
    {
      Ellipse();
      Ellipse(Physics::StateElements const &);
      float semi_major;
      float semi_minor;
      float perigee;
      float apogee;
    };
    int i = sizeof(Ellipse);
  public:
    OrbitalPlane();
    OrbitalPlane(GLuint prog_id, std::weak_ptr<Kepler::Planet>&, size_t segments = 64);
    void Initialize();
    void Draw(OpenGL::Camera &);
  private:
    void CalcSegments();
    void CalcEllipse(Ellipse &) const;
    //void CalcAscendingNode();
    //void CalcInclination();
    std::vector<glm::vec3>        m_vertex;
    std::weak_ptr<Kepler::Planet> m_planet;
    Physics::StateElements        m_elements;
    Transform                     m_transform;
    size_t m_segments;
    GLuint program_id;
    GLuint buffer_id;
    GLuint model_id;
  };
}