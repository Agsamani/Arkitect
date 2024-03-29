#version 460 core

layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec4 aColor; 
layout (location = 2) in vec2 aTexCoord;

uniform mat4 u_Camera;

out vec4 o_Color;
out vec2 o_TexCoord;
out vec3 o_Pos;

void main()
{
    o_Color = aColor;
    o_TexCoord = aTexCoord;
    o_Pos = aPos;
    gl_Position = u_Camera * vec4(aPos, 1.0);
}