#version 330
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;

uniform mat4 MVP;
out vec3 o_Color;

void main() {
    o_Color = color;
    vec4 multiplied = MVP * position;
    gl_Position = multiplied;
}
