#include "Camera.h"

Camera::Camera(GLFWwindow *window) : m_window(window), m_mode(COLOR) {
  m_projectionMatrix = ft_glm::perspective(ft_glm::radians(45.0f), static_cast<float>(WIN_WIDTH / WIN_HEIGHT), 0.1f, 100.0f);
  m_viewMatrix = ft_glm::lookAt(
      ft_glm::vec3(4, 3, -3), // Camera is at (4,3,3), in World Space
      ft_glm::vec3(0, 0, 0), // and looks at the origin
      ft_glm::vec3(0, +1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
  );
  m_modelMatrix = ft_glm::mat4(1.0f);
}

Camera::~Camera() {}

bool Camera::isShiftPressed() const { 
  return glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
}

void Camera::showMatrices() const {
  getProjectionMatrix().show("projection matrix");
  getViewMatrix().show("view matrix");
  getModelMatrix().show("model matrix");
  computeMVP().show("mvp matrix");
}

void Camera::translateModelWithVec3(const ft_glm::vec3 &vec3) {
  ft_glm::mat4 translateMatrix = ft_glm::translate(ft_glm::mat4(1.0f), vec3);
  m_modelMatrix  =  translateMatrix * m_modelMatrix;
}

ft_glm::mat4 Camera::computeMVP() const {
  return m_projectionMatrix * m_viewMatrix * m_modelMatrix;
}

void Camera::moveModelFromInputs() {

  ft_glm::vec3 moveVec = ft_glm::vec3(0.0f, 0.0f, 0.0f);

  // Moving Y axis (+)
  if (glfwGetKey( m_window, GLFW_KEY_UP )  == GLFW_PRESS 
    || glfwGetKey( m_window, GLFW_KEY_W ) == GLFW_PRESS ) {
    moveVec.y += m_moveRate * (isShiftPressed() ? m_shiftRate : 1.0f);
  }
  // Moving Y axis (-)
  if (glfwGetKey( m_window, GLFW_KEY_DOWN) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_S ) == GLFW_PRESS ) {
    moveVec.y -= m_moveRate * (isShiftPressed() ? m_shiftRate : 1.0f);
  }

  // Moving X axis (+)
  if (glfwGetKey( m_window, GLFW_KEY_RIGHT ) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_D ) == GLFW_PRESS) {
    moveVec.x += m_moveRate * (isShiftPressed() ? m_shiftRate : 1.0f);
  }

  // Moving X axis (-)
  if (glfwGetKey( m_window, GLFW_KEY_LEFT ) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_A ) == GLFW_PRESS) {
    moveVec.x -= m_moveRate * (isShiftPressed() ? m_shiftRate : 1.0f);;
  }

  // Moving Z axis (+)
  if (glfwGetKey( m_window, GLFW_KEY_PAGE_UP ) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_C ) == GLFW_PRESS) {
    moveVec.z += m_moveRate * (isShiftPressed() ? m_shiftRate : 1.0f);
  }

  // Moving Z axis (-)
  if (glfwGetKey( m_window, GLFW_KEY_PAGE_DOWN ) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_V ) == GLFW_PRESS) {
    moveVec.z -= m_moveRate * (isShiftPressed() ? m_shiftRate : 1.0f);
  }

   // Swap View mode
  if (glfwGetKey( m_window, GLFW_KEY_T ) == GLFW_PRESS) {
      m_mode = TEXTURE;
  } else if (glfwGetKey( m_window, GLFW_KEY_Y ) == GLFW_PRESS) {
      m_mode = COLOR;
  }

  translateModelWithVec3(moveVec);
}



void Camera::enableZoom() {
  static float cameraDistance = 10.0f;
  static float cameraHeight = 3.0f;

  float angle = 0.0f;
  float x = cos(angle) * cameraDistance;
  float z = sin(angle) * cameraDistance;
  
  ft_glm::vec3 position(x, cameraHeight, z);
  ft_glm::vec3 direction(0.0f, 0.0f, 0.0f); // camera look center
  ft_glm::vec3 up(0.0f, 1.0f, 0.0f);

  // Camera go closer
  if (glfwGetKey( m_window, GLFW_KEY_KP_ADD )  == GLFW_PRESS ) {
    cameraDistance -=  m_moveRate * (isShiftPressed() ? m_shiftRate : 1.0f);
    if (cameraDistance < 0.1f) {
      cameraDistance = 0.1f;
    }
  }
  // Camera go away
  if (glfwGetKey( m_window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS ) {
    cameraDistance +=  m_moveRate * (isShiftPressed() ? m_shiftRate : 1.0f);
  }

  // reset camera
  if (glfwGetKey( m_window, GLFW_KEY_R ) == GLFW_PRESS) {
    cameraDistance = 10.0f;
    cameraHeight = 3.0f;
  }

  // Camera matrix
  m_viewMatrix  = ft_glm::lookAt(position, direction, up);
}














/* -----------------------------------  [!] -------------------------------- */

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
  ft_glm::vec3 direction(
    cos(m_verticalAngle) * sin(m_horizontalAngle), 
    sin(m_verticalAngle),
    cos(m_verticalAngle) * cos(m_horizontalAngle)
  );
  
  // Right vector
  ft_glm::vec3 right = ft_glm::vec3(
    sin(m_horizontalAngle - 3.14f/2.0f), 
    0,
    cos(m_horizontalAngle - 3.14f/2.0f)
  );
  
  // Up vector
  ft_glm::vec3 up = ft_glm::cross( right, direction );

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
  m_projectionMatrix = ft_glm::perspective(ft_glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
  // Camera matrix
  m_viewMatrix  = ft_glm::lookAt(
    m_position,              // Camera is here
    m_position + direction,  // and looks here : at the same position, plus "direction"
    up                       // Head is up (set to 0,-1,0 to look upside-down)
  );

  lastTime = currentTime;
}