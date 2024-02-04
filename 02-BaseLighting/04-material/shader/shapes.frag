#version 330 core
in vec3 Normal;
in vec3 FragPos;

// 材质信息参数
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
// 材质光照参数
struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform Material objectMaterial;
uniform vec3 objectColor;
uniform vec3 lightColor;
// 观察的位置
uniform vec3 viewPos;
// 光源的位置
uniform vec3 lightPos;

out vec4 FragColor;

void main() {
    // color  0 1 1
    vec3 color = objectColor * lightColor;
    // ambient
    vec3 ambient = color * objectMaterial.ambient * light.ambient;
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = color * diff * objectMaterial.diffuse * light.diffuse;
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), objectMaterial.shininess);
    vec3 specular = color * spec * objectMaterial.specular * light.specular;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
