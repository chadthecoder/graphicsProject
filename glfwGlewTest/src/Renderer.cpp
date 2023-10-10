#include "../include/Renderer.hpp"

Renderer::Renderer(/* args */)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE); 
}

Renderer::~Renderer()
{
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT), __FILE__, __LINE__);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr), __FILE__, __LINE__);
}