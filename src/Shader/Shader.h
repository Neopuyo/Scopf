#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "glad.h"
#include <GLFW/glfw3.h>
#include "errorHandling.h"

#include <glm/glm.hpp>

struct ShaderProgramSource {
  std::string vertex;
  std::string fragment;
};

class Shader {
  private:
    std::string m_filepath;
    unsigned int m_rendererID;
    // caching for uniforms
    std::unordered_map<std::string, int> m_uniformLocationCache;


  public:
    Shader(const std::string &filepath);
    ~Shader();

    void bind() const;
    void unbind() const;

    // Set uniforms
    void setUniform1i(const std::string &name, int value);
    void setUniform1f(const std::string &name, float value);
    void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
    void setUniformMat4f(const std::string &name, const glm::mat4 &matrix);

  private:
    // [!] const or not? (check it for all this private func)
    int _getUniformLocation(const std::string &name); // not const, modifying cache

    ShaderProgramSource _parseShader(const std::string &filepath);
    unsigned int _compileShader(unsigned int type, const std::string &source);
    unsigned int _createShader(const std::string &vertexShader, const std::string &fragmentShadder);

};


/* ----- Displaying Tools ----- */

std::ostream &operator<<(std::ostream &o, const ShaderProgramSource &righty);