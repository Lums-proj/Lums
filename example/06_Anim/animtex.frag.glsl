#version 150

in vec4 fColor;
in vec2 fTexture;

uniform sampler2D sampler;

out vec4 fragColor;

void main() {
    vec4 color = texture(sampler, fTexture) * fColor;
    if (color.a < 0.5)
        discard;
    fragColor = color;
}
