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
    float *vertices;
    int sizeVertex;
    unsigned int *indices;
    int sizeIndex;

    VertexArray va;
    VertexBuffer vb;
    VertexBufferLayout layout;
    IndexBuffer ib;

    RenderAPI();
public:
    ~RenderAPI();

    int Draw(const Renderer& renderer, const Shader& shader);
    
    void Bind();
    void Unbind();
};