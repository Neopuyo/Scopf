#include "VertexArray.h"


VertexArray::VertexArray() {
  LOGCHECK(glGenVertexArrays(1, &m_rendererID));
}

VertexArray::~VertexArray() {
  LOGCHECK(glDeleteVertexArrays(1, &m_rendererID));

}

void VertexArray::addBufferVertexOnly(const VertexBuffer &vb, int attribute, int size) {
  bind();
  vb.bind();
  LOGCHECK(glEnableVertexAttribArray(attribute)); // [!] raw value used for now
  
  LOGCHECK(glVertexAttribPointer(
      attribute,          // attribute 0 linked to layout locatiuon in shader.
      size,               // size
      GL_FLOAT,           // type
      GL_FALSE,           // normalized?
      0,                  // stride // will be optimised with use of a bufferLayout in bigger project
      (void*)0            // array buffer offset // same as above
    ));
}

void VertexArray::bind() const {
  LOGCHECK(glBindVertexArray(m_rendererID));
}

void VertexArray::unbind() const {
  LOGCHECK(glBindVertexArray(0));
}