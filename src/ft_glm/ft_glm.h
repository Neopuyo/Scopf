#pragma once 

#include <cmath>

namespace ft_glm {

  // ---------- Generics
  float radians(float degree);
  float focalLength(float fovRadians);


  struct vec2 {
    float x;
    float y;

    vec2() : x(0.0f), y(0.0f) {}
    vec2(float x, float y) : x(x), y(y) {}
  };

  // ------------ Vextex 3 dimensions
  struct vec3 {
    float x;
    float y;
    float z;

    vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    vec3& operator+=(const vec3& v);
    vec3& operator-=(const vec3& v);
  };

  vec3 operator+(const vec3 &v1, const vec3 &v2);
  vec3 operator-(const vec3 &v1, const vec3 &v2);
  vec3 operator*(float s, const vec3 &v);
  vec3 operator*(const vec3 &v, float s);
  vec3 operator*(const vec3 &v1, const vec3 &v2);
  
  vec3 cross(const vec3 &v1, const vec3 &v2);
  float scalar(const vec3 &v1, const vec3 &v2);
  vec3 normalize(const vec3 &v);

  // ------------ Vextex 4 dimensions
  struct vec4 {
    float x;
    float y;
    float z;
    float w; // 0 -> direction // 1 -> position



    vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    vec4(float x, float y, float z) : x(x), y(y), z(z), w(1.0f) {}
    vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    vec4(const vec4 &other);
    vec4 &operator=(const vec4 &other);
  };

  vec4 operator*(const vec4 &v1, const vec4 &v2);


 /* ------------------------- 4x4 Matrices
  * v1.x   v2.x   v3.x   v4.x
  *
  * v1.y   v2.y   v3.y   v4.y
  *
  * v1.z   v2.z   v3.z   v4.z
  *
  * v1.w   v2.w   v3.w   v4.w
 */
  struct mat4 {
    vec4 v1;
    vec4 v2;
    vec4 v3;
    vec4 v4;

    mat4() : v1(vec4(1.0f, 0.0f, 0.0f, 0.0f)), v2(vec4(0.0f, 1.0f, 0.0f, 0.0f)), v3(vec4(0.0f, 0.0f, 1.0f, 0.0f)), v4(vec4(0.0f, 0.0f, 0.0f, 1.0f)) {}
    mat4(float f) : v1(vec4(f, 0.0f, 0.0f, 0.0f)), v2(vec4(0.0f, f, 0.0f, 0.0f)), v3(vec4(0.0f, 0.0f, f, 0.0f)), v4(vec4(0.0f, 0.0f, 0.0f, f)) {}
    mat4(vec4 v1, vec4 v2, vec4 v3, vec4 v4) : v1(v1), v2(v2), v3(v3), v4(v4) {}

    mat4(const mat4& other);
    mat4 &operator=(const mat4 &other);
  };

  vec4 operator*(const mat4 &m, const vec4 &v);
  mat4 operator*(const mat4 &m1, const mat4 &m2);
  mat4 translate(const mat4 &m, const vec3 &v);

  mat4 perspective(float fovRadians, float ratio, float near, float far);
  mat4 lookAt(const vec3 &position, const vec3 &target, const vec3 &up);

};