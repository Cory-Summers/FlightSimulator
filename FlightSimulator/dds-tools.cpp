#include "DDS-tools.h"
#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

namespace OpenGL::DDS
{
  Header ReadHeader(std::ifstream&);
  std::vector<uint8_t> ReadContents(std::ifstream&, DDS::Header&);
  GLuint CreateTexture(DDS::Header, std::vector<uint8_t>&);
  GLuint Loader(std::string const& file_name)
  {
    std::ifstream file(file_name, std::ios::binary);
    DDS::Header header;
    std::vector<uint8_t> contents;
    GLuint id;

    if (!file.is_open()) { throw "Can't Open File!"; }
    header = ReadHeader(file);
    contents = ReadContents(file, header);
    id = CreateTexture(header, contents);
    return id;
  }
  DDS::Header ReadHeader(std::ifstream& file)
  {
    std::array<uint8_t, 124> header;
    std::array<char, 4> type_code;
    DDS::Header temp;
    file.read(type_code.data(), 4);
    if (strncmp(type_code.data(), "DDS ", 4) != 0)
    {
      throw "NOT DDS FILE";
    }
    file.read((char*)header.data(), 124);
    temp.height = *(unsigned int*) & (header[8]);
    temp.width = *(unsigned int*) & (header[12]);
    temp.linear_size = *(unsigned int*) & (header[16]);
    temp.mip_map_count = *(unsigned int*) & (header[24]);
    temp.four_cc = *(unsigned int*) & (header[80]);
    return temp;
  }
  std::vector<uint8_t> ReadContents(std::ifstream& file, DDS::Header& header)
  {
    size_t contents_size = header.mip_map_count > 1 ? header.linear_size * 2 : header.linear_size;
    std::vector<uint8_t> contents(contents_size);
    file.read((char*) & (contents.front()), contents_size);
    file.close();
    return contents;
  }

  GLuint CreateTexture(DDS::Header header, std::vector<uint8_t>& contents)
  {

    GLuint texture_id, block_size, offset = 0, format;
    GLuint components = (header.four_cc == FOURCC_DXT1) ? 3 : 4;
    switch (header.four_cc)
    {
    case FOURCC_DXT1:
      format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
      break;
    case FOURCC_DXT3:
      format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
      break;
    case FOURCC_DXT5:
      format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
      break;
    }
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    block_size = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    for (GLuint level = 0; level < header.mip_map_count && (header.width || header.height); ++level)
    {
      GLuint size = ((header.width + 3) / 4) * ((header.height + 3) / 4) * block_size;
      glCompressedTexImage2D(GL_TEXTURE_2D, level, format, header.width, header.height,
        0, size, contents.data() + offset);

      offset += size;
      header.width /= 2;
      header.height /= 2;

      // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
      if (header.width < 1) header.width = 1;
      if (header.height < 1) header.height = 1;
    }
    return texture_id;
  }

  GLuint loadDDS(const char* imagepath) {

    unsigned char header[124];

    FILE* fp;

    /* try to open the file */
    fp = fopen(imagepath, "rb");
    if (fp == NULL) {
      printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar();
      return 0;
    }

    /* verify the type of file */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
      fclose(fp);
      return 0;
    }

    /* get the surface desc */
    fread(&header, 124, 1, fp);

    unsigned int height = *(unsigned int*) & (header[8]);
    unsigned int width = *(unsigned int*) & (header[12]);
    unsigned int linearSize = *(unsigned int*) & (header[16]);
    unsigned int mipMapCount = *(unsigned int*) & (header[24]);
    unsigned int fourCC = *(unsigned int*) & (header[80]);


    unsigned char* buffer;
    unsigned int bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    /* close the file pointer */
    fclose(fp);

    unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch (fourCC)
    {
    case FOURCC_DXT1:
      format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
      break;
    case FOURCC_DXT3:
      format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
      break;
    case FOURCC_DXT5:
      format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
      break;
    default:
      free(buffer);
      return 0;
    }

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* load the mipmaps */
    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
      unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
      glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
        0, size, buffer + offset);

      offset += size;
      width /= 2;
      height /= 2;

      // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
      if (width < 1) width = 1;
      if (height < 1) height = 1;

    }

    free(buffer);

    return textureID;


  }
};
