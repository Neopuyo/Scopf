#include "VertexArray.h"


VertexArray::VertexArray() {
  LOGCHECK(glGenVertexArrays(1, &m_rendererID));
}

VertexArray::~VertexArray() {
  LOGCHECK(glDeleteVertexArrays(1, &m_rendererID));

}

// void VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
//   bind();
//   vb.bind();
//   const std::vector<VertexBufferElement> &elements = layout.getElements();
//   unsigned int offset = 0;
//   for (unsigned int i = 0; i < elements.size(); i++) {
//     const VertexBufferElement &element = elements[i];
//     LOGCHECK(glEnableVertexAttribArray(i));
//     LOGCHECK(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), reinterpret_cast<void *>(offset)));
//     offset += element.count * VertexBufferElement::getSizeFor(element.type);
//   }
// }

void VertexArray::addBufferVertexOnly(const VertexBuffer &vb, int attribute, int size) {
  bind();
  vb.bind();
  LOGCHECK(glEnableVertexAttribArray(attribute)); // [!] raw value used for now
  
  LOGCHECK(glVertexAttribPointer(
      attribute,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
      size,                  // size
      GL_FLOAT,           // type
      GL_FALSE,           // normalized?
      0,                  // stride -> here is ok with 0 ?
      (void*)0            // array buffer offset
    ));
}

void VertexArray::bind() const {
  LOGCHECK(glBindVertexArray(m_rendererID));
}

void VertexArray::unbind() const {
  LOGCHECK(glBindVertexArray(0));
}