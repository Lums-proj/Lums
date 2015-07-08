#version 150

in vec2 fTexCoord;
in vec4 fColor;

uniform sampler2D sampler;

out vec4 fragColor;

void main() {
    vec4 color = texture(sampler, fTexCoord) * fColor;
    if (color.a < 0.5)
        discard;
	fragColor = color;
}
