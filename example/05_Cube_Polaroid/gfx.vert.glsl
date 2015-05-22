#version 150

in vec2 vPos;
in vec2 tPos;

out vec2 fragTex;

void main() {
	gl_Position = vec4(vPos, 0.0, 1.0);
	fragTex = tPos;
}
