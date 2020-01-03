#include "opengl-tools.h"
#include <array>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "Model.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace  OpenGL {

  void LoadObj_ReadFile(std::string const& file_name, OBJData&);
  void   LoadFromObj(std::string const& file_name, Model& model)
  {
    LoadFromObj(file_name, model.obj_data);
    //loadOBJ(file_name.c_str(), model.obj_data.vertices, model.obj_data.uvs, model.obj_data.normals);
  }
  void   LoadFromObj(std::string const& file_name, OBJData& obj_data)
  {
    OBJData* temp_data = new OBJData();
    LoadObj_ReadFile(file_name, *temp_data);
    for (size_t i = 0; i < temp_data->vertex_idx.size(); i++) {

      // Get the indices of its attributes
      unsigned int vertexIndex = temp_data->vertex_idx[i];
      unsigned int uvIndex = temp_data->uv_idx[i];
      unsigned int normalIndex = temp_data->normal_idx[i];

      // Get the attributes thanks to the index
      glm::vec3 vertex = temp_data->vertices[vertexIndex - 1];
      glm::vec2 uv = temp_data->uvs[uvIndex - 1];
      glm::vec3 normal = temp_data->normals[normalIndex - 1];

      // Put the attributes in buffers
      obj_data.vertices.push_back(vertex);
      obj_data.uvs.push_back(uv);
      obj_data.normals.push_back(normal);
    }
    delete temp_data;
  }
  void   LoadObj_ReadFile(std::string const& file_name, OBJData& obj_data)
  {
    std::array<char, 128> line_header;
    FILE* file = fopen(file_name.c_str(), "r");
    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
    glm::vec3 vertex;
    glm::vec2 uv;
    int result;
    if (file == NULL)
    {
      std::cout << "FAILURE: Can't open file \"" << file_name << "\"!\n";
    }
    while (1)
    {
      result = fscanf(file, "%s", line_header.data());
      if (result == EOF)
        break;
      if (strcmp(line_header.data(), "v") == 0)
      {
        fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
        obj_data.vertices.push_back(vertex);
      }
      else if (strcmp(line_header.data(), "vt") == 0)
      {
        fscanf(file, "%f %f\n", &uv.x, &uv.y);
        uv.y = -uv.y;
        obj_data.uvs.push_back(uv);
      }
      else if (strcmp(line_header.data(), "vn") == 0)
      {
        fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
        obj_data.normals.push_back(vertex);
      }
      else if (strcmp(line_header.data(), "f") == 0)
      {
        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
        obj_data.vertex_idx.push_back(vertexIndex[0]);
        obj_data.vertex_idx.push_back(vertexIndex[1]);
        obj_data.vertex_idx.push_back(vertexIndex[2]);
        obj_data.uv_idx.push_back(uvIndex[0]);
        obj_data.uv_idx.push_back(uvIndex[1]);
        obj_data.uv_idx.push_back(uvIndex[2]);
        obj_data.normal_idx.push_back(normalIndex[0]);
        obj_data.normal_idx.push_back(normalIndex[1]);
        obj_data.normal_idx.push_back(normalIndex[2]);
      }
      else {
        fgets(line_header.data(), 256, file);
      }
    }
    fclose(file);

  };
  bool loadOBJ(
    const char* path,
    std::vector<glm::vec3>& out_vertices,
    std::vector<glm::vec2>& out_uvs,
    std::vector<glm::vec3>& out_normals
  ) {
    printf("Loading OBJ file %s...\n", path);

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;


    FILE* file = fopen(path, "r");
    if (file == NULL) {
      printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
      getchar();
      return false;
    }

    while (1) {

      char lineHeader[128];
      // read the first word of the line
      int res = fscanf(file, "%s", lineHeader);
      if (res == EOF)
        break; // EOF = End Of File. Quit the loop.

      // else : parse lineHeader

      if (strcmp(lineHeader, "v") == 0) {
        glm::vec3 vertex;
        fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
        temp_vertices.push_back(vertex);
      }
      else if (strcmp(lineHeader, "vt") == 0) {
        glm::vec2 uv;
        fscanf(file, "%f %f\n", &uv.x, &uv.y);
        uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
        temp_uvs.push_back(uv);
      }
      else if (strcmp(lineHeader, "vn") == 0) {
        glm::vec3 normal;
        fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
        temp_normals.push_back(normal);
      }
      else if (strcmp(lineHeader, "f") == 0) {
        std::string vertex1, vertex2, vertex3;
        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
        if (matches != 9) {
          printf("File can't be read by our simple parser :-( Try exporting with other options\n");
          fclose(file);
          return false;
        }
        vertexIndices.push_back(vertexIndex[0]);
        vertexIndices.push_back(vertexIndex[1]);
        vertexIndices.push_back(vertexIndex[2]);
        uvIndices.push_back(uvIndex[0]);
        uvIndices.push_back(uvIndex[1]);
        uvIndices.push_back(uvIndex[2]);
        normalIndices.push_back(normalIndex[0]);
        normalIndices.push_back(normalIndex[1]);
        normalIndices.push_back(normalIndex[2]);
      }
      else {
        // Probably a comment, eat up the rest of the line
        char stupidBuffer[1000];
        fgets(stupidBuffer, 1000, file);
      }

    }

    // For each vertex of each triangle
    for (unsigned int i = 0; i < vertexIndices.size(); i++) {

      // Get the indices of its attributes
      unsigned int vertexIndex = vertexIndices[i];
      unsigned int uvIndex = uvIndices[i];
      unsigned int normalIndex = normalIndices[i];

      // Get the attributes thanks to the index
      glm::vec3 vertex = temp_vertices[vertexIndex - 1];
      glm::vec2 uv = temp_uvs[uvIndex - 1];
      glm::vec3 normal = temp_normals[normalIndex - 1];

      // Put the attributes in buffers
      out_vertices.push_back(vertex);
      out_uvs.push_back(uv);
      out_normals.push_back(normal);

    }
    fclose(file);
    return true;
  }
  
  int InitGLFW(int64_t unused)
  {
    if (!glfwInit())
    {
      fprintf(stderr, "Failed to initialize GLFW\n");
      return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return 0;
  }
  int CreateWindow(GLFWwindow  ** output, const uint32_t x, const uint32_t y, std::string const& name, GLFWmonitor* monitor, GLFWwindow* shared)
  {
    GLFWwindow* temp = nullptr;
    temp = glfwCreateWindow(x, y, name.c_str(), monitor, shared);
    if (temp == nullptr) {
      fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
      glfwTerminate();
      output = nullptr;
      return -1;
    }
    *output = temp;
    return 0;
  }

};