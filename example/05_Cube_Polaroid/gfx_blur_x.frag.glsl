#version 150

in vec2 fragTex;
uniform sampler2D sampler;

out vec4 fragColor;

void main() {
	float tw = 1.0 / 800.0;

	vec4 fc;

	fc = texture(sampler, vec2(fragTex.x - 5 * tw, fragTex.y));
	fc += texture(sampler, vec2(fragTex.x - 4 * tw, fragTex.y));
	fc += texture(sampler, vec2(fragTex.x - 3 * tw, fragTex.y));
	fc += texture(sampler, vec2(fragTex.x - 2 * tw, fragTex.y));
	fc += texture(sampler, vec2(fragTex.x - 1 * tw, fragTex.y));
	fc += texture(sampler, vec2(fragTex.x * tw, fragTex.y));
	fc += texture(sampler, vec2(fragTex.x + 1 * tw, fragTex.y));
	fc += texture(sampler, vec2(fragTex.x + 2 * tw, fragTex.y));
	fc += texture(sampler, vec2(fragTex.x + 3 * tw, fragTex.y));
	fc += texture(sampler, vec2(fragTex.x + 4 * tw, fragTex.y));
	fc += texture(sampler, vec2(fragTex.x + 5 * tw, fragTex.y));

	fragColor = fc / 11.0;
}
