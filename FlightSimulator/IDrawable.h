#pragma once
#include "Mesh.h"
#include "transform.h"
#include "entity.h"
#include "Camera.h"
#include <memory>
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