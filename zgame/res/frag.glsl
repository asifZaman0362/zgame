#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

struct Material {
    sampler2D diffuseMap;
    sampler2D normalMap;
    sampler2D roughnessMap;
    sampler2D metallicMap;
};

uniform Material mat;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{           
     // obtain normal from normal map in range [0,1]
    vec3 normal = texture(mat.normalMap, fs_in.TexCoords).rgb;
    // transform normal vector to range [-1,1]
    normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space
   
    // get diffuse color
    vec3 color = texture(mat.diffuseMap, fs_in.TexCoords).rgb;
    // ambient
    vec3 ambient = 0.1 * color;
    // diffuse
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 metallic = texture(mat.metallicMap, fs_in.TexCoords).rgb;
    vec3 metallicDiffuse = vec3(1) - metallic;
    vec3 diffuse = diff * color * (metallicDiffuse + vec3(0.2));
    // specular
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float roughness = texture(mat.roughnessMap, fs_in.TexCoords).r;
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32 + 128 * roughness) * metallic.r * (1 - roughness);

    vec3 specular = vec3(1) * spec;
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
