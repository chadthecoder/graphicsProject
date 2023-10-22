#pragma once

#include "glm/glm.hpp"

class Object
{
private:
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Color;
        glm::vec2 Texture;
        //int TexIndex;
    };
    
public:
    Object(/* args */);
    ~Object();
};
