#include "utils.h"

static std::vector<ft_glm::vec3> getColorPalette();

void launchTests() {

  std::vector<UnitTest> unitTests = {
    test_ft_glm_01,
    test_ft_glm_02,
    test_ft_glm_03,
    test_ft_glm_04,
  };

  for (unsigned int i = 0; i < unitTests.size(); i++) {
    bool result = unitTests[i]();
    if (!result) {
      std::cout << "Test matrices 0" << i + 1 << " failed" << std::endl;
      exit(-1);
    }
  }

};

void fillUpColors(std::vector<ft_glm::vec3> &colors, unsigned int count) {
  std::vector<ft_glm::vec3> colorPalette = getColorPalette();

  unsigned int index = 0;
  for (unsigned int i = 0 ; i < count; i++) {
    colors.push_back(colorPalette[index]);
    index++;
    if (index >= colorPalette.size())
      index = 0;
  }
}

static std::vector<ft_glm::vec3> getColorPalette() {
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

