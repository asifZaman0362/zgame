#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 MVP;
//uniform mat4 view; // view matrix is projection * camera because it is the same for all objects in the scene
                    // or atleast for every object being rendered by the same camera in the scene

//out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;
//out vec3 FragPos;

void main() {
    vec4 model_space_position = MVP * vec4(aPos, 1.0f);
    gl_Position = model_space_position;
    //FragPos = vec3(model_space_position);
    //ourColor = aColor;
    TexCoord = aTexCoord;
    Normal = aNormal;
}
