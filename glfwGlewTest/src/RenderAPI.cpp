#include "RenderAPI.hpp"

RenderAPI::~RenderAPI()
{
}

int RenderAPI::Draw(const Renderer& renderer, const Shader& shader)
{
    renderer.Draw(shader);
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
