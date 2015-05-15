#version 150

in vec2 fTexCoord;
in vec4 fColor;

uniform sampler2D sampler;

out vec4 fragColor;

void main() {
	//float y = dot(vec3(0.2126, 0.7152, 0.0722), texture(sampler, fTexCoord).rgb * fColor.rgb);
	//fragColor = vec4(y, y, y, 1);
	fragColor = texture(sampler, fTexCoord) * fColor;
}
