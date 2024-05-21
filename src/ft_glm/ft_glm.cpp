#include "ft_glm.h"

using namespace ft_glm;

// Generics

float ft_glm::radians(float degree) {
  return ( degree * M_PI ) / 180.0f;
}

float ft_glm::focalLength(float fovRadians) {
  return 1.0f / tanf(fovRadians * 0.5f);
}


// ------------ Vextex 3 dimensions

vec3 &ft_glm::vec3::operator+=(const vec3 &v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

vec3 &ft_glm::vec3::operator-=(const vec3 &v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}


vec3 ft_glm::operator+(const vec3 &v1, const vec3 &v2) {
  return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

vec3 ft_glm::operator-(const vec3 &v1, const vec3 &v2) {
  return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

vec3 ft_glm::operator*(float s, const vec3 &v) {
  return vec3(s * v.x, s * v.y, s * v.z);
}

vec3 ft_glm::operator*(const vec3& v, float s) {
    return vec3(s * v.x, s * v.y, s * v.z);
}

vec3 ft_glm::operator*(const vec3& v1, const vec3& v2) {
  return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

vec3 ft_glm::cross(const vec3 &v1, const vec3 &v2) {
  vec3 crossProduct;

  crossProduct.x = (v1.y * v2.z) - (v1.z * v2.y);
  crossProduct.y = (v1.z * v2.x) - (v1.x * v2.z);
  crossProduct.y = (v1.x * v2.y) - (v1.y * v2.x);

  return crossProduct;
}

// aka dot product
float ft_glm::scalar(const vec3 &v1, const vec3 &v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

vec3 ft_glm::normalize(const vec3 &v) {
    float invLength = 1 / sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
    return vec3(v.x * invLength, v.y * invLength, v.z * invLength);
}


// ------------ Vextex 4 dimensions
vec4 ft_glm::operator*(const vec4 &v1, const vec4 &v2) {
  return vec4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

ft_glm::vec4::vec4(const vec4 &other) {
  x = other.x;
  y = other.y;
  z = other.z;
  w = other.w;
}

vec4 &ft_glm::vec4::operator=(const vec4 &other) {
  if (this != &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
  }
  return *this;
}



// ------------- Matrices

ft_glm::mat4::mat4(float f) {
  data[0][0] = f;
  data[1][1] = f;
  data[2][2] = f;
}

ft_glm::mat4::mat4(const mat4 &other) {
 for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
        data[i][j] = other.data[i][j];
    }
  }
}

float *ft_glm::mat4::operator[](int index) {
    if (index < 0 || index >= 4) {
        static float invalid_value = 0.0f;
        return &invalid_value;
    }
    return data[index];
}

const float *ft_glm::mat4::operator[](int index) const {
  if (index < 0 || index >= 4) {
    static float invalid_value = 0.0f;
      return &invalid_value;
  }
    return data[index];
}

mat4 &ft_glm::mat4::operator=(const mat4 &other) {
  if (this != &other) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = other.data[i][j];
        }
    }
  }
  return *this;
}

vec4 ft_glm::operator*(const mat4 &m, const vec4 &v) {
  vec4 vertex = vec4();

  vertex.x = (m.data[0][0] * v.x) + (m.data[0][1] * v.y) + (m.data[0][2] * v.z) + (m.data[0][3] * v.w);
  vertex.y = (m.data[1][0] * v.x) + (m.data[1][1] * v.y) + (m.data[1][2] * v.z) + (m.data[1][3] * v.w);
  vertex.z = (m.data[2][0] * v.x) + (m.data[2][1] * v.y) + (m.data[2][2] * v.z) + (m.data[2][3] * v.w);
  vertex.w = (m.data[3][0] * v.x) + (m.data[3][1] * v.y) + (m.data[3][2] * v.z) + (m.data[3][3] * v.w);

  return vertex;
}

mat4 ft_glm::operator*(const mat4 &m1, const mat4 &m2) {
  mat4 mProduct;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mProduct.data[i][j] = 0;
      for (int k = 0; k < 4; k++) {
        mProduct.data[i][j] += m1.data[i][k] * m2.data[k][j];
      }
    }
  }

  return mProduct;
}

void ft_glm::mat4::show(const std::string &name) {
  std::cout << "[------ "<< name<< " ------]" << std::endl;
  for (int i = 0; i < 4; i++) {
    std::cout << "  ";
    for (int j = 0; j < 4; j++) {
      std::cout << std::fixed << std::setprecision(2) << (data[i][j] >= 0 ? " " : "") << data[i][j] << " ";
    }
    std::cout << std::endl;
  }
  
}


mat4 ft_glm::translate(const mat4 &m, const vec3 &v) {
  mat4 translationMatrice = m;

  translationMatrice.data[0][3] += v.x;
  translationMatrice.data[1][3] += v.y;
  translationMatrice.data[2][3] += v.z;

  return translationMatrice;
}

 mat4 ft_glm::perspective(float fovRadians, float ratio, float near, float far) {
  if (far == near || ratio == 0.0f) {
    std::cout << "Error inputs perspective" << std::endl;
    return mat4();
  }

  float tanHalfFov = tanf( fovRadians / 2.0f );

  mat4 projectionMatrix = mat4();

  projectionMatrix[0][0] = 1.0f / (ratio * tanHalfFov);
  projectionMatrix[1][1] = 1.0f / (tanHalfFov);
  projectionMatrix[2][2] = - (far + near) / (far - near);
  projectionMatrix[2][3] = 1.0f;
  projectionMatrix[3][2] = - (2.0f * far * near) / (far - near);

  return projectionMatrix;
}

mat4 ft_glm::lookAt(const vec3 &position, const vec3 &target, const vec3 &up) {
  const vec3 forward = vec3(normalize(target - position));
  const vec3 right(normalize(cross(forward, up)));
  const vec3 newUp(cross(right, forward));

  mat4 matrix(1);
  matrix[0][0] = right.x;
  matrix[1][0] = right.y;
  matrix[2][0] = right.z;
  matrix[0][1] = newUp.x;
  matrix[1][1] = newUp.y;
  matrix[2][1] = newUp.z;
  matrix[0][2] = -forward.x;
  matrix[1][2] = -forward.y;
  matrix[2][2] = -forward.z;
  matrix[3][0] = -scalar(right, position);
  matrix[3][1] = -scalar(newUp, position);
  matrix[3][2] = scalar(forward, position);

  return matrix;
}