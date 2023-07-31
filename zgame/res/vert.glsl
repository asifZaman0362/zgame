#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
//layout (location = 2) in vec3 aNormal;

uniform mat4 transform;

//out vec3 ourColor;
out vec2 TexCoord;
//out vec3 Normal;
//out vec3 FragPos;

void main() {
    gl_Position = transform * vec4(aPos, 1.0f);
    //FragPos = vec3(transform * vec4(aPos, 1.0f));
    //ourColor = aColor;
    TexCoord = aTexCoord;
    //Normal = aNormal;
}
