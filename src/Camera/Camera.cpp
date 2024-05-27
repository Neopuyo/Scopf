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

bool Camera::isAltPressed() const { 
  return glfwGetKey(m_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS;
}

void Camera::showMatrices() const {
  getProjectionMatrix().show("projection matrix");
  getViewMatrix().show("view matrix");
  getModelMatrix().show("model matrix");
  computeMVP().show("MVP");
}

void Camera::translateModelToCenter() {
  ft_glm::mat4 translateMatrix = ft_glm::translate(ft_glm::mat4(1.0f), -modelCenter);
  m_modelMatrix  =  translateMatrix * m_modelMatrix;
}

void Camera::translateModelWithVec3(const ft_glm::vec3 &vec3) {
  ft_glm::mat4 translateMatrix = ft_glm::translate(ft_glm::mat4(1.0f), vec3);
  m_modelMatrix  =  translateMatrix * m_modelMatrix;
}

void Camera::rotateModelWithVec3(const ft_glm::vec3 &vec3) {
  ft_glm::mat4 translateToOrigin = ft_glm::translate(ft_glm::mat4(1.0f), -m_model_position);
  ft_glm::mat4 rotateMatrix = ft_glm::rotate(ft_glm::mat4(1.0f), ft_glm::radians(m_rotationRate), vec3);
  ft_glm::mat4 translateBackToPos = ft_glm::translate(ft_glm::mat4(1.0f), m_model_position);

  m_modelMatrix = translateBackToPos * rotateMatrix * translateToOrigin * m_modelMatrix;
}

ft_glm::mat4 Camera::computeMVP() const {
  return m_projectionMatrix * m_viewMatrix * m_modelMatrix;
}

void Camera::moveModelFromInputs() {

  ft_glm::vec3 moveVec = ft_glm::vec3(0.0f, 0.0f, 0.0f);
  float value = m_moveRate * (isShiftPressed() ? m_shiftRate : 1.0f);

  // Moving Y axis (+)
  if ((glfwGetKey( m_window, GLFW_KEY_UP )  == GLFW_PRESS 
    || glfwGetKey( m_window, GLFW_KEY_W ) == GLFW_PRESS ) && !isAltPressed()) {
    moveVec.y += value;
    m_model_position.y += value;
  }
  // Moving Y axis (-)
  if ((glfwGetKey( m_window, GLFW_KEY_DOWN) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_S ) == GLFW_PRESS ) && !isAltPressed()) {
    moveVec.y -= value;
    m_model_position.y -= value;
  }

  // Moving X axis (+)
  if ((glfwGetKey( m_window, GLFW_KEY_RIGHT ) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_D ) == GLFW_PRESS) && !isAltPressed()) {
    moveVec.x += value;
    m_model_position.x += value;
  }

  // Moving X axis (-)
  if ((glfwGetKey( m_window, GLFW_KEY_LEFT ) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_A ) == GLFW_PRESS) && !isAltPressed()) {
    moveVec.x -= value;
    m_model_position.x -= value;
  }

  // Moving Z axis (+)
  if ((glfwGetKey( m_window, GLFW_KEY_PAGE_UP ) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_C ) == GLFW_PRESS) && !isAltPressed()) {
    moveVec.z += value;
    m_model_position.z += value;
  }

  // Moving Z axis (-)
  if ((glfwGetKey( m_window, GLFW_KEY_PAGE_DOWN ) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_V ) == GLFW_PRESS) && !isAltPressed()) {
    moveVec.z -= value;
    m_model_position.z -= value;
  }

   // Swap View mode
  if (glfwGetKey( m_window, GLFW_KEY_T ) == GLFW_PRESS) {
      m_mode = TEXTURE;
  } else if (glfwGetKey( m_window, GLFW_KEY_Y ) == GLFW_PRESS) {
      m_mode = COLOR;
  }

  translateModelWithVec3(moveVec);
}

void Camera::rotateModelFromInputs() {

  bool rotateAsked = false;
  ft_glm::vec3 rotateVec = ft_glm::vec3(0.0f, 0.0f, 0.0f);

    // Moving Y axis (+)
  if ((glfwGetKey( m_window, GLFW_KEY_UP )  == GLFW_PRESS 
    || glfwGetKey( m_window, GLFW_KEY_W ) == GLFW_PRESS ) && isAltPressed()) {
    rotateVec.y = +1.0f;
    rotateAsked = true;
  }
  // Moving Y axis (-)
  if ((glfwGetKey( m_window, GLFW_KEY_DOWN) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_S ) == GLFW_PRESS ) && isAltPressed()) {
    rotateVec.y = -1.0f;
    rotateAsked = true;
  }

  // Moving X axis (+)
  if ((glfwGetKey( m_window, GLFW_KEY_RIGHT ) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_D ) == GLFW_PRESS) && isAltPressed()) {
    rotateVec.x = +1.0f;
    rotateAsked = true;
  }

  // Moving X axis (-)
  if ((glfwGetKey( m_window, GLFW_KEY_LEFT ) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_A ) == GLFW_PRESS) && isAltPressed()) {
    rotateVec.x = -1.0f;
    rotateAsked = true;
  }

  // Moving Z axis (+)
  if ((glfwGetKey( m_window, GLFW_KEY_PAGE_UP ) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_C ) == GLFW_PRESS) && isAltPressed()) {
    rotateVec.z = +1.0f;
    rotateAsked = true;
  }

  // Moving Z axis (-)
  if ((glfwGetKey( m_window, GLFW_KEY_PAGE_DOWN ) == GLFW_PRESS
    || glfwGetKey( m_window, GLFW_KEY_V ) == GLFW_PRESS) && isAltPressed()) {
    rotateVec.z = -1.0f;
    rotateAsked = true;
  }

  if (rotateAsked) {
    rotateModelWithVec3(rotateVec);
  }
}

void Camera::autoRotate() {
  ft_glm::vec3 rotateVec = ft_glm::vec3(0.0f, 1.0f, 0.0f);

  if (m_autoRotate) {
    rotateModelWithVec3(rotateVec);
  }
}


void Camera::selectRotationSpeedFromInputs() {
  static float speeds[10] = {0.1f, 0.5f, 1.0f, 2.0f, 3.0f, 5.0f, 8.0f, 12.0f, 28.0f, 50.0f};

  if (glfwGetKey( m_window, GLFW_KEY_KP_0 )  == GLFW_PRESS)
    m_rotationRate = speeds[0];
  else if (glfwGetKey( m_window, GLFW_KEY_KP_1 )  == GLFW_PRESS)
    m_rotationRate = speeds[1];
  else if (glfwGetKey( m_window, GLFW_KEY_KP_2 )  == GLFW_PRESS)
    m_rotationRate = speeds[2];
  else if (glfwGetKey( m_window, GLFW_KEY_KP_3 )  == GLFW_PRESS)
    m_rotationRate = speeds[3];
  else if (glfwGetKey( m_window, GLFW_KEY_KP_4 )  == GLFW_PRESS)
    m_rotationRate = speeds[4];
  else if (glfwGetKey( m_window, GLFW_KEY_KP_5 )  == GLFW_PRESS)
    m_rotationRate = speeds[5];
  else if (glfwGetKey( m_window, GLFW_KEY_KP_6 )  == GLFW_PRESS)
    m_rotationRate = speeds[6];
  else if (glfwGetKey( m_window, GLFW_KEY_KP_7 )  == GLFW_PRESS)
    m_rotationRate = speeds[7];
  else if (glfwGetKey( m_window, GLFW_KEY_KP_8 )  == GLFW_PRESS)
    m_rotationRate = speeds[8];
  else if (glfwGetKey( m_window, GLFW_KEY_KP_9 )  == GLFW_PRESS)
    m_rotationRate = speeds[9];
}


void Camera::switchAutoRotateFromInputs() {
  if (glfwGetKey( m_window, GLFW_KEY_SPACE ) == GLFW_PRESS) {
    float current = glfwGetTime();
    float elapsed = current - m_lastRotateSwitchTime;

    if (elapsed >= 0.5f) {
      m_autoRotate = !m_autoRotate;
      m_lastRotateSwitchTime = current;
    }
  }
}

void Camera::switchWireframeFromInputs() {
  if (glfwGetKey( m_window, GLFW_KEY_KP_DIVIDE) == GLFW_PRESS 
  || glfwGetKey( m_window, GLFW_KEY_KP_MULTIPLY) == GLFW_PRESS) {
    float current = glfwGetTime();
    float elapsed = current - m_lastWireframeSwitchTime;

    if (elapsed >= 0.5f) {
      if (glfwGetKey( m_window, GLFW_KEY_KP_DIVIDE) == GLFW_PRESS) {
        LOGCHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
      } else {
        LOGCHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
      }
      m_lastWireframeSwitchTime = current;
    }
  }
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
    m_rotationRate = 2.0f;
    m_modelMatrix = ft_glm::translate(ft_glm::mat4(1.0f), -modelCenter);
  }

  // Camera matrix
  m_viewMatrix  = ft_glm::lookAt(position, direction, up);
}