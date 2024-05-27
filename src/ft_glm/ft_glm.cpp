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
  data[0][0] = f;
  data[1][1] = f;
  data[2][2] = f;
  if (f == 0.0f || f == 1.0f) {
    data[3][3] = f;
  }
}

ft_glm::mat4::mat4(float m00, float m01, float m02, float m03,
                   float m10, float m11, float m12, float m13,
                   float m20, float m21, float m22, float m23,
                   float m30, float m31, float m32, float m33) {
    data[0][0] = m00;
    data[0][1] = m01;
    data[0][2] = m02;
    data[0][3] = m03;
    data[1][0] = m10;
    data[1][1] = m11;
    data[1][2] = m12;
    data[1][3] = m13;
    data[2][0] = m20;
    data[2][1] = m21;
    data[2][2] = m22;
    data[2][3] = m23;
    data[3][0] = m30;
    data[3][1] = m31;
    data[3][2] = m32;
    data[3][3] = m33;
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
    throw std::out_of_range("Invalid index");
  }
  return data[index];
}

const float *ft_glm::mat4::operator[](int index) const {
  if (index < 0 || index >= 4) {
    throw std::out_of_range("Invalid index");
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

vec4 ft_glm::mat4::operator*(const vec4 &v) const {
  vec4 vertex = vec4();

  vertex.x = (data[0][0] * v.x) + (data[1][0] * v.y) + (data[2][0] * v.z) + (data[3][0] * v.w);
  vertex.y = (data[0][1] * v.x) + (data[1][1] * v.y) + (data[2][1] * v.z) + (data[3][1] * v.w);
  vertex.z = (data[0][2] * v.x) + (data[1][2] * v.y) + (data[2][2] * v.z) + (data[3][2] * v.w);
  vertex.w = (data[0][3] * v.x) + (data[1][3] * v.y) + (data[2][3] * v.z) + (data[3][3] * v.w);

  return vertex;
}

mat4 ft_glm::mat4::operator*(const mat4 &m) const {
  mat4 mProduct;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      float sum = 0.0f;
      for (int k = 0; k < 4; k++) {
        sum += data[k][j] * m[i][k];
      }
      mProduct[i][j] = sum;
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

  translationMatrice[3][0] += v.x;
  translationMatrice[3][1] += v.y;
  translationMatrice[3][2] += v.z;

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

  projectionMatrix[0][0] = 1.0f / (ratio * tanHalfFov);
  projectionMatrix[1][1] = 1.0f / (tanHalfFov);
  projectionMatrix[2][2] = - (far + near) / (far - near);
  projectionMatrix[2][3] = - 1.0f;
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

ft_glm::mat4 ft_glm::rotate(mat4 const &m, float const &angle, vec3 const &v) {
  float const a = angle;
  float const c = cos(a);
  float const s = sin(a);


  vec3 axis(normalize(v));
  vec3 temp((1.0f - c) * axis);

  mat4 rotate;
  rotate[0][0] = c + temp[0] * axis[0];
  rotate[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
  rotate[0][2] = 0 + temp[0] * axis[2] - s * axis[1];

  rotate[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
  rotate[1][1] = c + temp[1] * axis[1];
  rotate[1][2] = 0 + temp[1] * axis[2] + s * axis[0];

  rotate[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
  rotate[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
  rotate[2][2] = c + temp[2] * axis[2];

  mat4 rotationMatrix;

  (void)m;
  // rotationMatrix[0] = m[0] * rotate[0][0];

  // for (int i = 0; i < 4; i++) {
  //   float* row = rotationMatrix[i];
  //   row[0] = m[i][0] * rotate[i][0] + m[i][1] * rotate[i][1] + m[i][2] * rotate[i][2];
  //   rotationMatrix[0][i] = row[0];
  // }

  // rotationMatrix[0] = m[0] * rotate[0][0] + m[1] * rotate[0][1] + m[2] * rotate[0][2];
  // rotationMatrix[1] = m[0] * rotate[1][0] + m[1] * rotate[1][1] + m[2] * rotate[1][2];
  // rotationMatrix[2] = m[0] * rotate[2][0] + m[1] * rotate[2][1] + m[2] * rotate[2][2];
  // rotationMatrix[3] = m[3];
  return rotationMatrix;
}