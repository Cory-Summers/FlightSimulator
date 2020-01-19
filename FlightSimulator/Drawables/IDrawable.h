#pragma once
#include <memory>

#include "entity.h"
#include "../OpenGL/Mesh.h"
#include "../Math/transform.h"
#include "../OpenGL/Camera.h"
namespace OpenGL {
  class IDrawable : public Entity
  {
  public:
    virtual void Initialize(GLuint const &)   = 0;
    virtual void Draw(Camera &) = 0;
    virtual void Destroy()      = 0;
    inline Transform& GetTransform() { return m_transform; };
  protected:
    IDrawable() : m_transform() {}
    OpenGL::Transform m_transform;
  private:
  };

}