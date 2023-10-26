#pragma once

#include "Errors.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Vertex.hpp"

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
    Shader shader;
public:
    //Renderer(std::string dimension, float *vertices, int sizeVertex, unsigned int *indices, int sizeIndex);
    Renderer(std::string dimension, int maxVerticesSize, unsigned int *indices, int sizeIndex, const std::string& filepath);
    ~Renderer();

    static std::array<openglStuff::Vertex, 5> Pyramid(float x, float y, float z);

    void Clear() const;
    void Draw(const void* data, unsigned int size) const; // unsigned int* indexArray void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

    void Bind();
    void Unbind();
};