#version 330 core
layout(location = 0) in vec3 aPos;
out vec4 u_Color;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    u_Color = vec4(0.8f, 0.1f, 0.1f, 1.0f);
}
