#version 460 core

out vec4 FragColor;

void main()
{
    vec3 viewCoord = vec3((gl_FragCoord.xy / 1050) * 2.0 - vec2(1680.0/1050.0,1.0), 5.0) / 2.5;
    FragColor = vec4(viewCoord, 1.0);
} 