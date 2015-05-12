#version 150

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec3 pos;
in vec4 color;

out vec4 vertColor;

void main() {
	vertColor = color;
	gl_Position = model * view * projection * vec4(pos, 1.0);
}

