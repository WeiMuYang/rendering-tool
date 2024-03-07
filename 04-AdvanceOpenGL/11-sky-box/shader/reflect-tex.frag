#version 330 core
#extension GL_NV_shadow_samplers_cube : enable
struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_reflection1;
    float shininess;
};

struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;


uniform Material material;
uniform vec3 viewPos;
uniform samplerCube skybox;

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;



void main() {
    vec3 diffuseTexColor=vec3(texture2D(material.texture_diffuse1,TexCoords));
    vec3 specularTexColor=vec3(texture2D(material.texture_specular1,TexCoords));
    vec3 reflectionTexColor=vec3(texture2D(material.texture_reflection1,TexCoords));

    // ambient
    vec3 ambient = diffuseTexColor*light.ambient;
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff *diffuseTexColor*light.diffuse;
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular =  spec*specularTexColor*light.specular;

    //reflection
    vec3 I = normalize(FragPos - viewPos);
    vec3 R = reflect(I, normalize(Normal));
    vec3 reflectionSkyBox = textureCube(skybox, R).rgb;
    vec3 reflection=reflectionTexColor*reflectionSkyBox;

    vec3 result = (ambient + diffuse + specular + reflection);
    FragColor = vec4(result, 1.0);
}
