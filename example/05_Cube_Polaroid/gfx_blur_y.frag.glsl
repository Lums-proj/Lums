#version 150

in vec2 fragTex;
uniform sampler2D sampler;

out vec4 fragColor;

void main() {
	float th = 1.0 / 600.0;

	vec4 fc;

	fc = texture(sampler, vec2(fragTex.x, fragTex.y - 5 * th));
	fc += texture(sampler, vec2(fragTex.x, fragTex.y - 4 * th));
	fc += texture(sampler, vec2(fragTex.x, fragTex.y - 3 * th));
	fc += texture(sampler, vec2(fragTex.x, fragTex.y - 2 * th));
	fc += texture(sampler, vec2(fragTex.x, fragTex.y - 1 * th));
	fc += texture(sampler, vec2(fragTex.x, fragTex.y * th));
	fc += texture(sampler, vec2(fragTex.x, fragTex.y + 1 * th));
	fc += texture(sampler, vec2(fragTex.x, fragTex.y + 2 * th));
	fc += texture(sampler, vec2(fragTex.x, fragTex.y + 3 * th));
	fc += texture(sampler, vec2(fragTex.x, fragTex.y + 4 * th));
	fc += texture(sampler, vec2(fragTex.x, fragTex.y + 5 * th));

	fragColor = fc / 11.0;
}
