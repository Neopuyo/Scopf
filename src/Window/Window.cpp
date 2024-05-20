#include "Window.h"

Window::Window(int width, int height, const char *title) {
 if (!glfwInit()) {
    std::cout << "glfwInit() failed" << std::endl;
    return;
  }

  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL (4.6)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, title, NULL, NULL);
  if( window == NULL ){
      std::cout << "Failed to open GLFW window." << std::endl;
      glfwTerminate();
      return;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // loop speed

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "couldn't load opengl" << std::endl;
    glfwTerminate();
    return;
  }

  std::cout << "OpenGl version : " << glGetString(GL_VERSION) << std::endl;
}

Window::~Window() {
  glfwTerminate();
}

bool Window::shouldClose() {
  return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
  glfwSwapBuffers(window);
}

void Window::pollEvents() {
  glfwPollEvents();
}

void Window::setInputMode() {
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

int Window::getKey(int key) const {
  return glfwGetKey(window, key);
}
