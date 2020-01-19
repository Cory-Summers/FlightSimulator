#pragma once

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <glm/glm.hpp>

#include <cstdint>
#include <vector>
namespace OpenGL {
  struct OBJData
  {
    OBJData();
    std::vector<uint16_t> vertex_idx;
    std::vector<uint16_t> uv_idx;
    std::vector<uint16_t> normal_idx;
    std::vector<uint16_t>  indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
  };
  int AssetImportEtay(std::string const& path, OBJData& output);
  int AssetImport(
    std::string const& path,
    OBJData& output
  );

};
