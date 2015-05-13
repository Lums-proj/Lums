#version 150

in vec2 pos;
in vec2 texcoord;
in vec4 color;

uniform mat4 proj;

out vec2 fTexCoord;
out vec4 fColor;

void main() {
	gl_Position = proj * vec4(pos, 0.0, 1.0);
	fTexCoord = texcoord;
	fColor = color;
}
