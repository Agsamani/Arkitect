#version 460 core

out vec4 FragColor;

in vec4 o_Color;
in vec2 o_TexCoord;
in vec3 o_Pos;

uniform sampler2D u_Texture;

void main()
{   
    FragColor = o_Color * texture(u_Texture, o_TexCoord);
}