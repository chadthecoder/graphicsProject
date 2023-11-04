#shader vertex
#version 330 core
                               
//layout(location = 0) in vec2 aPos;
//layout(location = 1) in vec2 aTex;

layout(location = 0) in vec4 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTex;

uniform float u_gScale;
uniform float u_incLoc;

out vec3 v_color;
out vec2 v_texCoord;

uniform mat4 u_camMatrix;

void main()
{
    v_color = aColor;
    v_texCoord = aTex;

    gl_Position = u_camMatrix *  aPos;
};

#shader fragment
#version 330 core
                                 
layout(location = 0) out vec4 color;

uniform sampler2D u_Texture;

in vec3 v_color;
in vec2 v_texCoord;

void main()
{
    vec4 texColor = texture(u_Texture, v_texCoord);

    color = texColor; //vec4(v_color, 1.0f); //vec4(1.0, 1.0, 1.0, 1.0); //white color //cPartial; //cGradient; //cLine; //texColor; //vec4(mouseNormal.y, 0.0, mouseNormal.x, 1.0); //vec4(uv.x, 0.0, uv.y, 1.0); //u_Color; //vec4(0.6, 0.0, 0.6, 1.0); // purple
};