#version 460 core

layout (location = 0) in vec2 aPos; 
layout (location = 1) in vec4 aColor; 
layout (location = 2) in vec2 aTexCoord;

uniform mat4 u_Camera;

out vec4 o_Color;
out vec2 o_TexCoord;

void main()
{
    o_Color = aColor;
    o_TexCoord = aTexCoord;
    gl_Position = u_Camera * vec4(aPos, 1.0, 1.0);
}