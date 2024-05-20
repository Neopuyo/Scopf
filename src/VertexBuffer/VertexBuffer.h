#pragma once

#include "errorHandling.h"

class VertexBuffer {
  private:
    unsigned int m_rendererID;
  public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;

    inline unsigned int getID() const { return m_rendererID; }
};