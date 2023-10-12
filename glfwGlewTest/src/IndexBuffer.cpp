#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_Count(count)
{
    GLCall(glGenBuffers(1, &m_RendererID), __FILE__, __LINE__);
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID), __FILE__, __LINE__);
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW), __FILE__, __LINE__);
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID), __FILE__, __LINE__);
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID), __FILE__, __LINE__);
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0), __FILE__, __LINE__);
}