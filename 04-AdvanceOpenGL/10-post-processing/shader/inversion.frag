#version 330 core

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

uniform Material material;

out vec4 FragColor;

in vec2 TexCoords;

in vec3 FragPos;


void main() {
    FragColor = vec4(vec3(1.0 - texture(material.texture_diffuse1, TexCoords)), 1.0);
}

