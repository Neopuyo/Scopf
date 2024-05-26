#include "utils.h"

static std::vector<ft_glm::vec3> _getColorPalette();
static std::string _parseAnArg(std::string const &av, Path::Kind kind);

void launchTests() {

  std::vector<UnitTest> unitTests = {
    test_ft_glm_01,
    test_ft_glm_02,
    test_ft_glm_03,
    test_ft_glm_04,
  };

  std::cout << "OpenGL version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "-----------------------------------------" << std::endl;

  for (unsigned int i = 0; i < unitTests.size(); i++) {
    bool result = unitTests[i]();
    if (!result) {
      std::cout << "Test matrices 0" << i + 1 << "  \033[1;31mfailed\033[0m" << std::endl;
      exit(-1);
    } else {
      std::cout << "Test matrices 0" << i + 1 << " \033[1;32mOK!\033[0m" << std::endl;
    }
  }

};

void fillUpColors(std::vector<ft_glm::vec3> &colors, unsigned int count) {
  std::vector<ft_glm::vec3> colorPalette = _getColorPalette();

  unsigned int index = 0;
  for (unsigned int i = 0 ; i < count; i++) {
    colors.push_back(colorPalette[index]);
    index++;
    if (index >= colorPalette.size())
      index = 0;
  }
}

// Each triplet will make a triangle color
static std::vector<ft_glm::vec3> _getColorPalette() {
  std::vector<ft_glm::vec3> colorPalette = {
    // glm::vec3(0.997f,  0.513f,  0.064f),
    // glm::vec3(0.945f,  0.719f,  0.592f),
    // glm::vec3(0.543f,  0.021f,  0.978f),

    // glm::vec3(0.279f,  0.317f,  0.505f),
    // glm::vec3(0.167f,  0.620f,  0.077f),
    // glm::vec3(0.347f,  0.857f,  0.137f),
    
    // glm::vec3(0.406f,  0.615f,  0.116f),
    // glm::vec3(0.971f,  0.572f,  0.833f),
    // glm::vec3(0.279f,  0.317f,  0.505f),
    
    // glm::vec3(0.302f,  0.455f,  0.848f),
    // glm::vec3(0.517f,  0.713f,  0.338f),
    // glm::vec3(0.820f,  0.883f,  0.371f),

    ft_glm::vec3(0.1f,  0.1f,  0.1f),
    ft_glm::vec3(0.1f,  0.1f,  0.1f),
    ft_glm::vec3(0.1f,  0.1f,  0.1f),

    ft_glm::vec3(0.2f,  0.2f,  0.2f),
    ft_glm::vec3(0.2f,  0.2f,  0.2f),
    ft_glm::vec3(0.2f,  0.2f,  0.2f),

    ft_glm::vec3(0.3f,  0.3f,  0.3f),
    ft_glm::vec3(0.3f,  0.3f,  0.3f),
    ft_glm::vec3(0.3f,  0.3f,  0.3f),

    ft_glm::vec3(0.4f,  0.4f,  0.4f),
    ft_glm::vec3(0.4f,  0.4f,  0.4f),
    ft_glm::vec3(0.4f,  0.4f,  0.4f),
  };
  return colorPalette;
}

void fillUpUVs(std::vector<ft_glm::vec2> &uvs, const std::vector<ft_glm::vec3> &vertices, const ft_glm::mat4 &projectionMatrix, const ft_glm::mat4 &viewMatrix) {
    if (uvs.size() == 0) {
    for (auto vertex : vertices) {
      // Planar projection - texture
      ft_glm::vec4 vertexPos = ft_glm::vec4(vertex.x, vertex.y, vertex.z, 1.0f);
      ft_glm::vec4 clipPos = projectionMatrix * viewMatrix * vertexPos;
      ft_glm::vec3 texCoords = ft_glm::vec3(clipPos.x / clipPos.w, clipPos.y / clipPos.w, 0.0f);
      uvs.push_back(ft_glm::vec2(texCoords.x, texCoords.y));
    }
  }
}

// Parsing Inputs ~ Path namespace

Path::Data Path::parseInputsArgs(int ac, char **av) {
  std::string objPath;
  std::string texturePath;

  if (ac != 3) {
    objPath = _parseAnArg(OBJ_DEFAULT_NAME, Path::Kind::OBJECT);
    texturePath = _parseAnArg(TEXTURE_DEFAULT_NAME, Path::Kind::TEXTURE);
  } else {
    objPath = _parseAnArg(av[1], Path::Kind::OBJECT);
    texturePath = _parseAnArg(av[2], Path::Kind::TEXTURE);
  }

  return Path::Data(objPath, texturePath);
}

static std::string _parseAnArg(std::string const &av, Path::Kind kind) {
  bool isValid = std::all_of(av.begin(), av.end(), [](char c) {
    return std::isalnum(c) || c == '_';
  });

  std::string name = isValid ? av : (kind == Path::Kind::OBJECT ? OBJ_DEFAULT_NAME : TEXTURE_DEFAULT_NAME);
  std::string path = kind == Path::Kind::OBJECT ? OBJ_DEFAULT_DIR : TEXTURE_DEFAULT_DIR;
  path+= name;
  path+= kind == Path::Kind::OBJECT ? OBJ_DEFAULT_EXTENSION : TEXTURE_DEFAULT_EXTENSION;
  return path;
}

