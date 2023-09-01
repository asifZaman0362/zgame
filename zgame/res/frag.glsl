#version 330 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 frag;

uniform vec3 lightPos;
uniform vec3 ambientLight;
uniform vec3 lightColor;
uniform vec3 cameraPosition;
uniform float metallic;
uniform float smoothness;

struct Material {
    uniform sampler2D albedo;
    uniform sampler2D specularMap;
    uniform sampler2D normalMap;
    uniform sampler2D smoothness;
    uniform vec3 specular;
};

uniform Material mat;


#define SPEC_STRENGTH 0.5f

void main() {
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diffuse_amount = max(dot(norm, lightDir), 0.0);
    float base_color = vec3(texture(ourTexture, TexCoord));
    float diffuse = lightColor * (diffuse_amount * base_color);

    // specular
    vec3 view_dir = normalize(cameraPosition - FragPos);
    vec3 reflection = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflection), 0.0), smoothness);
    vec3 specular = lightColor * (spec * specularColor);

    // result
    frag = vec4(ambient + diffuse + specular, 1.0f);
}
