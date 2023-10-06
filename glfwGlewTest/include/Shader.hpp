#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "../include/Errors.hpp"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, unsigned int> m_UniformLocationCache;
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform1f(const std::string& name, float f0);
    void SetUniform2f(const std::string& name, float f0, float f1);
    void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
private:
    ShaderProgramSource ParseShader(const std::string &filepath);
    unsigned int CompileShader(unsigned int type, const std::string &source);
    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);

    unsigned int GetUniformLocation(const std::string& name);
};