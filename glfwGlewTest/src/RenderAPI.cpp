#include "RenderAPI.hpp"

RenderAPI::~RenderAPI()
{
}

int RenderAPI::DrawSqaure(const Renderer& renderer, const Shader& shader)
{
    //Renderer renderer("3D", float *vertices, int sizeVertex, unsigned int *indices, int sizeIndex);
    //renderer.Draw(shader);
    return 0;
}

void RenderAPI::Bind()
{
}

void RenderAPI::Unbind()
{
    //va.Unbind();
    //vb.Unbind();
    //ib.Unbind();
}
