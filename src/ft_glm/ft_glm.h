#pragma once 

#include <iostream>
#include <iomanip>
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


 /* ------------------------- 4x4 Matrices -------------------- */
  struct mat4 {


    float data[4][4] = {
      {1.0f, 0.0f, 0.0f, 0.0f}, // column 1
      {0.0f, 1.0f, 0.0f, 0.0f}, // column 2
      {0.0f, 0.0f, 1.0f, 0.0f}, // column 3
      {0.0f, 0.0f, 0.0f, 1.0f}  // column 4
    };

    mat4() {};
    mat4(float f);

    mat4(const mat4& other);
    mat4 &operator=(const mat4 &other);

    float *operator[](int index);
    const float* operator[](int index) const;
    void show(const std::string &name);
  };

  vec4 operator*(const mat4 &m, const vec4 &v);
  mat4 operator*(const mat4 &m1, const mat4 &m2);
  mat4 translate(const mat4 &m, const vec3 &v);

  mat4 perspective(float fovRadians, float ratio, float near, float far);
  mat4 lookAt(const vec3 &position, const vec3 &target, const vec3 &up);

};