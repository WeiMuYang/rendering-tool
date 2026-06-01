#version 330 core 
layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection; 
void main() { 
    // 法线信息转成换成世界坐标，同时需要排除宽和高不等比例缩放的影响： model先求逆，再转置
    // 法线矩阵： mat3(transpose(inverse(model)))
    Normal = mat3(transpose(inverse(model))) * aNormal;
    // 模型顶点 转化成 世界坐标
    FragPos=vec3(model * vec4(aPos,1.0));
    gl_Position = projection * view * model * vec4(aPos, 1.0);
} 
