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

vec3 ft_glm::vec3::operator-() const {
  return vec3(-x, -y, -z);
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

float &ft_glm::vec3::operator[](int index) {
  switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range("Invalid index");
  }
}

const float &ft_glm::vec3::operator[](int index) const {
  switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range("Invalid index");
  }
}

vec3 ft_glm::cross(const vec3 &v1, const vec3 &v2) {
  vec3 crossProduct;

  crossProduct.x = (v1.y * v2.z) - (v1.z * v2.y);
  crossProduct.y = (v1.z * v2.x) - (v1.x * v2.z);
  crossProduct.z = (v1.x * v2.y) - (v1.y * v2.x);

  return crossProduct;
}

vec3 ft_glm::midPoint(const vec3 &v1, const vec3 &v2) {
  return vec3((v1.x + v2.x) * 0.5f, (v1.y + v2.y) * 0.5f, (v1.z + v2.z) * 0.5f);
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

bool ft_glm::operator==(const ft_glm::vec4 &lhs, const ft_glm::vec4 &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

// ----------------- Display

std::ostream& operator<<(std::ostream& os, const ft_glm::vec4& vec) {
  os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
  return os;
}

std::ostream &operator<<(std::ostream& os, const ft_glm::vec3 &vec) {
  os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return os;
}


// ------------- Matrices

ft_glm::mat4::mat4(float f) {
  data[0] = f;
  data[5] = f;
  data[10] = f;
  if (f == 0.0f || f == 1.0f) {
    data[15] = f;
  }
}

ft_glm::mat4::mat4(float m00, float m01, float m02, float m03,
                   float m10, float m11, float m12, float m13,
                   float m20, float m21, float m22, float m23,
                   float m30, float m31, float m32, float m33) {
    data[0] = m00;
    data[1] = m01;
    data[2] = m02;
    data[3] = m03;
    data[4] = m10;
    data[5] = m11;
    data[6] = m12;
    data[7] = m13;
    data[8] = m20;
    data[9] = m21;
    data[10] = m22;
    data[11] = m23;
    data[12] = m30;
    data[13] = m31;
    data[14] = m32;
    data[15] = m33;
}

ft_glm::mat4::mat4(const mat4 &other) {
 for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
        data[i * 4 + j] = other.data[i * 4 + j];
    }
  }
}

float &ft_glm::mat4::operator[](int index) {
  if (index < 0 || index >= 16) {
    throw std::out_of_range("Invalid index");
  }
  return data[index];
}

const float &ft_glm::mat4::operator[](int index) const {
  if (index < 0 || index >= 16) {
    throw std::out_of_range("Invalid index");
  }
  return data[index];
}

mat4 &ft_glm::mat4::operator=(const mat4 &other) {
  if (this != &other) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i * 4 + j] = other.data[i * 4 + j];
        }
    }
  }
  return *this;
}

vec4 ft_glm::mat4::operator*(const vec4 &v) const {
  vec4 vertex = vec4();

  vertex.x = (data[0] * v.x) + (data[4] * v.y) + (data[8] * v.z) + (data[12] * v.w);
  vertex.y = (data[1] * v.x) + (data[5] * v.y) + (data[9] * v.z) + (data[13] * v.w);
  vertex.z = (data[2] * v.x) + (data[6] * v.y) + (data[10] * v.z) + (data[14] * v.w);
  vertex.w = (data[3] * v.x) + (data[7] * v.y) + (data[11] * v.z) + (data[15] * v.w);

  return vertex;
}

mat4 ft_glm::mat4::operator*(const mat4 &m) const {
  mat4 mProduct;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      float sum = 0.0f;
      for (int k = 0; k < 4; k++) {
        sum += data[k * 4 + j] * m[i * 4 + k];
      }
      mProduct[i * 4 + j] = sum;
    }
  }
  return mProduct;
}

void ft_glm::mat4::show(const std::string &name) {
  std::cout << "[------ "<< name<< " ------]" << std::endl;
  for (int i = 0; i < 4; i++) {
    std::cout << "  ";
    for (int j = 0; j < 4; j++) {
      std::cout << std::fixed << std::setprecision(2) << (data[i * 4 + j] >= 0 ? " " : "") << data[i * 4 + j] << " ";
    }
    std::cout << std::endl;
  }
  
}


mat4 ft_glm::translate(const mat4 &m, const vec3 &v) {
  mat4 translationMatrice = m;

  translationMatrice[12] += v.x;
  translationMatrice[13] += v.y;
  translationMatrice[14] += v.z;

  return translationMatrice;
}


// Usefull sources :
// https://github.com/g-truc/glm/blob/0.9.5/glm/gtc/matrix_transform.inl#L208
// https://www.songho.ca/opengl/gl_lookattoaxes.html
 mat4 ft_glm::perspective(float fovRadians, float ratio, float near, float far) {
  if (far == near || ratio == 0.0f) {
    std::cout << "Error inputs perspective" << std::endl;
    return mat4();
  }

  float tanHalfFov = tanf( fovRadians / 2.0f );

  mat4 projectionMatrix = mat4(0.0f);

  projectionMatrix[0] = 1.0f / (ratio * tanHalfFov);
  projectionMatrix[5] = 1.0f / (tanHalfFov);
  projectionMatrix[10] = - (far + near) / (far - near);
  projectionMatrix[11] = - 1.0f;
  projectionMatrix[14] = - (2.0f * far * near) / (far - near);

  return projectionMatrix;
}
mat4 ft_glm::lookAt(const vec3 &position, const vec3 &target, const vec3 &up) {
  const vec3 forward = vec3(normalize(target - position));
  const vec3 right(normalize(cross(forward, up)));
  const vec3 newUp(cross(right, forward));

  mat4 matrix(1);
  matrix[0] = right.x;
  matrix[4] = right.y;
  matrix[8] = right.z;
  matrix[1] = newUp.x;
  matrix[5] = newUp.y;
  matrix[9] = newUp.z;
  matrix[2] = -forward.x;
  matrix[6] = -forward.y;
  matrix[10] = -forward.z;
  matrix[12] = -scalar(right, position);
  matrix[13] = -scalar(newUp, position);
  matrix[14] = scalar(forward, position);

  return matrix;
}

ft_glm::mat4 ft_glm::rotate(mat4 const &m, float const &angle, vec3 const &v) {
  float const a = angle;
  float const c = cos(a);
  float const s = sin(a);


  vec3 axis(normalize(v));
  vec3 temp((1.0f - c) * axis);

  mat4 rotate;
  rotate[0] = c + temp[0] * axis[0];
  rotate[1] = 0 + temp[0] * axis[1] + s * axis[2];
  rotate[2] = 0 + temp[0] * axis[2] - s * axis[1];

  rotate[4] = 0 + temp[1] * axis[0] - s * axis[2];
  rotate[5] = c + temp[1] * axis[1];
  rotate[6] = 0 + temp[1] * axis[2] + s * axis[0];

  rotate[8] = 0 + temp[2] * axis[0] + s * axis[1];
  rotate[9] = 0 + temp[2] * axis[1] - s * axis[0];
  rotate[10] = c + temp[2] * axis[2];

  mat4 rotationMatrix;

  for (int i = 0; i < 4; i++) {
    rotationMatrix[i * 4 + 0] = m[i * 4 + 0] * rotate[0] + m[i * 4 + 1] * rotate[1] + m[i * 4 + 2] * rotate[2];
    rotationMatrix[i * 4 + 1] = m[i * 4 + 0] * rotate[4] + m[i * 4 + 1] * rotate[5] + m[i * 4 + 2] * rotate[6];
    rotationMatrix[i * 4 + 2] = m[i * 4 + 0] * rotate[8] + m[i * 4 + 1] * rotate[9] + m[i * 4 + 2] * rotate[10];
    rotationMatrix[i * 4 + 3] = m[i * 4 + 3];
  }

  // rotationMatrix[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
  // rotationMatrix[1] = m[0] * rotate[1][0] + m[1] * rotate[1][1] + m[2] * rotate[1][2];
  // rotationMatrix[2] = m[0] * rotate[2][0] + m[1] * rotate[2][1] + m[2] * rotate[2][2];
  // rotationMatrix[3] = m[3];
  return rotationMatrix;
}