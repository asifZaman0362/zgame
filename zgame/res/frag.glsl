#version 330 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 frag;

uniform sampler2D ourTexture;
uniform vec3 lightPos;
//uniform vec3 lightColor;

void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0f);
    //vec4(diffuse * vec3(1.0f, 0.5f, 0.5f), 1.0f);
    frag = texture(ourTexture, TexCoord);
    frag = frag * vec4(diffuse, 1.0f);
}
