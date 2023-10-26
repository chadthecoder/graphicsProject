#pragma once

class VertexBuffer
{
private:
    unsigned int m_RendererID;
public:
    VertexBuffer(const void* data, unsigned int size, unsigned int usage);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    //for some reason gives error if this function isnt const
    unsigned int GetRendererID() const;
};
