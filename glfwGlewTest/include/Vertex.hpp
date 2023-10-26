#pragma once
//only header file for now

#include "glm/glm.hpp"

namespace openglStuff {

    /* struct vec2
    {
        float x, y;
    };

    struct vec3
    {
        float x, y, z;
    }; */

    class Vertex
    {
    public:
        glm::vec3 Position;
        glm::vec3 Color;
        glm::vec2 Texture;
        //int TexIndex;

        Vertex(/* args */) {}
        ~Vertex() {}
    };

}