#version 150

in vec3 pos;
in vec2 tex;
in vec4 color;

uniform mat4 proj;
uniform mat4 view;

out vec4 fColor;
out vec2 fTexture;

void main() {
    gl_Position = proj * view * vec4(pos, 1.0);
    fTexture = tex;
    fColor = color;
}
