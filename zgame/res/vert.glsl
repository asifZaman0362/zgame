#version 330 core

layout (location = 0) in vec3 vert;
//layout (location = 1) in vec2 aTexCoord;

uniform mat4 other;
uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(vert, 1.0f);
}
