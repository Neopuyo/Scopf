#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "glad.h"
#include <GLFW/glfw3.h>
#include "errorHandling.h"

// Load a .BMP file using our custom loader
GLuint loadBMP_custom(const char * imagepath);

// Load a .DDS file using GLFW's own loader
GLuint loadDDS(const char * imagepath);