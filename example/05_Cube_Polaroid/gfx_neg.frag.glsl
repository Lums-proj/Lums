#version 150

in vec2 fragTex;
uniform sampler2D sampler;

out vec4 fragColor;

void main() {
	vec4 c = texture(sampler, fragTex);
	fragColor = vec4(1.0 - c.r, 1.0 - c.g, 1.0 - c.b, 1.0);
}
