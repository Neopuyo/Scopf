#pragma once

#include <tests_ft_glm.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <filesystem>

#define OBJ_DEFAULT_NAME "42"
#define OBJ_DEFAULT_DIR "../res/obj/"
#define OBJ_DEFAULT_EXTENSION ".obj"

#define TEXTURE_DEFAULT_NAME "poney"
#define TEXTURE_DEFAULT_DIR "../res/textures/"
#define TEXTURE_DEFAULT_EXTENSION ".bmp"

#define SHADER_FILE "../res/shaders/basic_shader.glsl"

#ifdef TEST_MODE
  #define DEBUG(x) x
#else
  #define DEBUG(x)
#endif

namespace Path {

  struct Data {
    const std::string objFilePath;
    const std::string textureFilePath;

    Data(const std::string &objFilePath, const std::string &textureFilePath) : objFilePath(objFilePath), textureFilePath(textureFilePath) {}
  };

  enum class Kind {
    OBJECT,
    TEXTURE
  };

  Data parseInputsArgs(int ac, char **av);
};


void launchTests();

void fillUpColors(std::vector<ft_glm::vec3> &colors, unsigned int count);
void fillUpUVs(std::vector<ft_glm::vec2> &uvs, const std::vector<ft_glm::vec3> &vertices, const ft_glm::mat4 &projectionMatrix, const ft_glm::mat4 &viewMatrix);