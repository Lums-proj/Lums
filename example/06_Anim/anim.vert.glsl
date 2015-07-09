#version 150

in vec3 pos;
in vec4 color;

uniform mat4 proj;
uniform mat4 view;

out vec4 fColor;

void main() {
	gl_Position = proj * view * vec4(pos, 1.0);
	fColor = color;
}
