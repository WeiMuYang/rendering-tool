#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform Light light;


uniform Material material;
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;

void main() {
    vec3 diffuseTexColor=vec3(texture(material.diffuse,TexCoords));
    vec3 specularTexColor=vec3(texture(material.specular,TexCoords));

    vec3 lightDir=normalize(FragPos-light.position);
    float theta = dot(lightDir, normalize(light.direction));
    // theta = cosθ的值 在0-90度是递减，因此只要大于light.cutOff就能有光照效果
    if(theta > light.cutOff) {
        // ambient
        vec3 ambient = diffuseTexColor*light.ambient;
        // diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(light.position-FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff *diffuseTexColor*light.diffuse;
        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular =  spec*specularTexColor*light.specular;

        //attenuation
        float distance = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance +
                                  light.quadratic * (distance * distance));
        //ambient *= attenuation; // 不考虑环境光衰减
        diffuse *= attenuation;
        specular *= attenuation;

        vec3 result = (ambient + diffuse + specular);
        FragColor = vec4(result, 1.0);
    }else
        // 只有环境光
        FragColor = vec4(light.ambient * diffuseTexColor, 1.0);

}
