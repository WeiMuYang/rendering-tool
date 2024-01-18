#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCord;
// sampler2D 指的是采样器
uniform sampler2D textureWall;
uniform sampler2D textureSmile;
void main(){
    // mix(tex0, tex1, 0.5) 纹理混合
    // texture(textureSmile,TexCord);  // 纹理textureSmile根据TexCord坐标采样
    FragColor = mix(texture(textureWall,TexCord),
            texture(textureSmile,TexCord),0.5);
}
