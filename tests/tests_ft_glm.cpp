#include "tests_ft_glm.h"

void mat4show(const glm::mat4 m, const std::string &name) {
  std::cout << "[------ "<< name<< " ------]" << std::endl;
  for (int i = 0; i < 4; i++) {
    std::cout << "  ";
    for (int j = 0; j < 4; j++) {
      std::cout << std::fixed << std::setprecision(2) << (m[i][j] >= 0 ? " " : "") << m[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

bool compareMatrices(const ft_glm::mat4 &ft_m, const glm::mat4 &m) {
  bool isFailed = false;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (ft_m[i][j] != m[i][j]) {
        std::cout << "ft_m[" << i << "][" << j << "] = " << ft_m[i][j] << " != m[" << i << "][" << j << "] = " << m[i][j] << std::endl;
        isFailed = true;
      }
    }
  }
  return !isFailed;
}

// ------------------------------------------------

bool test_ft_glm_01() {
  // Définition des matrices et des vecteurs
    ft_glm::mat4 matrix1(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    );

    ft_glm::mat4 matrix2(
        16.0f, 15.0f, 14.0f, 13.0f,
        12.0f, 11.0f, 10.0f, 9.0f,
        8.0f, 7.0f, 6.0f, 5.0f,
        4.0f, 3.0f, 2.0f, 1.0f
    );

    ft_glm::vec4 vector1(1.0f, 2.0f, 3.0f, 4.0f);
    ft_glm::vec4 vector2(4.0f, 3.0f, 2.0f, 1.0f);

    // Calcul des résultats attendus
    ft_glm::vec4 expected_result1(
        30.0f, 70.0f, 110.0f, 150.0f
    );

    ft_glm::vec4 expected_result2(
        150.0f, 110.0f, 70.0f, 30.0f
    );

    // Multiplication des matrices et des vecteurs
    ft_glm::vec4 result1 = matrix1 * vector1;
    ft_glm::vec4 result2 = matrix2 * vector2;

    // Comparaison des résultats avec les résultats attendus
    if (result1 == expected_result1 && result2 == expected_result2) {
        std::cout << "Le test a réussi !" << std::endl;
    } else {
        std::cout << "Le test a échoué !" << std::endl;
        std::cout << "Résultat 1 attendu : " << expected_result1 << std::endl;
        std::cout << "Résultat 1 obtenu : " << result1 << std::endl;
        std::cout << "Résultat 2 attendu : " << expected_result2 << std::endl;
        std::cout << "Résultat 2 obtenu : " << result2 << std::endl;
        return false;
    }
    return true;
}


bool test_ft_glm_02() {
  ft_glm::vec3 ft_position(0.0f, 0.0f, 0.0f);
  ft_glm::vec3 ft_target(0.0f, 0.0f, -1.0f);
  ft_glm::vec3 ft_up(0.0f, 1.0f, 0.0f);


  ft_glm::mat4 ft_resultLookAt = ft_glm::lookAt(ft_position, ft_target, ft_up);
  ft_resultLookAt.show("ft_resultLookAt");

  glm::vec3 position(0.0f, 0.0f, 0.0f);
  glm::vec3 target(0.0f, 0.0f, -1.0f);
  glm::vec3 up(0.0f, 1.0f, 0.0f);


  glm::mat4 resultLookAt = glm::lookAt(position, target, up);
  mat4show(resultLookAt, "resultLookAt");

  return compareMatrices(ft_resultLookAt, resultLookAt);

}