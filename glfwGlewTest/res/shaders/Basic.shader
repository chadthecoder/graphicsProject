#shader vertex
#version 330 core
                               
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

uniform float u_gScale;
uniform float u_incLoc;

out vec2 v_texCoord;

uniform mat4 u_MVP; //model view projection matrix, by multiplying with position, it shows in 4:3

void main()
{
    v_texCoord = texCoord;
    gl_Position = u_MVP * vec4(u_gScale*position.x+u_incLoc, u_gScale*position.y, position.z, 1.0); // = position;
};

#shader fragment
#version 330 core
                                 
layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform vec2 u_mouse;
uniform vec2 u_resolution;
uniform sampler2D u_Texture;

in vec2 v_texCoord;

void main()
{
    vec2 mouseNormal = u_mouse.xy / u_resolution.xy;
    //vec2 uv = gl_FragCoord.xy / u_resolution.xy;

    vec4 texColor = texture(u_Texture, v_texCoord);

    color = vec4(mouseNormal.y, 0.0, mouseNormal.x, 1.0); //texColor; //vec4(mouseNormal.y, 0.0, mouseNormal.x, 1.0); //vec4(uv.x, 0.0, uv.y, 1.0); //u_Color; //vec4(0.6, 0.0, 0.6, 1.0); // purple
};