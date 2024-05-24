#pragma once

#include "errorHandling.h"
#include "VertexBuffer.h"

class VertexBuffer;

class VertexArray {
  private:
    unsigned int m_rendererID;

  public:
    VertexArray();
    ~VertexArray();

    void addBufferVertexOnly(const VertexBuffer &vb, int attribute, int size);

    void bind() const;
    void unbind() const;
};