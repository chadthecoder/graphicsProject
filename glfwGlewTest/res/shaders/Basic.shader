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

uniform mat4 u_MVP; //model view projection matrix, by multiplying with position, it shows in 4:3
uniform mat4 u_model;
uniform mat4 u_camMatrix;

void main()
{
    v_color = aColor;
    v_texCoord = aTex;

    //vec4 tempPos =  u_MVP * position;
    //gl_Position = vec4(u_gScale*tempPos.x+u_incLoc, u_gScale*tempPos.y, tempPos.z, tempPos.w);
    //gl_Position = u_MVP * aPos;
    gl_Position = u_camMatrix * u_model * aPos;
};

#shader fragment
#version 330 core
                                 
layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform vec2 u_mouse;
uniform vec2 u_resolution;
uniform sampler2D u_Texture;

in vec3 v_color;
in vec2 v_texCoord;

void main()
{
    vec2 mouseNormal = u_mouse.xy / u_resolution.xy;
    //vec2 uv = gl_FragCoord.xy / u_resolution.xy;
    vec2 uv = v_texCoord.xy / u_resolution.xy;

    vec4 texColor = texture(u_Texture, v_texCoord);

    vec4 c1 = vec4(0.3, 0.0, 0.3, 1.0);
    vec4 c2 = vec4(1.0, 0.5, 0.5, 1.0);
    vec4 cGradient = mix(c1, c2, v_texCoord.x);
    vec4 cPartial = vec4(1.0, 1.0, 1.0, 1.0);
    if(v_texCoord.x < 0.5) cPartial.xyz = vec3(0.3, 0.0, 0.3);
    if(v_texCoord.x > 0.5) cPartial.xyz = vec3(1.0, 0.5, 0.5);
    float thickness = 0.1;
    vec4 cLine = vec4(1.0, 1.0, 1.0, 1.0);
    if(v_texCoord.x > 0.49 && v_texCoord.x < 0.51) cLine.xyz = vec3(0.0, 1.0, 0.0);
    if(v_texCoord.y > 0.49 && v_texCoord.y < 0.51) cLine.xyz = vec3(1.0, 0.0, 0.0);
    vec4 cFun = mix(cLine, u_Color, v_texCoord.x);

    color = texColor; //vec4(1.0, 1.0, 1.0, 1.0); //white color //cPartial; //cGradient; //cLine; //texColor; //vec4(mouseNormal.y, 0.0, mouseNormal.x, 1.0); //vec4(uv.x, 0.0, uv.y, 1.0); //u_Color; //vec4(0.6, 0.0, 0.6, 1.0); // purple
};