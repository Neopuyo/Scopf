#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
  LOGCHECK(glGenBuffers(1, &m_rendererID));
  LOGCHECK(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
  LOGCHECK(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
  LOGCHECK(glDeleteBuffers(1, &m_rendererID));
}

void VertexBuffer::bind() const {
  LOGCHECK(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void VertexBuffer::unbind() const {
  LOGCHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}