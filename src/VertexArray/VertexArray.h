#pragma once

#include "errorHandling.h"

#include "VertexBuffer.h"
// #include "vertexBufferLayout.h"

class VertexBuffer;
// class VertexBufferLayout;

class VertexArray {
  private:
    unsigned int m_rendererID;

  public:
    VertexArray();
    ~VertexArray();

    // void addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);
    void addBufferVertexOnly(const VertexBuffer &vb, int attribute, int size);

    void bind() const;
    void unbind() const;
};