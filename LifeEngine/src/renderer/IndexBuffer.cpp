#include "IndexBuffer.h"

#include <GL/glew.h>

#include "../util/Debug.h"

namespace LifeEngine {

    IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) {
        GLCall(glGenBuffers(1, &m_RendererID));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

        m_Count = count;
    }

    IndexBuffer::~IndexBuffer() {
        Unbind();
        GLCall(glDeleteBuffers(1, &m_RendererID));
    }

    void IndexBuffer::Bind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    }

    void IndexBuffer::Unbind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

}
