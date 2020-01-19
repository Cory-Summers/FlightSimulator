#include "object-loader.h"
#include "Model.h"
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags
namespace OpenGL
{
  const aiScene* ImportScene(std::string const& path);
  void InitMesh(const aiMesh* mesh, OBJData&);
};
OpenGL::OBJData::OBJData()
  : vertices()
  , uvs()
  , normals()
{
}
int OpenGL::AssetImport(std::string const& path, OBJData& output)
{
  Assimp::Importer importer;
  OBJData* temp = new OBJData();
  const aiScene* scene = importer.ReadFile(path, aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
  if (!scene) {
    fprintf(stderr, importer.GetErrorString());
    return false;
  }
  const aiMesh* mesh = scene->mMeshes[0];
  // Fill vertices positions
  temp->vertices.reserve(mesh->mNumVertices);
  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    aiVector3D pos = mesh->mVertices[i];
    temp->vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
  }
  // Fill vertices texture coordinates
  temp->uvs.reserve(mesh->mNumVertices);
  for (unsigned int k = 0; k < mesh->mNumVertices; k++) {
    aiVector3D UVW = mesh->mTextureCoords[0][k]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
    temp->uvs.push_back(glm::vec2(UVW.x, UVW.y));
  }
  // Fill vertices normals
  temp->normals.reserve(mesh->mNumVertices);
  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    aiVector3D n = mesh->mNormals[i];
    temp->normals.push_back(glm::vec3(n.x, n.y, n.z));
  }
  // Fill face indices
  temp->indices.reserve(3ull * mesh->mNumFaces);
  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    // Assume the model has only triangles.
    temp->indices.push_back(mesh->mFaces[i].mIndices[0]);
    temp->indices.push_back(mesh->mFaces[i].mIndices[1]);
    temp->indices.push_back(mesh->mFaces[i].mIndices[2]);
  }
  // The "scene" pointer will be deleted automatically by "importer"
  output = *temp;
  delete temp;
  return true;
}


const aiScene* OpenGL::ImportScene(std::string const& path)
{
  Assimp::Importer importer;
  const aiScene* temp = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);
  if (temp == nullptr)
    throw "Can't Load Scene!\n";
  return temp;
}
