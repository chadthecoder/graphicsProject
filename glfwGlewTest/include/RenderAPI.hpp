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
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Color;
        glm::vec2 Texture;
        int TexIndex;
    };
    RenderAPI();
public:
    ~RenderAPI();

    int DrawSqaure(const Renderer& renderer, const Shader& shader);
    
    void Bind();
    void Unbind();
};