#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "glad.h"
#include <GLFW/glfw3.h>
#include "errorHandling.h"

#define BMP_HEADER_SIZE 54
#define RGB 3

struct BMPmeta {
  GLuint dataPos;
  GLuint imageSize;
  GLuint imageWidth;
  GLuint imageHeight;
};

class BMPLoader {
  private:
    GLuint m_textureID;
    BMPmeta m_meta;

    GLuint _loadBMP(const std::string &bmpFile);
    bool _checkFormat(const std::string &bmpFile);
    GLuint _accessImageData(const std::string &bmpFile);


  public:

    BMPLoader(const std::string &bmpFile);
    ~BMPLoader();

    void Bind();
    inline GLuint getTextureID() const { return m_textureID; }

};