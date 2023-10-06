#pragma once

#include "../include/Errors.hpp"
#include "../include/VertexArray.hpp"
#include "../include/IndexBuffer.hpp"
#include "../include/Shader.hpp"

class Renderer
{
private:
    /* data */
public:
    Renderer();
    ~Renderer();

    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};