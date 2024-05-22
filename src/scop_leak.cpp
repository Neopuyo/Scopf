#include <vector>
#include <string>
#include <iostream>

#include "glad.h"
#include <GLFW/glfw3.h>


#include <tests_ft_glm.h> // [!]

#include <ft_glm.h>
#include <errorHandling.h>

#include "Window.h"
#include "Camera.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ObjLoader.h"
#include "BMPLoader.h"


int main()
{
   Window window = Window(WIN_WIDTH, WIN_HEIGHT, "Scop");
   Camera camera = Camera(window.getWindow());

   // Load Obj file
  ObjLoader objLoader = ObjLoader();
  std::vector<ft_glm::vec3> vertices;
  std::vector<ft_glm::vec2> uvs;
  std::vector<ft_glm::vec3> normals; // will not be used yet

  const std::string objFilePath = "../res/obj/42.obj";
  const std::string textureFilePath = "../res/textures/poney.bmp";

  ft_glm::vec3 maxs;
  ft_glm::vec3 mins;

  try {
    objLoader.loadOBJ(objFilePath, vertices, uvs, normals, maxs, mins);
  } catch(std::exception &e) {
    std::cout << "Failed to load object file : " + objFilePath;
    std::cout << ": " << e.what() << std::endl;
    exit(-1);
  }

  ft_glm::vec3 center = ft_glm::vec3((maxs.x + mins.x) * 0.5f, (maxs.y + mins.y) * 0.5f, (maxs.z + mins.z) * 0.5f);
  ft_glm::mat4 translateTestMatrix = ft_glm::translate(ft_glm::mat4(1.0f), ft_glm::vec3(-center.x, -center.y, -center.z));

  ft_glm::mat4 projectionMatrix = camera.getProjectionMatrix();
  ft_glm::mat4 viewMatrix = camera.getViewMatrix();
  ft_glm::mat4 modelMatrix  =  translateTestMatrix * ft_glm::mat4(1.0f);
  ft_glm::mat4 mvp = projectionMatrix  * viewMatrix * modelMatrix;
  (void)mvp;

  // [N] using glfw will generate unavoidable leaks that valgrind will report
  // You can see that removing the two next line will remove all error and leaks generated.
  glfwSetInputMode(window.getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
  glfwPollEvents();

  /* ---------------------------------------------------------------------------------- */

  // To test without openGl stuff
  std::vector<std::string> msg {"End", "of", "scop", "final project ", "POUIKA !"};

  for (const std::string &word : msg)
  {
    std::cout << word << " ";
  }
  std::cout << std::endl;


}