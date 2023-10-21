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
        int floatsPerVertex = 4;

        layout.Push(GL_FLOAT, 2);
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
    /* VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices)); //VertexBuffer vb(positionsPyramid, sizeof(positionsPyramid));

    float test = 0.5f;
    float *testy = &test;

    float test2[] = { 0.5f, 1.0f };
    auto test3 = test2+sizeof(float);
    auto test4 = &test3;
    **test4 = **test4 + 1.0f;
    //test4 = test4 + 1.0f;
    std::cout << "hi: " << test2 << " : " << *(test2+sizeof(float)) << " : " << *test4 << "\n";

    //for 2d square
    //int floatsPerVertex = 4;
    //VertexBuffer vb(positions, 4 * floatsPerVertex * sizeof(float));
     //VertexBufferLayout layout;
    //layout.Push(GL_FLOAT, 2);
    //layout.Push(GL_FLOAT, 2); 

    VertexBufferLayout layoutPyramid;
    layoutPyramid.Push(GL_FLOAT, 3);
    layoutPyramid.Push(GL_FLOAT, 3);
    layoutPyramid.Push(GL_FLOAT, 2);
    
    va.AddBuffer(vb, layoutPyramid);

    IndexBuffer ib(indexArray, 18); //IndexBuffer ib(indicesPyramid, 18); */

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