#include "RenderAPI.hpp"

RenderAPI::RenderAPI(std::string dimension, float *vertices, int sizeVertex, unsigned int *indices, int sizeIndex)
    : vb(vertices, sizeVertex), ib(indices, sizeIndex)
{
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

RenderAPI::~RenderAPI()
{
}

int RenderAPI::Draw(const Renderer& renderer, const Shader& shader)
{
    renderer.Draw(va, ib, shader);
    return 0;
}

void RenderAPI::Bind()
{
}

void RenderAPI::Unbind()
{
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
}
