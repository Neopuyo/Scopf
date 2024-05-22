#pragma once

#include <string>
#include <iostream>

#include "glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp> // [!] only to compare with ft_glm => remove it after !
#include <glm/gtc/matrix_transform.hpp> // [!] only to compare with ft_glm => remove it after !

#include <ft_glm.h>
#include <errorHandling.h>

typedef bool (*UnitTest)();


bool test_ft_glm_01();
bool test_ft_glm_02();
bool test_ft_glm_03();
bool test_ft_glm_04();



void mat4show(const glm::mat4 m, const std::string &name);
void vec4show(const glm::vec4 v, const std::string &name);
bool compareMatrices(const ft_glm::mat4 &ft_m, const glm::mat4 &m);
bool compareVec4(const ft_glm::vec4 &ft_v, const glm::vec4 &v);