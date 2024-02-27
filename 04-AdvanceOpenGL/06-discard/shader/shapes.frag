#version 330 core

out vec4 FragColor;

uniform sampler2D texture_diffuse1;

in vec2 TexCoords;

void main() {
    vec4 texColor = texture(texture_diffuse1, TexCoords);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
}
