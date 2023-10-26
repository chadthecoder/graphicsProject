#include "Renderer.hpp"

Renderer::Renderer(std::string dimension, int maxVerticesSize, unsigned int *indices,
     int sizeIndex, const std::string& shaderPath, const std::string& texturePath)
    : vb(nullptr, maxVerticesSize, GL_DYNAMIC_DRAW), ib(indices, sizeIndex, GL_DYNAMIC_DRAW),
        shader(shaderPath), texture(texturePath, dimension)
    //: vb(vertices, sizeVertex, GL_DYNAMIC_DRAW), ib(indices, sizeIndex, GL_DYNAMIC_DRAW)
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
    Unbind();
}


//gives pyramid rendered in positive directions from given point
std::array<openglStuff::Vertex, 5> Renderer::Pyramid(float x, float y, float z)
{

    float size = 1.0f;

/* 0.0f, 0.5f,  1.0f,     0.83f, 0.70f, 0.44f,	    0.0f, 0.0f,
	0.0f, 0.5f, 0.0f,     0.83f, 0.70f, 0.44f,	    5.0f, 0.0f,
	1.0f, 0.5f, 0.0f,     0.83f, 0.70f, 0.44f,	    0.0f, 0.0f,
	1.0f, 0.5f,  1.0f,     0.83f, 0.70f, 0.44f,	    5.0f, 0.0f,
	0.5f, 1.3f,  0.5f,     0.92f, 0.86f, 0.76f,	    2.5f, 5.0f, */

    openglStuff::Vertex v0;
    //float* data = glm::value_ptr(vec);
    v0.Position = glm::vec3(x+0.0f, y+0.5f,  z+1.0f);
    v0.Color = glm::vec3(0.83f, 0.70f, 0.44f);
    v0.Texture = glm::vec2(0.0f, 0.0f);

    openglStuff::Vertex v1;
    v1.Position = glm::vec3(x+0.0f, y+0.5f, z+0.0f);
    v1.Color = glm::vec3(0.83f, 0.70f, 0.44);
    v1.Texture = glm::vec2(5.0f, 0.0f);

    openglStuff::Vertex v2;
    v2.Position = glm::vec3(x+1.0f, y+0.5f, z+0.0f);
    v2.Color = glm::vec3(0.83f, 0.70f, 0.44);
    v2.Texture = glm::vec2(0.0f, 0.0f);

    openglStuff::Vertex v3;
    v3.Position = glm::vec3(x+1.0f, y+0.5f,  z+1.0f);
    v3.Color = glm::vec3(0.83f, 0.70f, 0.44);
    v3.Texture = glm::vec2(5.0f, 0.0f);

    openglStuff::Vertex v4;
    v4.Position = glm::vec3(x+0.5f, y+1.0f,  z+0.5f);
    v4.Color = glm::vec3(0.92f, 0.86f, 0.76f);
    v4.Texture = glm::vec2(2.5f, 5.0f);

    return { v0, v1, v2, v3, v4 };
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT), __FILE__, __LINE__);
}

void Renderer::Draw(const void* data, unsigned int size) const //Draw(float* vertices, unsigned int* indexArray, const Shader& shader) const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vb.GetRendererID()), __FILE__, __LINE__);
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data), __FILE__, __LINE__);

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr), __FILE__, __LINE__);
}

void Renderer::SetUniform1i(const std::string& name, int i0)
{
    shader.SetUniform1i(name, i0);
}

void Renderer::SetUniform1f(const std::string& name, float f0)
{
    shader.SetUniform1f(name, f0);
}

void Renderer::SetUniform2f(const std::string& name, float f0, float f1)
{
    shader.SetUniform2f(name, f0, f1);
}

void Renderer::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
    shader.SetUniform4f(name, f0, f1, f2, f3);
}

void Renderer::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    shader.SetUniformMat4f(name, matrix);
}

Shader& Renderer::GetShader()
{
    return shader;
}

void Renderer::Bind()
{
    shader.Bind();
    va.Bind();
    vb.Bind();
    ib.Bind();
    texture.Bind();
}

void Renderer::Unbind()
{
    shader.Unbind();
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    texture.Unbind();
}