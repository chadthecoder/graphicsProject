#pragma once

#include "Errors.hpp"

class IndexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count, unsigned int usage);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline void GetCount2() const {  std::cout << m_Count << std::endl; }
    inline unsigned int GetCount() const { return m_Count; }
};
