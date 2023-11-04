#pragma once

#include "Errors.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"

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
    Texture texture;
public:
    //Renderer(std::string dimension, float *vertices, int sizeVertex, unsigned int *indices, int sizeIndex);
    Renderer(std::string dimension, int maxVerticesSize, unsigned int *indices,
        int sizeIndex, const std::string& shaderPath, const std::string& texturePath);
    ~Renderer();

    static std::array<openglStuff::Vertex, 5> Pyramid(float x, float y, float z);
    //static std::array<openglStuff::Vertex, 8> Cube(float x, float y, float z);
    openglStuff::Vertex* Cube(openglStuff::Vertex* target, float x, float y, float z);
    openglStuff::Vertex* Cube2(openglStuff::Vertex* target, float x, float y, float z);

    void Clear() const;
    void Draw(const void* data, unsigned int size) const; // unsigned int* indexArray void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

    //shader functions
    void SetUniform1i(const std::string& name, int i0);
    void SetUniform1f(const std::string& name, float f0);
    void SetUniform2f(const std::string& name, float f0, float f1);
    void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

    Shader& GetShader();

    void Bind() const;
    void Unbind();
};