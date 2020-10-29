#version 330
layout (location=0) in vec4 a_Position;
layout (location=1) in vec2 a_TexCoords;

out vec2 v_TexCoords;

uniform mat4 u_MVP;

void main() {
    v_TexCoords = a_TexCoords;
    gl_Position = u_MVP * a_Position;
}
