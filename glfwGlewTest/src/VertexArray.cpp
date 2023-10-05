#include "../include/Errors.hpp"
#include "../include/VertexArray.hpp"
#include "../include/VertexBuffer.hpp"
#include "../include/VertexBufferLayout.hpp"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID), __FILE__, __LINE__);
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID), __FILE__, __LINE__);
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    intptr_t offset = 0;
    for(unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i), __FILE__, __LINE__);
        GLCall(glVertexAttribPointer(i, element.count, element.type,
            element.normalized, layout.GetStride(), (const void*)offset), __FILE__, __LINE__);
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID), __FILE__, __LINE__);
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0), __FILE__, __LINE__);
}
