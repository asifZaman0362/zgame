#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform vec3 lightPos;
//uniform mat4 MVP;
//uniform mat4 view; // view matrix is projection * camera because it is the same for all objects in the scene
                    // or atleast for every object being rendered by the same camera in the scene

//out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;

void main() {
    TexCoord = aTexCoord;
    FragPos = vec3(model * vec4(aPos, 1.0f));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    //LightPos = view * lightPos;
    gl_Position = projection * view * vec4(FragPos, 1.0f);
}
