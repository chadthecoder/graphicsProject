#pragma once

#include "Errors.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Sound.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

class RenderAPI
{
private:
    RenderAPI();
public:
    ~RenderAPI();

    int DrawSqaure(const Renderer& renderer, const Shader& shader);
    
    void Bind();
    void Unbind();
};