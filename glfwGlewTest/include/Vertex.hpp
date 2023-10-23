#pragma once
//only header file for now

#include "glm/glm.hpp"

class Vertex
{
private:
    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec2 Texture;
    //int TexIndex;
public:
    Vertex(/* args */) {}
    ~Vertex() {}
};