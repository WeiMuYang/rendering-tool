#version 330 core


#define NR_LIGHTS 2

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct SPotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform SPotLight spotLights[NR_LIGHTS];

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLights;

struct PointLight {
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform PointLight pointLights[NR_LIGHTS];

uniform Material material;
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;

vec3 diffuseTexColor=vec3(texture(material.diffuse,TexCoords));
vec3 specularTexColor=vec3(texture(material.specular,TexCoords));

vec3 CalcSpotLight(SPotLight light, vec3 normal, vec3 viewDir);
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result=vec3(0);
    for(int i = 0;i < NR_LIGHTS; i++) {
        result += CalcSpotLight(spotLights[i],norm,viewDir); // 聚光灯
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);  // 点光源
    }
    result += CalcDirLight(dirLights,norm,viewDir);   // 平行光
    FragColor = vec4(result, 1.0);
}

vec3 CalcSpotLight(SPotLight light, vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(light.position-FragPos);
    // ambient
    vec3 ambient = diffuseTexColor*light.ambient;
    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff *diffuseTexColor*light.diffuse;
    // specular

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular =  spec*specularTexColor*light.specular;

    //attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                               light.quadratic * (distance * distance));
    //ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    //smooth
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    diffuse *= intensity;
    specular *= intensity;

    return (ambient + diffuse + specular);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * diffuseTexColor;
    vec3 diffuse = light.diffuse * diff * diffuseTexColor;
    vec3 specular = light.specular * spec * specularTexColor;
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 	1.0/(light.constant+light.linear*distance+light.quadratic*(distance*distance));
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
