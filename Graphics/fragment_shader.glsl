#version 330

out vec4 color;
in vec3 o_Color;

void main() {
    color = vec4(o_Color, 1.0);
}
