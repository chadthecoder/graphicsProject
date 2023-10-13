#include "../include/Texture.hpp"

Texture::Texture(const std::string& path, std::string dimension)
    : m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr),
      m_Width(0), m_Height(0), m_BPP(0), firstLoad(true)
{
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4); //four channels for rgba

    GLCall(glGenTextures(1,&m_RendererID), __FILE__, __LINE__);
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID), __FILE__, __LINE__);

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR), __FILE__, __LINE__);
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), __FILE__, __LINE__);
    if(dimension=="2D")
    {
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), __FILE__, __LINE__);
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), __FILE__, __LINE__);
    }
    else if(dimension=="3D")
    {
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT), __FILE__, __LINE__);
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT), __FILE__, __LINE__);
    }
    else //handle later?
    {}    
    
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer), __FILE__, __LINE__);
    GLCall(glBindTexture(GL_TEXTURE_2D, 0), __FILE__, __LINE__);

    if(m_LocalBuffer) stbi_image_free(m_LocalBuffer);
    else std::cout << "stbi error: " << stbi_failure_reason() << "\n";
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &m_RendererID), __FILE__, __LINE__);
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot), __FILE__, __LINE__);
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID), __FILE__, __LINE__);
}

void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0), __FILE__, __LINE__);
}


