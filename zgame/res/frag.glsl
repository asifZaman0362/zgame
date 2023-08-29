#version 330 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 frag;

uniform sampler2D ourTexture;
uniform vec3 lightPos;
uniform vec3 ambientLight;
uniform vec3 lightColor;
uniform vec3 diffuseColor;
uniform vec3 cameraPosition;

#define SPEC_STRENGTH 0.5f

void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor + ambientLight;
    vec4 textureSample = texture(ourTexture, TexCoord); //* vec4(diffuseColor, 1.0f);
    vec3 viewDir = normalize(cameraPosition - FragPos);
    vec3 reflection = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflection), 0.0), 32);
    vec3 specular = SPEC_STRENGTH * spec * lightColor;
    frag = textureSample * vec4(diffuse + specular, 1.0f);
}
