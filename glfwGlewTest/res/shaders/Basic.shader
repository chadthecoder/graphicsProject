#shader vertex
#version 330 core
                               
layout(location = 0) in vec4 position;
uniform float gScale;
uniform float incLoc;
                               
void main()
{
    gl_Position = vec4(gScale*position.x+incLoc, gScale*position.y, position.z, 1.0); // = position;
};

#shader fragment
#version 330 core
                                 
layout(location = 0) out vec4 color;
uniform vec4 u_Color;
uniform float u_Green;
                                 
void main()
{
    color = u_Color; //vec4(0.6, 0.0, 0.6, 1.0); // purple
};