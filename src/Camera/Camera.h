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
    ft_glm::mat4 m_translationMatrix;
    ft_glm::mat4 m_rotationMatrix;


    // camera
    ft_glm::vec3 m_position = ft_glm::vec3( 0, 0, 5 ); // Initial position : on +Z
    ft_glm::vec3 m_model_position = ft_glm::vec3(0.0f, 0.0f, 0.0f); // relative center of model

    // Model Rotation
    bool m_autoRotate = true;
    float m_lastRotateSwitchTime = 0.0f;
    float m_lastWireframeSwitchTime = 0.0f;
    float m_rotationRate = 2.0f;

    // Model Tranlsation
    const float m_moveRate = 0.1f;
    const float m_shiftRate = 5.0f;

  public:
    // Model
    ft_glm::vec3 modelCenter = ft_glm::vec3(0.0f, 0.0f, 0.0f); // absolute center of model

    Camera(GLFWwindow *window);
    ~Camera();

    inline ViewMode     getViewMode() const { return m_mode; }
    inline ft_glm::mat4 getViewMatrix() const { return m_viewMatrix; }
    inline ft_glm::mat4 getProjectionMatrix() const { return m_projectionMatrix; }
    inline ft_glm::mat4 getModelMatrix() const { return m_modelMatrix; }
    bool isShiftPressed() const;
    bool isAltPressed() const;
    void showMatrices() const;

    ft_glm::mat4 computeMVP() const;
    void moveModelFromInputs();
    void rotateModelFromInputs();
    void selectRotationSpeedFromInputs();
    void switchAutoRotateFromInputs();
    void switchWireframeFromInputs();
    void enableZoom();
    void autoRotate();
    void translateModelToCenter();
    void translateModelWithVec3(const ft_glm::vec3 &vec3);
    void rotateModelWithVec3(const ft_glm::vec3 &vec3);
};

