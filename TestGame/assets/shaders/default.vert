#version 460 core

layout (location = 0) in vec3 aPos; 

uniform mat4 u_TMat;
uniform mat4 u_Cam;

out vec3 fColor;

void main()
{
    fColor = aPos;
    gl_Position = u_Cam * u_TMat* vec4(aPos, 1.0);
}