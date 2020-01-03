#pragma once

#include "kepler-physics.h"
#include "planet-class.h"
#include "ObjectPool.h"
#include "PlanetObject.h"
namespace MVC::Render {
  class Renderer;
  class ViewRenderer
  {
  public:
    ViewRenderer(Renderer &);
  protected:
    Vector3D  camera_pos;
   // sf::View  m_view;
    Renderer* m_parent;
    ObjectPool<WorldObjectBase> m_planets;
  };
}

