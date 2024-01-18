#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCord;
uniform sampler2D textureWall;
uniform sampler2D textureSmile;
uniform sampler2D textureSmall;
void main(){
    FragColor = texture(textureSmall,TexCord);
}
