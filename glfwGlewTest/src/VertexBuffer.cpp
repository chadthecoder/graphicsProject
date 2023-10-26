#include "../include/VertexBuffer.hpp"
#include "../include/Errors.hpp"

VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int usage)
{
    GLCall(glGenBuffers(1, &m_RendererID), __FILE__, __LINE__);
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID), __FILE__, __LINE__);
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage), __FILE__, __LINE__);
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID), __FILE__, __LINE__);
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID), __FILE__, __LINE__);
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0), __FILE__, __LINE__);
}

unsigned int VertexBuffer::GetRendererID() const
{
    return m_RendererID;
}