#version 150

in vec4 fColor;

out vec4 fragColor;

void main() {
    vec4 color = fColor;
    if (color.a < 0.5)
        discard;
	fragColor = color;
}
