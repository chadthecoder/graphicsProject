#include "Shader.hpp"

Shader::Shader(const std::string& filepath) : m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
    
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID), __FILE__, __LINE__);
}

ShaderProgramSource Shader::ParseShader(const std::string &filepath)
{

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr), __FILE__, __LINE__);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::Bind() const
{
    //std::cout << "calling shader bind, id is: " << m_RendererID << "\n";
    GLCall(glUseProgram(m_RendererID), __FILE__, __LINE__);
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0), __FILE__, __LINE__);
}

void Shader::SetUniform1i(const std::string& name, int i0)
{
    //std::cout << "error?: " << name << " : i0: " << i0 << "\n";
    GLCall(glUniform1i(GetUniformLocation(name), i0), __FILE__, __LINE__);
}

void Shader::SetUniform1f(const std::string& name, float f0)
{
    GLCall(glUniform1f(GetUniformLocation(name), f0), __FILE__, __LINE__);
}

void Shader::SetUniform2f(const std::string& name, float f0, float f1)
{
    GLCall(glUniform2f(GetUniformLocation(name), f0, f1), __FILE__, __LINE__);
}

void Shader::SetUniform4f(const std::string &name, float f0, float f1, float f2, float f3)
{
    GLCall(glUniform4f(GetUniformLocation(name), f0, f1, f2, f3), __FILE__, __LINE__);
}

void Shader::SetUniformMat4f(const std::string &name, const glm::mat4& matrix)
{
     GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]), __FILE__, __LINE__);
}

unsigned int Shader::GetRendererID()
{
    return m_RendererID;
}

int Shader::GetUniformLocation(const std::string &name)
{
    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    {
        return m_UniformLocationCache[name];
    }

    int location = GLCall2(glGetUniformLocation(m_RendererID, name.c_str()), __FILE__, __LINE__);
    if(location == -1)
    {
        std::cout << "Warning: Uniform " << name << " doesn't exist!\n";
    }

    m_UniformLocationCache[name] = location;

    return location;
}