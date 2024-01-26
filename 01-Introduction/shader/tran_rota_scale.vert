#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCord;
out vec3 ourColor;
out vec2 TexCord;
uniform mat4 theMatrix;
void main(){
    gl_Position = theMatrix*vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    ourColor=aColor;
    TexCord=vec2(1-aTexCord.s,aTexCord.t);
}
