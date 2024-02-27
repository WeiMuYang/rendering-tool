#version 330 core

uniform sampler2D texture_specular1;
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;


void main() {
   FragColor = texture(texture_specular1 ,TexCoords);
}
