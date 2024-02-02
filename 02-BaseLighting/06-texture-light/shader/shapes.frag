#version 330 core
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

struct Material {
    // ambient和diffuse一样
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;  // 自发光
    float shininess;
};

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;
uniform Material material;

uniform vec3 viewPos;
uniform vec3 lightPos;
out vec4 FragColor;

void main() {
    vec3 diffuseTexColor = vec3(texture(material.diffuse, TexCoords));
    vec3 specularTexColor = vec3(texture(material.specular, TexCoords));

    // ambient
    vec3 ambient = diffuseTexColor * light.ambient;
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseTexColor * light.diffuse;
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular =  spec*specularTexColor*light.specular;

    // emission
    vec3 emissionTexColor = texture(material.emission,TexCoords).rgb; // 和diffuseTexColor求法一样

    vec3 result = ambient + diffuse + specular + emissionTexColor;
    FragColor = vec4(result, 1.0);
}
