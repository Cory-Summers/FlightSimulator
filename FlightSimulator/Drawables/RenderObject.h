#pragma once
#include <array>

#include "IDrawable.h"
#include "../OpenGL/texture.h"
namespace OpenGL {
  enum ObjBufIdx {
    OB_MODEL_ID = 0,
    OB_MATRIX_ID = 1,
    OB_IDX_SIZE = 3
  };
  class RenderObject :
    public IDrawable
  {
  public:
    RenderObject();
    RenderObject(
      GLuint prog_id,
      std::string const& mesh_file,
      std::string const& texture_file,
      std::string const& mesh_uniform = "M",
      std::string const& texture_uniform = "myTextureSampler"
    );
    void Initialize(GLuint const & prog_id)  override;
    void Draw(Camera&) override;
    void Destroy()     override;
    ~RenderObject();
  protected:
    glm::mat4  ModelMatrix();
    std::array<GLuint, ObjBufIdx::OB_IDX_SIZE> m_buffer;
    std::shared_ptr<OpenGL::Mesh>    m_mesh;
    std::shared_ptr<OpenGL::Texture> m_texture;
  private:
  };

};
