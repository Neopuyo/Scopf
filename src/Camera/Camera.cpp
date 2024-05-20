#include "Camera.h"

Camera::Camera(GLFWwindow *window) : m_window(window), m_mode(COLOR) {
  m_projectionMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(WIN_WIDTH / WIN_HEIGHT), 0.1f, 100.0f);
  m_viewMatrix = glm::lookAt(
      glm::vec3(4, 3, -3), // Camera is at (4,3,3), in World Space
      glm::vec3(0, 0, 0), // and looks at the origin
      glm::vec3(0, +1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
  );

}

Camera::~Camera() {}

void Camera::computeMatricesFromInputs() {
  static double lastTime = glfwGetTime(); // static to get initialized only once, at first call

  // Compute time difference between current and last frame
  double currentTime = glfwGetTime();
  float deltaTime = float(currentTime - lastTime);

  // Get mouse position
  double xpos, ypos;
  glfwGetCursorPos(m_window, &xpos, &ypos);

  // Reset mouse position for next frame
  glfwSetCursorPos(m_window, WIN_WIDTH / 2, WIN_HEIGHT / 2);

  // Compute new orientation
  m_horizontalAngle += m_mouseSpeed * float(WIN_WIDTH / 2 - xpos );
  m_verticalAngle   += m_mouseSpeed * float(WIN_HEIGHT / 2 - ypos );

  // Direction : Spherical coordinates to Cartesian coordinates conversion
  glm::vec3 direction(
    cos(m_verticalAngle) * sin(m_horizontalAngle), 
    sin(m_verticalAngle),
    cos(m_verticalAngle) * cos(m_horizontalAngle)
  );
  
  // Right vector
  glm::vec3 right = glm::vec3(
    sin(m_horizontalAngle - 3.14f/2.0f), 
    0,
    cos(m_horizontalAngle - 3.14f/2.0f)
  );
  
  // Up vector
  glm::vec3 up = glm::cross( right, direction );

  //Move forward
  if (glfwGetKey( m_window, GLFW_KEY_UP )  == GLFW_PRESS 
    || glfwGetKey( m_window, GLFW_KEY_W ) == GLFW_PRESS ) {
    m_position += direction * deltaTime * m_speed;
  }
  // Move backward
  if (glfwGetKey( m_window, GLFW_KEY_DOWN) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_S ) == GLFW_PRESS ) {
    m_position -= direction * deltaTime * m_speed;
  }
  // Strafe right
  if (glfwGetKey( m_window, GLFW_KEY_RIGHT ) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_D ) == GLFW_PRESS) {
    m_position += right * deltaTime * m_speed;
  }
  // Strafe left
  if (glfwGetKey( m_window, GLFW_KEY_LEFT ) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_A ) == GLFW_PRESS) {
    m_position -= right * deltaTime * m_speed;
  }

  float FoV = m_initialFoV;

  // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
  m_projectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
  // Camera matrix
  m_viewMatrix  = glm::lookAt(
    m_position,              // Camera is here
    m_position + direction,  // and looks here : at the same position, plus "direction"
    up                       // Head is up (set to 0,-1,0 to look upside-down)
  );

  lastTime = currentTime;
}

void Camera::autoCamera(const float speed /* = 1.0f*/) {
  static double lastTime = glfwGetTime(); // static to get initialized only once, at first call
  static float cameraDistance = 10.0f;
  static float cameraHeight = 3.0f;

  // Compute time difference between current and last frame
  double currentTime = glfwGetTime();
  float deltaTime = float(currentTime - lastTime);

  float angle = speed * static_cast<float>(currentTime);
  float x = cos(angle) * cameraDistance;
  float z = sin(angle) * cameraDistance;
  glm::vec3 position(x, cameraHeight, z);

  glm::vec3 direction(0.0f, 0.0f, 0.0f); // camera look center
  glm::vec3 up(0.0f, 1.0f, 0.0f);

  float FoV = m_initialFoV;

    // Camera go closer
  if (glfwGetKey( m_window, GLFW_KEY_UP )  == GLFW_PRESS 
    || glfwGetKey( m_window, GLFW_KEY_W ) == GLFW_PRESS ) {
    cameraDistance -= deltaTime * m_speed;
  }
  // Camera go away
  if (glfwGetKey( m_window, GLFW_KEY_DOWN) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_S ) == GLFW_PRESS ) {
    cameraDistance += deltaTime * m_speed;
  }
  // Camera position down
  if (glfwGetKey( m_window, GLFW_KEY_RIGHT ) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_D ) == GLFW_PRESS) {
    cameraHeight += deltaTime * m_speed;
  }
  // Camera position up
  if (glfwGetKey( m_window, GLFW_KEY_LEFT ) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_A ) == GLFW_PRESS) {
    cameraHeight -= deltaTime * m_speed;
  }

   // Swap View mode
  if (glfwGetKey( m_window, GLFW_KEY_T ) == GLFW_PRESS) {
      m_mode = TEXTURE;
  } else if (glfwGetKey( m_window, GLFW_KEY_Y ) == GLFW_PRESS) {
      m_mode = COLOR;
  }

  // reset camera
  if (glfwGetKey( m_window, GLFW_KEY_R ) == GLFW_PRESS) {
    cameraDistance = 10.0f;
    cameraHeight = 3.0f;
  }

  // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
  m_projectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
  // Camera matrix
  m_viewMatrix  = glm::lookAt(position, direction, up);

  lastTime = currentTime;
}