#pragma once

#include "../include/Errors.hpp"
#include "../include/VertexArray.hpp"
#include "../include/IndexBuffer.hpp"
#include "../include/Shader.hpp"

class Renderer
{
private:
    float *vertices;
    int sizeVertex;
    unsigned int *indices;
    int sizeIndex;

    VertexArray va;
    VertexBuffer vb;
    VertexBufferLayout layout;
    IndexBuffer ib;
public:
    Renderer(std::string dimension, float *vertices, int sizeVertex, unsigned int *indices, int sizeIndex);
    ~Renderer();

    void Clear() const;
    void Draw(const Shader& shader) const; // unsigned int* indexArray void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

    void Bind();
    void Unbind();
};