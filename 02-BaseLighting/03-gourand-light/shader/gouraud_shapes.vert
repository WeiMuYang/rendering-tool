#version 330 core 
layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec3 aNormal;

out vec3 result;
uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection; 
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;

uniform float ambientStrength;
uniform float specularStrength;
uniform int shiny;

// 在顶点着色器中实现的冯氏光照模型，称为Gouraud着色，
// 这种优势是，相比片段来说，顶点要少得多，因此会更高效.
// 但是看起来会很奇怪
void main() { 
    vec3 Normal = mat3(transpose(inverse(model))) * aNormal;
    vec3 FragPos = vec3(model * vec4(aPos,1.0));

    // ambient
    vec3 ambient = ambientStrength * lightColor;
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shiny);
    vec3 specular = specularStrength * spec * lightColor;

    result = (ambient+diffuse+specular) * objectColor;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
} 
