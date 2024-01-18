#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
// 获取纹理坐标，进行纹理采样
layout(location = 2) in vec2 aTexCord;
out vec3 ourColor;
out vec2 TexCord;
void main(){
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    ourColor = aColor;
    TexCord = aTexCord;
}
