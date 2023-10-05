#include "../include/Errors.hpp"

void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(int test, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cout << "GL Error(Hex: "
            << std::hex
            << error
            << ")\nError in File: "
            << __FILE__
            << "\nError in Line: "
            <<  __LINE__
            << "\nError in Function: "
            << test
            << "\n\n";
        return false;
    }
    return true;
}

bool GLLogCall(const char* func, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cout << "GL Error(Hex: "
            << std::hex
            << error
            << std::dec
            << ")\nError in File: "
            << file
            << "\nError in Line: "
            <<  line
            << "\nError in Function: "
            << func
            << "\n\n";
        return false;
    }
    return true;
}

bool GLLogCall(const char* func)
{
    while(GLenum error = glGetError())
    {
        std::cout << "GL Error(Hex: "
            << std::hex
            << error
            << std::dec
            << ")\nError in File: "
            << __FILE__
            << "\nError in Line: "
            <<  __LINE__
            << "\nError in Function: "
            << func
            << "\n\n";
        return false;
    }
    return true;
}

int GLCall2(int test, const char* file, int line) //std::function<unsigned int(unsigned int, const char[])> func
{
    GLClearError();
    ASSERT(GLLogCall(test, file, line));
    return test;
}