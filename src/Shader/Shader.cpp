#include "Shader.h"



Shader::Shader(const std::string &filepath) : m_filepath(filepath), m_rendererID(0) {
  ShaderProgramSource sources = _parseShader(filepath);

  std::cout << sources << std::endl; // [!] display to debug

  m_rendererID = _createShader(sources.vertex, sources.fragment);
}

Shader::~Shader() {
  LOGCHECK(glDeleteProgram(m_rendererID));
}

void Shader::bind() const {
  LOGCHECK(glUseProgram(m_rendererID));
}

void Shader::unbind() const {
  LOGCHECK(glUseProgram(0));
}

// Set uniforms
void Shader::setUniform1i(const std::string &name, int value) {
  LOGCHECK(glUniform1i(_getUniformLocation(name), value));
}

void Shader::setUniform1f(const std::string &name, float value) {
  LOGCHECK(glUniform1f(_getUniformLocation(name), value));
}

void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
  LOGCHECK(glUniform4f(_getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformMat4f(const std::string &name, const ft_glm::mat4 &matrix) {
  // [+][!] subscript ??
  LOGCHECK(glUniformMatrix4fv(_getUniformLocation(name), 1, GL_FALSE, &(matrix.v1.x))); // glm is already openGL specifiq, can use GL_FALSE
}


int Shader::_getUniformLocation(const std::string &name) {
  if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
    return m_uniformLocationCache[name];

  int location = -1;
   LOGCHECK(location = glGetUniformLocation(m_rendererID, name.c_str()));
   if (location < 0)
    std::cout << "[warning] uniform location of '" << name << "' can't be found" << std::endl;

   m_uniformLocationCache[name] = location;
   return location;
}


ShaderProgramSource Shader::_parseShader(const std::string &filepath) {
  std::ifstream stream(filepath);
  
  enum class ShaderType {
    NONE = -1, VERTEX = 0, FRAGMENT = 1
  };

  std::string line;
  std::stringstream ss[2];
  ShaderType type = ShaderType::NONE;
  while (getline(stream, line)) {

    if (line.find("//") != std::string::npos) {
        continue;
    }

    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos)
        type = ShaderType::VERTEX;
      else if (line.find("fragment") != std::string::npos)
        type = ShaderType::FRAGMENT;
    } else {
      // [!] if type is still NONE ?
      if (type != ShaderType::NONE) {
        ss[static_cast<int>(type)] << line << '\n';
      }
    }
  }

  return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::_compileShader(unsigned int type, const std::string &source) {
  unsigned int id = glCreateShader(type);

  // conseille de securiser au cas ou source est free avant qu'on utilise
  // [!] verifier qu'on a bien une copie ainsi (utiliser "=" sur une réf) ?
  std::string sourceDup = source;
  const char *src = sourceDup.c_str();
  // const char *src = source.c_str();

  LOGCHECK(glShaderSource(id, 1 , &src, nullptr)); // https://docs.gl/gl4/glShaderSource
  LOGCHECK(glCompileShader(id)); // [!] dont forget this too :D

  // Handle errors
  int result;
  LOGCHECK(glGetShaderiv(id, GL_COMPILE_STATUS, &result)); // Returns a parameter from a shader object
  if (result == GL_FALSE) {
    int length;
    LOGCHECK(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
    char *message = (char *)alloca(length * sizeof(char)); // allocation sur la stack, pas comme malloc
    LOGCHECK(glGetShaderInfoLog(id, length, &length, message));
    std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
    std::cout << message << std::endl;
  }

  return id;
}


unsigned int Shader::_createShader(const std::string &vertexShader, const std::string &fragmentShadder) {
  unsigned int program;
  LOGCHECK(program = glCreateProgram());
  unsigned int vs = _compileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = _compileShader(GL_FRAGMENT_SHADER, fragmentShadder);

  // Shader are like files to compiles. Once done we can delete it, more or less like *.o files)
  LOGCHECK(glAttachShader(program, vs));
  LOGCHECK(glAttachShader(program, fs));
  LOGCHECK(glLinkProgram(program));
  LOGCHECK(glValidateProgram(program));

  LOGCHECK(glDeleteShader(vs)); // glDetachShader should be technically called -> more info later [?]
  LOGCHECK(glDeleteShader(fs));

  // [!][?] use this instaed of delete ?
  LOGCHECK(glDetachShader(program, vs));
  LOGCHECK(glDetachShader(program, fs));


  return program;
}

/* ----- Displaying Tools ----- */

std::ostream &operator<<(std::ostream &o, const ShaderProgramSource &righty) {
    o << "\033[1;36m#Vertex shader\033[0m" << std::endl;
    o << righty.vertex << std::endl;
    o << "\033[1;36m#Fragment shader\033[0m" << std::endl;
    o << righty.fragment << std::endl;
    return o;
}