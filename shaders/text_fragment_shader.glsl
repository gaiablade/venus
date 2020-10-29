#version 330
in vec2 v_TexCoords;
out vec4 color;

uniform sampler2D u_Texture;
//uniform vec3 color;

void main() {
    vec4 sampled = vec4(0, 0, 0, texture(u_Texture, v_TexCoords).r);
    color = sampled;
    //color = vec4(1, 0, 0, 1);
}
