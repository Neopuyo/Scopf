#include <vector>
#include <string>
#include <iostream>

#include "glad.h"
#include <GLFW/glfw3.h>

#include <ft_glm.h>
#include <errorHandling.h>
#include <utils.h>

#include "Window.h"
#include "Camera.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ObjLoader.h"
#include "BMPLoader.h"


int main(int ac, char **av)
{
  (void)ac;
  (void)av;
  if (!glfwInit())
  {
    std::cout << "GLFW init failed" << std::endl;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
  if (!window)
  {
    std::cout << "Window or context creation failed" << std::endl;
  }
  glfwMakeContextCurrent(window);

  sleep(2);

  glfwDestroyWindow(window);
  glfwTerminate();


  /* ---------------------------------------------------------------------------------- */

  std::vector<std::string> msg {"As you can see, a basic usage of GLFW library causes errors and leaks | ", "end of ", "scop", " leaking tests", " !"};

  for (const std::string &word : msg)
  {
    std::cout << word << " ";
  }
  std::cout << std::endl;


}