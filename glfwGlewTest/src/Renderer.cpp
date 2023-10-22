#include "Renderer.hpp"

Renderer::Renderer(std::string dimension, float *vertices, int sizeVertex, unsigned int *indices, int sizeIndex)
    : vb(vertices, sizeVertex, GL_DYNAMIC_DRAW), ib(indices, sizeIndex, GL_DYNAMIC_DRAW)
{
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA), __FILE__, __LINE__);
    GLCall(glEnable(GL_BLEND), __FILE__, __LINE__);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE); 

    //square
    if(dimension == "2D")
    {

       /*  layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 2); */
        
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 2);

        va.AddBuffer(vb, layout);
    }
    //pyramid, should work for others in same format
    else if(dimension == "3D")
    {
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 2);
    
        va.AddBuffer(vb, layout);
    }
}

Renderer::~Renderer()
{
    //need to take care of unbinding later, where?
    //va.Unbind();
    //vb.Unbind();
    //ib.Unbind();
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT), __FILE__, __LINE__);
}

void Renderer::Draw(const Shader& shader) const //Draw(float* vertices, unsigned int* indexArray, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr), __FILE__, __LINE__);
}

void Renderer::Bind()
{
}

void Renderer::Unbind()
{
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
}