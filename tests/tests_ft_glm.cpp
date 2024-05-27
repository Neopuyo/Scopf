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
      if (ft_m[i *4 + j] != m[i][j]) {
        std::cout << "ft_m[" << i << "][" << j << "] = " << ft_m[i * 4 + j] << " != m[" << i << "][" << j << "] = " << m[i][j] << std::endl;
        isFailed = true;
      }
    }
  }
  return !isFailed;
}

void vec4show(const glm::vec4 v, const std::string &name) {
  std::cout << "   "<< name<< " : (";
  std::cout << std::fixed << std::setprecision(2) << v.x << ", ";
  std::cout << std::fixed << std::setprecision(2) << v.y << ", ";
  std::cout << std::fixed << std::setprecision(2) << v.z << ", ";
  std::cout << std::fixed << std::setprecision(2) << v.w << ")" ;
  std::cout << std::endl;

}

bool compareVec4(const ft_glm::vec4 &ft_v, const glm::vec4 &v) {
  bool isFailed = false;
  
  if (ft_v.x != v.x) {
    std::cout << "ft_v.x = " << ft_v.x << " != v.x = " << v.x << std::endl;
    isFailed = true;
  }
  if (ft_v.y != v.y) {
    std::cout << "ft_v.y = " << ft_v.y << " != v.y = " << v.y << std::endl;
    isFailed = true;
  }
  if (ft_v.z != v.z) {
    std::cout << "ft_v.z = " << ft_v.z << " != v.z = " << v.z << std::endl;
    isFailed = true;
  }
  if (ft_v.w != v.w) {
    std::cout << "ft_v.w = " << ft_v.w << " != v.w = " << v.w << std::endl;
    isFailed = true;
  }
  return !isFailed;
}

// ------------------------------------------------

bool test_ft_glm_01() {

  bool isFailed = false;

  ft_glm::mat4 ft_matrix1(
      1.0f, 2.0f, 3.0f, 4.0f,
      5.0f, 6.0f, 7.0f, 8.0f,
      9.0f, 10.0f, 11.0f, 12.0f,
      13.0f, 14.0f, 15.0f, 16.0f
  );

  ft_glm::mat4 ft_matrix2(
      16.0f, 15.0f, 14.0f, 13.0f,
      12.0f, 11.0f, 10.0f, 9.0f,
      8.0f, 7.0f, 6.0f, 5.0f,
      4.0f, 3.0f, 2.0f, 1.0f
  );

  glm::mat4 matrix1(
      1.0f, 2.0f, 3.0f, 4.0f,
      5.0f, 6.0f, 7.0f, 8.0f,
      9.0f, 10.0f, 11.0f, 12.0f,
      13.0f, 14.0f, 15.0f, 16.0f
  );

  glm::mat4 matrix2(
      16.0f, 15.0f, 14.0f, 13.0f,
      12.0f, 11.0f, 10.0f, 9.0f,
      8.0f, 7.0f, 6.0f, 5.0f,
      4.0f, 3.0f, 2.0f, 1.0f
  );

  ft_glm::vec4 ft_vector1(1.0f, 2.0f, 3.0f, 4.0f);
  ft_glm::vec4 ft_vector2(4.0f, 3.0f, 2.0f, 1.0f);
  ft_glm::vec4 ft_result1 = ft_matrix1 * ft_vector1;
  ft_glm::vec4 ft_result2 = ft_matrix2 * ft_vector2;

  glm::vec4 vector1(1.0f, 2.0f, 3.0f, 4.0f);
  glm::vec4 vector2(4.0f, 3.0f, 2.0f, 1.0f);
  glm::vec4 result1 = matrix1 * vector1;
  glm::vec4 result2 = matrix2 * vector2;

  ft_glm::mat4 ft_resultNOPE = ft_matrix1 * ft_matrix2;
  glm::mat4 resultNOPE = matrix1 * matrix2;

  if (!compareMatrices(ft_matrix1, matrix1)) {
    ft_matrix1.show("ft_matrix1");
    mat4show(matrix1, "matrix1");
    isFailed = true;
  }

  if (!compareMatrices(ft_resultNOPE, resultNOPE)) {
    ft_resultNOPE.show("ft_resultNOPE");
    mat4show(resultNOPE, "resultNOPE");
    isFailed = true;
  }

  if (!compareMatrices(ft_matrix1, matrix1) || !compareMatrices(ft_matrix2, matrix2)) {
    mat4show(matrix1, "matrix1");
    ft_matrix1.show("ft_matrix1");
    std::cout << std::endl;

    mat4show(matrix2, "matrix2");
    ft_matrix2.show("ft_matrix2");
    std::cout << std::endl;

    std::cout << std::endl;
    isFailed = true;
  }

  if (!compareVec4(ft_result1, result1) || !compareVec4(ft_result2, result2)) {
    std::cout << std::endl;
    vec4show(result1, "result1");
    std::cout << "ft_result1 : " << ft_result1 << std::endl;\
    std::cout << std::endl;
    vec4show(result2, "result2");
    std::cout << "ft_result2 : " << ft_result2 << std::endl;
    std::cout << std::endl;
    isFailed = true;
  }

  return !isFailed;
}


bool test_ft_glm_02() {
  bool isFailed = false;
  ft_glm::vec3 ft_position(0.0f, 0.0f, 0.0f);
  ft_glm::vec3 ft_target(0.0f, 0.0f, -1.0f);
  ft_glm::vec3 ft_up(0.0f, 1.0f, 0.0f);
  ft_glm::mat4 ft_resultLookAt = ft_glm::lookAt(ft_position, ft_target, ft_up);

  glm::vec3 position(0.0f, 0.0f, 0.0f);
  glm::vec3 target(0.0f, 0.0f, -1.0f);
  glm::vec3 up(0.0f, 1.0f, 0.0f);
  glm::mat4 resultLookAt = glm::lookAt(position, target, up);

  if (!compareMatrices(ft_resultLookAt, resultLookAt)) {
    mat4show(resultLookAt, "resultLookAt");
    ft_resultLookAt.show("ft_resultLookAt");
    isFailed = true;
  }

  return !isFailed;
}

bool test_ft_glm_03() {
  bool isFailed = false;

  float fovDegrees = 45.0f;
  float ratio = 4.0f / 3.0f;
  float near = 0.1f;
  float far = 100.0f;

  float ft_fovRadians = ft_glm::radians(fovDegrees);
  float fovRadians = glm::radians(fovDegrees);

  if (ft_fovRadians != fovRadians) {
    std::cout << "ft_fovRadians = " << ft_fovRadians << std::endl;
    std::cout << "fovRadians = " << fovRadians << std::endl;
    isFailed = true;
  }

  glm::mat4 projMatrix = glm::perspective(fovRadians, ratio, near, far);
  ft_glm::mat4 ft_projMatrix = ft_glm::perspective(ft_fovRadians, ratio, near, far);


  if (!compareMatrices(ft_projMatrix, projMatrix)) {
    mat4show(projMatrix, "projMatrix");
    ft_projMatrix.show("ft_projMatrix");
    isFailed = true;
  }
  
  ft_glm::mat4 ft_identityMatrix = ft_glm::mat4(1.0f);;
  glm::mat4 identityMatrix = glm::mat4(1.0f);;

  if (!compareMatrices(ft_identityMatrix, identityMatrix)) {
    mat4show(identityMatrix, "identityMatrix");
    ft_identityMatrix.show("ft_identityMatrix");
    isFailed = true;
  }

  ft_glm::mat4 ft_emptyMatrix = ft_glm::mat4(0.0f);
  glm::mat4 emptyMatrix = glm::mat4(0.0f);

  if (!compareMatrices(ft_emptyMatrix, emptyMatrix)) {
    mat4show(emptyMatrix, "emptyMatrix");
    ft_emptyMatrix.show("ft_emptyMatrix");
    isFailed = true;
  }

  return !isFailed;
}

bool test_ft_glm_04() {
  bool isFailed = false;

  ft_glm::vec3 ft_center = ft_glm::vec3(3.0f, 5.5f, 0.7f);
  glm::vec3 center = glm::vec3(3.0f, 5.5f, 0.7f);

  ft_glm::mat4 ft_translateTestMatrix = ft_glm::translate(ft_glm::mat4(1.0f), ft_glm::vec3(-ft_center.x, -ft_center.y, -ft_center.z));
  glm::mat4 translateTestMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-center.x, -center.y, -center.z));

  if (!compareMatrices(ft_translateTestMatrix, translateTestMatrix)) {
    mat4show(translateTestMatrix, "translateTestMatrix");
    ft_translateTestMatrix.show("ft_translateTestMatrix");
    isFailed = true;
  }

  return !isFailed;
}