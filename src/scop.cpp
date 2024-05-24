
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
  Window window = Window(WIN_WIDTH, WIN_HEIGHT, "Scop");
  Camera camera = Camera(window.getWindow());

  DEBUG(launchTests());

  ObjLoader objLoader = ObjLoader();
  std::vector<ft_glm::vec3> vertices;
  std::vector<ft_glm::vec2> uvs;
  std::vector<ft_glm::vec3> normals;
  ft_glm::vec3 maxs;
  ft_glm::vec3 mins;


  // [1] Load Obj file + bmp file from ac/av
  Path::Data const pathData = Path::parseInputsArgs(ac, av);

  try {
    objLoader.loadOBJ(pathData.objFilePath, vertices, uvs, normals, maxs, mins);
  } catch(std::exception &e) {
    std::cout << "Failed to load object file : " + pathData.objFilePath;
    std::cout << ": " << e.what() << std::endl;
    exit(-1);
  }

  BMPLoader bmpLoader = BMPLoader(pathData.textureFilePath);
  if (bmpLoader.getTextureID() == 0) {
    std::cout << "Failed to load texture bmp file : " + pathData.textureFilePath << std::endl;
    exit(-1);
  }

  // [2] Compute Matrices for MVP : Model View Projection
  ft_glm::vec3 center = ft_glm::midPoint(maxs, mins);
  ft_glm::mat4 translateTestMatrix = ft_glm::translate(ft_glm::mat4(1.0f), ft_glm::vec3(-center.x, -center.y, -center.z));
  ft_glm::mat4 projectionMatrix = camera.getProjectionMatrix();
  ft_glm::mat4 viewMatrix = camera.getViewMatrix();
  ft_glm::mat4 modelMatrix  =  translateTestMatrix * ft_glm::mat4(1.0f);
  ft_glm::mat4 mvp = projectionMatrix  * viewMatrix * modelMatrix;

  DEBUG(translateTestMatrix.show("translate matrix"));
  DEBUG(projectionMatrix.show("projection matrix"));
  DEBUG(viewMatrix.show("view matrix"));
  DEBUG(modelMatrix.show("model matrix"));
  DEBUG(mvp.show("mvp matrix"));

  // [3] GLFW : input handler
  glfwSetInputMode(window.getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
  glfwPollEvents();


  // [4] OpenGL : Vertex Array, Vertex Buffer, Shader, Texture (using or creating UV coordinates)
  fillUpUVs(uvs, vertices, projectionMatrix, viewMatrix);

  VertexArray vertexArray = VertexArray();
  vertexArray.bind();

  Shader shader = Shader(SHADER_FILE);
  shader.bind();

  VertexBuffer vertexBuffer = VertexBuffer(&vertices[0], vertices.size() * sizeof(ft_glm::vec3));
  vertexBuffer.bind();

  VertexBuffer uvBuffer = VertexBuffer(&uvs[0], uvs.size() * sizeof(ft_glm::vec2));
  uvBuffer.bind();

  std::vector<ft_glm::vec3> colors;
  fillUpColors(colors, vertices.size());

  VertexBuffer colorBuffer = VertexBuffer(&colors[0], colors.size() * sizeof(ft_glm::vec3));
  colorBuffer.bind();

  // [5] Setting uniforms in glsl shader
  shader.setUniformMat4f("u_mvp", mvp);
  shader.setUniform1i("u_myTexture", 0);
  shader.setUniform1i("u_viewMode", COLOR);

  // [6] Prepare Main loop - bind are called with addBufferVertexOnly() calls
  shader.unbind();
  vertexArray.unbind();
  vertexBuffer.unbind();
  uvBuffer.unbind();
  colorBuffer.unbind();

  window.setInputMode();

  LOGCHECK(glClearColor(0.35f, 0.65f, 0.85f, 1.0f)); // background color
  // LOGCHECK(glClearColor(0.0f, 0.0f, 0.4f, 0.0f)); // Dark blue background

  // Enable depth test
  LOGCHECK(glEnable(GL_DEPTH_TEST));
  LOGCHECK(glDepthFunc(GL_LESS)); // Accept fragment if it is closer to the camera than the former one
  // LOGCHECK(glEnable(GL_CULL_FACE)); // switch this on/off to display or not inside model

  do {
    LOGCHECK(glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ));

    shader.bind();

    camera.autoCamera();
    mvp = camera.getProjectionMatrix() * camera.getViewMatrix() * modelMatrix;
    shader.setUniformMat4f("u_mvp", mvp);
    shader.setUniform1i("u_viewMode", camera.getViewMode());

    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bmpLoader.getTextureID());

    vertexArray.addBufferVertexOnly(vertexBuffer, 0, 3);
    vertexArray.addBufferVertexOnly(uvBuffer, 1, 2);
    vertexArray.addBufferVertexOnly(colorBuffer, 2, 3);

    // Draw the triangles to build the object
    LOGCHECK(glDrawArrays(GL_TRIANGLES, 0, vertices.size()));

    LOGCHECK(glDisableVertexAttribArray(0));
    LOGCHECK(glDisableVertexAttribArray(1));
    LOGCHECK(glDisableVertexAttribArray(2));

    // Swap buffers
    window.swapBuffers();
    window.pollEvents();

  } while( !window.shouldClose() 
      && window.getKey(GLFW_KEY_ESCAPE) != GLFW_PRESS 
  );

}