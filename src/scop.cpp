
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




// [!] TEST ONLY // [!] TEST ONLY // [!] TEST ONLY // [!] TEST ONLY // [!] TEST ONLY // [!] TEST ONLY
// int testMatrices() {
//     // Définition des matrices et des vecteurs
//     ft_glm::mat4 matrix1(
//         1.0f, 2.0f, 3.0f, 4.0f,
//         5.0f, 6.0f, 7.0f, 8.0f,
//         9.0f, 10.0f, 11.0f, 12.0f,
//         13.0f, 14.0f, 15.0f, 16.0f
//     );

//     ft_glm::mat4 matrix2(
//         16.0f, 15.0f, 14.0f, 13.0f,
//         12.0f, 11.0f, 10.0f, 9.0f,
//         8.0f, 7.0f, 6.0f, 5.0f,
//         4.0f, 3.0f, 2.0f, 1.0f
//     );

//     ft_glm::vec4 vector1(1.0f, 2.0f, 3.0f, 4.0f);
//     ft_glm::vec4 vector2(4.0f, 3.0f, 2.0f, 1.0f);

//     // Calcul des résultats attendus
//     ft_glm::vec4 expected_result1(
//         30.0f, 70.0f, 110.0f, 150.0f
//     );

//     ft_glm::vec4 expected_result2(
//         150.0f, 110.0f, 70.0f, 30.0f
//     );

//     // Multiplication des matrices et des vecteurs
//     ft_glm::vec4 result1 = matrix1 * vector1;
//     ft_glm::vec4 result2 = matrix2 * vector2;

//     // Comparaison des résultats avec les résultats attendus
//     if (result1 == expected_result1 && result2 == expected_result2) {
//         std::cout << "Le test a réussi !" << std::endl;
//     } else {
//         std::cout << "Le test a échoué !" << std::endl;
//         std::cout << "Résultat 1 attendu : " << expected_result1 << std::endl;
//         std::cout << "Résultat 1 obtenu : " << result1 << std::endl;
//         std::cout << "Résultat 2 attendu : " << expected_result2 << std::endl;
//         std::cout << "Résultat 2 obtenu : " << result2 << std::endl;
//         return -1;
//     }

//     // *******************


//   ft_glm::vec3 position(0.0f, 0.0f, 0.0f);
//   ft_glm::vec3 target(0.0f, 0.0f, -1.0f);
//   ft_glm::vec3 up(0.0f, 1.0f, 0.0f);


//   ft_glm::mat4 resultLookAt = ft_glm::lookAt(position, target, up);
//   resultLookAt.show("resultLookAt"); // [!] DEBUG



//     return 0;
// }


void launchTests() {
  bool test01 = test_ft_glm_01();
  if (!test01) {
    std::cout << "Test matrices 01 failed" << std::endl;
    exit(-1);
  }

  bool test02 = test_ft_glm_02();
  if (!test02) {
    std::cout << "Test matrices 02 failed" << std::endl;
    exit(-1);
  }


};


int main()
{
  Window window = Window(WIN_WIDTH, WIN_HEIGHT, "Tutorial 08");
  Camera camera = Camera(window.getWindow());

  // Load Obj file
  ObjLoader objLoader = ObjLoader();
  std::vector<ft_glm::vec3> vertices;
  std::vector<ft_glm::vec2> uvs;
  std::vector<ft_glm::vec3> normals; // will not be used yet

  const std::string objFilePath = "../res/obj/cube.obj";
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

  ft_glm::vec3 center = ft_glm::vec3((maxs.x + mins.x) * 0.5f, (maxs.y + mins.y) * 0.5f, (maxs.z + mins.z) * 0.5f);
   std::cout << "Center : " << center.x << ", " << center.y << ", " << center.z << std::endl;

   ft_glm::mat4 translateTestMatrix = ft_glm::translate(ft_glm::mat4(1.0f), ft_glm::vec3(-center.x, -center.y, -center.z));




  ft_glm::mat4 projectionMatrix = camera.getProjectionMatrix();
  projectionMatrix.show("projectionMatrix"); // [!] DEBUG

  ft_glm::mat4 viewMatrix = camera.getViewMatrix();
  viewMatrix.show("viewMatrix"); // [!] DEBUG

  ft_glm::mat4 modelMatrix  =  translateTestMatrix * ft_glm::mat4(1.0f);
  modelMatrix.show("modelMatrix"); // [!] DEBUG
  
  ft_glm::mat4 mvp = projectionMatrix  * viewMatrix * modelMatrix;
  mvp.show("mvp"); // [!] DEBUG

  launchTests();




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