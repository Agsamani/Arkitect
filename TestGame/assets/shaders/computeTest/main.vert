#version 460 core

layout (location = 0) in vec2 aPos; 
layout (location = 1) in vec2 texCoord; 

uniform mat4 u_Cam;

out vec2 fTexCoord;

void main()
{
    fTexCoord = texCoord;
    gl_Position = u_Cam * vec4(aPos, 0.0, 1.0);
}