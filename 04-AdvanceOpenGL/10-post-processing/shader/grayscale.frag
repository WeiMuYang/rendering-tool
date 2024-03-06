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
    FragColor = texture(material.texture_diffuse1, TexCoords);
    float average = (FragColor.r + FragColor.g + FragColor.b) / 3.0;
    FragColor = vec4(average, average, average, 1.0);
}

