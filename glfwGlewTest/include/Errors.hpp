//maybe make later?

#pragma once

#include <GL/glew.h>
#include <iostream>
#include <csignal>

#define ASSERT(x){ if(!x)\
raise(SIGTRAP); } //__builtin_debugtrap(); //instead of raise(SIGTRAP) for windows

void GLClearError();

bool GLLogCall(int test, const char* file, int line);

bool GLLogCall(const char* func, const char* file, int line);

bool GLLogCall(const char* func);

#define GLCall(x,y, z) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, y, z));


int GLCall2(int test, const char* file, int line); //std::function<unsigned int(unsigned int, const char[])> func