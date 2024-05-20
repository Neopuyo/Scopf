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
  return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

vec3 ft_glm::operator-(const vec3 &v1, const vec3 &v2) {
  return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
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

  crossProduct.x = (v1.y * v2.z) - (v1.z - v2.y);
  crossProduct.y = (v1.z * v2.x) - (v1.x - v2.z);
  crossProduct.y = (v1.x * v2.y) - (v1.y - v2.x);

  return crossProduct;
}


float ft_glm::scalar(const vec3 &v1, const vec3 &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3 ft_glm::normalize(const vec3 &v) {
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return vec3(v.x / length, v.y / length, v.z / length);
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
  x = other.x;
  y = other.y;
  z = other.z;
  w = other.w;
  return *this;
}



// ------------- Matrices
ft_glm::mat4::mat4(const mat4 &other) {
  v1 = other.v1;
  v2 = other.v2;
  v3 = other.v3;
  v4 = other.v4;
}

mat4 &ft_glm::mat4::operator=(const mat4 &other) {
  v1 = other.v1;
  v2 = other.v2;
  v3 = other.v3;
  v4 = other.v4;
  return *this;
}

vec4 ft_glm::operator*(const mat4 &m, const vec4 &v) {
  vec4 vertex = vec4();

  vertex.x = (m.v1.x * v.x) + (m.v2.x * v.y) + (m.v3.x * v.z) + (m.v4.x * v.w);
  vertex.y = (m.v1.y * v.x) + (m.v2.y * v.y) + (m.v3.y * v.z) + (m.v4.y * v.w);
  vertex.y = (m.v1.z * v.x) + (m.v2.z * v.y) + (m.v3.z * v.z) + (m.v4.z * v.w);
  vertex.y = (m.v1.w * v.x) + (m.v2.w * v.y) + (m.v3.w * v.z) + (m.v4.w * v.w);

  return vertex;
}

mat4 ft_glm::operator*(const mat4 &m1, const mat4 &m2) {
   mat4 mProduct;

  mProduct.v1.x = m1.v1.x * m2.v1.x + m1.v2.x * m2.v1.y + m1.v3.x * m2.v1.z + m1.v4.x * m2.v1.w;
  mProduct.v1.y = m1.v1.y * m2.v1.x + m1.v2.y * m2.v1.y + m1.v3.y * m2.v1.z + m1.v4.y * m2.v1.w;
  mProduct.v1.z = m1.v1.z * m2.v1.x + m1.v2.z * m2.v1.y + m1.v3.z * m2.v1.z + m1.v4.z * m2.v1.w;
  mProduct.v1.w = m1.v1.w * m2.v1.x + m1.v2.w * m2.v1.y + m1.v3.w * m2.v1.z + m1.v4.w * m2.v1.w;

  mProduct.v2.x = m1.v1.x * m2.v2.x + m1.v2.x * m2.v2.y + m1.v3.x * m2.v2.z + m1.v4.x * m2.v2.w;
  mProduct.v2.y = m1.v1.y * m2.v2.x + m1.v2.y * m2.v2.y + m1.v3.y * m2.v2.z + m1.v4.y * m2.v2.w;
  mProduct.v2.z = m1.v1.z * m2.v2.x + m1.v2.z * m2.v2.y + m1.v3.z * m2.v2.z + m1.v4.z * m2.v2.w;
  mProduct.v2.w = m1.v1.w * m2.v2.x + m1.v2.w * m2.v2.y + m1.v3.w * m2.v2.z + m1.v4.w * m2.v2.w;

  mProduct.v3.x = m1.v1.x * m2.v3.x + m1.v2.x * m2.v3.y + m1.v3.x * m2.v3.z + m1.v4.x * m2.v3.w;
  mProduct.v3.y = m1.v1.y * m2.v3.x + m1.v2.y * m2.v3.y + m1.v3.y * m2.v3.z + m1.v4.y * m2.v3.w;
  mProduct.v3.z = m1.v1.z * m2.v3.x + m1.v2.z * m2.v3.y + m1.v3.z * m2.v3.z + m1.v4.z * m2.v3.w;
  mProduct.v3.w = m1.v1.w * m2.v3.x + m1.v2.w * m2.v3.y + m1.v3.w * m2.v3.z + m1.v4.w * m2.v3.w;

  mProduct.v4.x = m1.v1.x * m2.v4.x + m1.v2.x * m2.v4.y + m1.v3.x * m2.v4.z + m1.v4.x * m2.v4.w;
  mProduct.v4.y = m1.v1.y * m2.v4.x + m1.v2.y * m2.v4.y + m1.v3.y * m2.v4.z + m1.v4.y * m2.v4.w;
  mProduct.v4.z = m1.v1.z * m2.v4.x + m1.v2.z * m2.v4.y + m1.v3.z * m2.v4.z + m1.v4.z * m2.v4.w;
  mProduct.v4.w = m1.v1.w * m2.v4.x + m1.v2.w * m2.v4.y + m1.v3.w * m2.v4.z + m1.v4.w * m2.v4.w;

  return mProduct;
}


mat4 ft_glm::translate(const mat4 &m, const vec3 &v) {
  mat4 translationMatrice = m;

  translationMatrice.v4.x = v.x;
  translationMatrice.v4.y = v.y;
  translationMatrice.v4.z = v.z;

  return translationMatrice;
}

 mat4 ft_glm::perspective(float fovRadians, float ratio, float near, float far) {
  float focal = focalLength(fovRadians);

  mat4 projectionMatrix = mat4(
    vec4(focal / ratio, 0.0f, 0.0f, 0.0f),
    vec4(0.0f, focal, 0.0f, 0.0f),
    vec4(0.0f, 0.0f, (near+far)/(near-far), -1.0f),
    vec4(0.0f, 0.0f, (2*near*far)/(near-far), 0.0f)
  );

  return projectionMatrix;
}

mat4 ft_glm::lookAt(const vec3 &position, const vec3 &target, const vec3 &up) {
  vec3 forward = normalize(target - position);
  vec3 right = normalize(cross(forward, up));
  vec3 newUp = cross(right, forward);

  mat4 viewMatrix = mat4(
    vec4(right.x, right.y, right.z, -scalar(right, position)),
    vec4(newUp.x, newUp.y, newUp.z, -scalar(newUp, position)),
    vec4(-forward.x, -forward.y, -forward.z, scalar(forward, position)),
    vec4(0.0f, 0.0f, 0.0f, 1.0f)
  );

  return viewMatrix;
}