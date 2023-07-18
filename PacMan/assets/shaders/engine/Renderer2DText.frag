#version 450 core

layout (location = 0) out vec4 FragColor;
layout (binding = 0) uniform sampler2D u_FontAtlas;

in vec4 o_Color;
in vec2 o_TexCoord;

float screenPxRange() {
	const float pxRange = 2.0; // set to distance field's pixel range
    vec2 unitRange = vec2(pxRange)/vec2(textureSize(u_FontAtlas, 0));
    vec2 screenTexSize = vec2(1.0)/fwidth(o_TexCoord);
    return max(0.5*dot(unitRange, screenTexSize), 1.0);
}

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

void main()
{
	vec4 texColor = o_Color * texture(u_FontAtlas, o_TexCoord);

	vec3 msd = texture(u_FontAtlas, o_TexCoord).rgb;
    float sd = median(msd.r, msd.g, msd.b);
    float screenPxDistance = screenPxRange()*(sd - 0.5);
    float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);
	if (opacity == 0.0)
		discard;

	vec4 bgColor = vec4(0.0);
    FragColor = mix(bgColor, o_Color, opacity);
	if (FragColor.a == 0.0)
		discard;
}