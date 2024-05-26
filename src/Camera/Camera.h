#pragma once

// Include GLFW
#include "../glad/glad.h"
#include <GLFW/glfw3.h>

#include <ft_glm.h>

#include "errorHandling.h"
#include "Window.h"

enum ViewMode {
  COLOR,
  TEXTURE
};

class Camera {
  private:
    GLFWwindow *m_window;
    ViewMode m_mode;
    ft_glm::mat4 m_projectionMatrix;
    ft_glm::mat4 m_viewMatrix;
    ft_glm::mat4 m_modelMatrix;

    ft_glm::vec3 m_position = ft_glm::vec3( 0, 0, 5 ); // Initial position : on +Z
    
    float m_horizontalAngle = 3.14f; // Initial horizontal angle : toward -Z
    float m_verticalAngle = 0.0f;    // Initial vertical angle : none
    float m_initialFoV = 45.0f;      // Initial Field of View
    float m_speed = 3.0f;            // 3 units / second
    float m_mouseSpeed = 0.001f;

    const float m_moveRate = 0.1f;
    const float m_shiftRate = 5.0f;

  public:
    Camera(GLFWwindow *window);
    ~Camera();

    inline ViewMode     getViewMode() const { return m_mode; }
    inline ft_glm::mat4 getViewMatrix() const { return m_viewMatrix; }
    inline ft_glm::mat4 getProjectionMatrix() const { return m_projectionMatrix; }
    inline ft_glm::mat4 getModelMatrix() const { return m_modelMatrix; }
    bool isShiftPressed() const;
    void showMatrices() const;

    ft_glm::mat4 computeMVP() const;
    void moveModelFromInputs();
    void computeMatricesFromInputs();
    void enableZoom();
    void translateModelWithVec3(const ft_glm::vec3 &vec3);
};

