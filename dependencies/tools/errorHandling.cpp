#include "errorHandling.h"

void clearError() {
  while (glGetError() != GL_NO_ERROR);
}

bool noLogCall(const char *function, const char *file, int line ) {
  if (GLenum error = glGetError()) {
    std::cout << "\033[1;31m" << "[OpenGL Error]" << " [code: " << error << "] [hexa: ";
    std::cout << std::showbase << std::hex << error  << "]" << std::dec  << std::noshowbase << "\033[0m" << std::endl;
    std::cout << file << "\033[1;33m" << " " << function << "\033[0m" << " : line : " << "\033[1;32m" << line << "\033[0m" << std::endl;
    std::cout << "----------\n" << std::endl;
    return false;
  }
  return true;
}