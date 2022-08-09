#version 460 core

layout (location = 0) in vec2 aPos; 
layout (location = 1) in vec2 aTexCoord; 

out vec2 fTexCoord;

void main()
{
    fTexCoord = aTexCoord;
    gl_Position = vec4(aPos / 2.0, 0.0, 1.0);
}