#include "../include/VertexBufferLayout.hpp"

VertexBufferLayout::VertexBufferLayout() : m_Stride(0)
{
}

VertexBufferLayout::~VertexBufferLayout()
{
}

void VertexBufferLayout::Push(unsigned int type, unsigned int count)
{
        if(type == GL_UNSIGNED_BYTE) m_Elements.push_back({ type, count, GL_TRUE });
        else m_Elements.push_back({ type, count, GL_FALSE });
        m_Stride += count * VertexBufferElement::GetSizeOfType(type);
}
