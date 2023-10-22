#pragma once

#pragma once

#include "../include/Errors.hpp"
#include "../include/VertexBuffer.hpp"
#include "../include/VertexBufferLayout.hpp"

class VertexArray
{
private:
    unsigned int m_RendererID;
public:
    VertexArray(/* args */);
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind() const;
    void Unbind() const;
};