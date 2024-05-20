
#include <vector>
#include <string>
#include <iostream>

#include "glad.h"
#include <GLFW/glfw3.h>

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
  Window window = Window(WIN_WIDTH, WIN_HEIGHT, "Tutorial 08");
  Camera camera = Camera(window.getWindow());


    // Load Obj file
  ObjLoader objLoader = ObjLoader();
  std::vector<ft_glm::vec3> vertices;
  std::vector<ft_glm::vec2> uvs;
  std::vector<ft_glm::vec3> normals; // will not be used yet

  const std::string objFilePath = "../res/obj/teapot.obj";
  // const std::string textureFilePath = "../res/textures/unikitty.bmp";
  const std::string textureFilePath = "../res/textures/poney.bmp";

  ft_glm::vec3 maxs;
  ft_glm::vec3 mins;

  // MY
  try {

    objLoader.loadOBJ(objFilePath, vertices, uvs, normals, maxs, mins);

  } catch(std::exception &e) {
    std::cout << "Failed to load object file : " + objFilePath;
    std::cout << ": " << e.what() << std::endl;
    exit(-1);
  }


    std::cout << "maxs : " << maxs.x << ", " << maxs.y << ", " << maxs.z << std::endl;
    std::cout << "mins : " << mins.x << ", " << mins.y << ", " << mins.z << std::endl;

  // ---------------------
  // Projection matrix: 45° Field of View, 4:3 ratio, display range: 0.1 unit <-> 100 units

  ft_glm::vec3 center = ft_glm::vec3((maxs.x + mins.x) / 2, (maxs.y + mins.y) / 2, (maxs.z + mins.z) / 2);
   std::cout << "Center : " << center.x << ", " << center.y << ", " << center.z << std::endl;
  // glm::mat4 transToCenterMatrix = glm::translate(glm::mat4(), glm::vec3(-center.x, -center.y, -center.z));
  // glm::mat4 myScalingMatrix = glm::scale(glm::mat4(1), glm::vec3(2,2,2));

   ft_glm::mat4 translateTestMatrix = ft_glm::translate(ft_glm::mat4(1.0f), ft_glm::vec3(-center.x, -center.y, -center.z));




  ft_glm::mat4 projectionMatrix = camera.getProjectionMatrix();
  ft_glm::mat4 viewMatrix = camera.getViewMatrix();
  ft_glm::mat4 modelMatrix  = translateTestMatrix * ft_glm::mat4(1.0f);
  ft_glm::mat4 mvp = projectionMatrix  * viewMatrix * modelMatrix;


  // GLFW : input handler
  glfwSetInputMode(window.getWindow(), GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key being pressed below
  // glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Hide the mouse and enable unlimited movement
  glfwPollEvents();
  // glfwSetCursorPos(window.getWindow(), WIN_WIDTH / 2, WIN_HEIGHT / 2); // Set the mouse at the center of the screen

  // Load the texture using any two methods
  // GLuint myTexture = loadBMP_custom("../res/textures/unikitty.bmp");
  BMPLoader bmpLoader = BMPLoader(textureFilePath);
  if (bmpLoader.getTextureID() == 0) {
    std::cout << "Failed to load texture bmp file : " + textureFilePath << std::endl;
    exit(-1);
  }


  if (uvs.size() == 0) {
    for (auto vertex : vertices) {
      // Planar projection - texture
      ft_glm::vec4 vertexPos = ft_glm::vec4(vertex.x, vertex.y, vertex.z, 1.0f);
      ft_glm::vec4 clipPos = projectionMatrix * viewMatrix * vertexPos;
      ft_glm::vec3 texCoords = ft_glm::vec3(clipPos.x / clipPos.w, clipPos.y / clipPos.w, 0.0f);
      uvs.push_back(ft_glm::vec2(texCoords.x, texCoords.y));
    }
  }



  VertexArray vertexArray = VertexArray();
  vertexArray.bind();


  Shader shader = Shader("../res/shaders/basic_shader.glsl");
  shader.bind();

  VertexBuffer vertexBuffer = VertexBuffer(&vertices[0], vertices.size() * sizeof(ft_glm::vec3));
  vertexBuffer.bind();

  VertexBuffer uvBuffer = VertexBuffer(&uvs[0], uvs.size() * sizeof(ft_glm::vec2));
  uvBuffer.bind();

  std::vector<ft_glm::vec3> colors;

  std::vector<ft_glm::vec3> colorPalette = {
    // glm::vec3(0.997f,  0.513f,  0.064f),
    // glm::vec3(0.945f,  0.719f,  0.592f),
    // glm::vec3(0.543f,  0.021f,  0.978f),
    // glm::vec3(0.279f,  0.317f,  0.505f),
    // glm::vec3(0.167f,  0.620f,  0.077f),
    // glm::vec3(0.347f,  0.857f,  0.137f),
    
    // glm::vec3(0.406f,  0.615f,  0.116f),
    // glm::vec3(0.971f,  0.572f,  0.833f),
    // glm::vec3(0.279f,  0.317f,  0.505f),
    // glm::vec3(0.302f,  0.455f,  0.848f),
    // glm::vec3(0.517f,  0.713f,  0.338f),
    // glm::vec3(0.820f,  0.883f,  0.371f),

    ft_glm::vec3(0.1f,  0.1f,  0.1f),
    ft_glm::vec3(0.1f,  0.1f,  0.1f),
    ft_glm::vec3(0.1f,  0.1f,  0.1f),

    ft_glm::vec3(0.2f,  0.2f,  0.2f),
    ft_glm::vec3(0.2f,  0.2f,  0.2f),
    ft_glm::vec3(0.2f,  0.2f,  0.2f),

    ft_glm::vec3(0.3f,  0.3f,  0.3f),
    ft_glm::vec3(0.3f,  0.3f,  0.3f),
    ft_glm::vec3(0.3f,  0.3f,  0.3f),

    ft_glm::vec3(0.4f,  0.4f,  0.4f),
    ft_glm::vec3(0.4f,  0.4f,  0.4f),
    ft_glm::vec3(0.4f,  0.4f,  0.4f),
  };


  unsigned int index = 0;
  for (unsigned int i = 0 ; i < vertices.size(); i++) {
    colors.push_back(colorPalette[index]);
    index++;
    if (index >= colorPalette.size())
      index = 0;
  }

  VertexBuffer colorBuffer = VertexBuffer(&colors[0], colors.size() * sizeof(ft_glm::vec3));
  colorBuffer.bind();


  // Get a handle for our "MVP" uniform
  // Only during the initialisation
  shader.setUniformMat4f("u_mvp", mvp);


  // Get a handle for our "myTextureSampler" uniform
  shader.setUniform1i("u_myTexture", 0);

  shader.setUniform1i("u_viewMode", COLOR);


  // UNbinding all to let bind process in loop
  shader.unbind();
  vertexArray.unbind();
  vertexBuffer.unbind();
  uvBuffer.unbind();

  bool isUV = (vertices.size() == uvs.size());
  window.setInputMode();

  LOGCHECK(glClearColor(0.35f, 0.65f, 0.85f, 1.0f)); // background color
  // LOGCHECK(glClearColor(0.0f, 0.0f, 0.4f, 0.0f)); // Dark blue background

  // Enable depth test
  LOGCHECK(glEnable(GL_DEPTH_TEST));
  LOGCHECK(glDepthFunc(GL_LESS)); // Accept fragment if it is closer to the camera than the former one
  // LOGCHECK(glEnable(GL_CULL_FACE)); // switch this on/off to display or not inside model

  do{
    LOGCHECK(glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ));


    shader.bind();
    // vertexArray.bind(); // bind are call in vertexArray.addBufferVertexOnly
    // vertexBuffer.bind();
    // colorBuffer.bind();

    // inputs handling
    // camera.computeMatricesFromInputs();
    camera.autoCamera();
    mvp = camera.getProjectionMatrix() * camera.getViewMatrix() * modelMatrix;
    shader.setUniformMat4f("u_mvp", mvp);
    shader.setUniform1i("u_viewMode", camera.getViewMode());

    // Bind our texture in Texture Unit 0
    if (isUV) {
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, bmpLoader.getTextureID());
      // shader.setUniform1i("u_myTexture", 0); // need ??
    }

    
    vertexArray.addBufferVertexOnly(vertexBuffer, 0, 3); // need call in loop

    if (isUV)
      vertexArray.addBufferVertexOnly(uvBuffer, 1, 2);

    vertexArray.addBufferVertexOnly(colorBuffer, 2, 3);



    // Draw the triangles to build the cube
    LOGCHECK(glDrawArrays(GL_TRIANGLES, 0, vertices.size())); // Starting from vertex 0; 12*3 vertices total -> 12 triangles


    LOGCHECK(glDisableVertexAttribArray(0));
    if (isUV)
      LOGCHECK(glDisableVertexAttribArray(1));

    // Swap buffers
    window.swapBuffers();
    window.pollEvents();

  } while( !window.shouldClose() 
      && window.getKey(GLFW_KEY_ESCAPE) != GLFW_PRESS 
  );

  // To test without openGl stuff
  std::vector<std::string> msg {"End", "of", "scop", "final project ", "POUIKA !"};

  for (const std::string &word : msg)
  {
    std::cout << word << " ";
  }
  std::cout << std::endl;



}