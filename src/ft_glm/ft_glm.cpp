#include "ft_glm.h"

using namespace ft_glm;

// ------------ Vextex 3 dimensions
vec3 ft_glm::operator*(float s, const vec3 &v) {
  return vec3(s * v.x, s * v.y, s * v.z);
}

vec3 ft_glm::operator*(const vec3& v, float s) {
    return vec3(s * v.x, s * v.y, s * v.z);
}

vec3 ft_glm::operator*(const vec3& v1, const vec3& v2) {
  return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
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


mat4 ft_glm::translate(const mat4 &m, const vec3 &v) {
  mat4 translationMatrice = m;

  translationMatrice.v4.x = v.x;
  translationMatrice.v4.y = v.y;
  translationMatrice.v4.z = v.z;

  return translationMatrice;
}