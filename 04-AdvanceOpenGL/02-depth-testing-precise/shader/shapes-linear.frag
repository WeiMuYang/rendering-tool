#version 330 core

out vec4 FragColor;
float near = 0.1;
float far = 100.0;
// 将深度值反算成线性变化，效果同： float w = near*far/(near* 𝐹𝑑𝑒𝑝𝑡ℎ -far * 𝐹𝑑𝑒𝑝𝑡ℎ + far);
float LinearizeDepth(float depth) {
    float z_ndc = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z_ndc  * (far - near));
}

void main() {
//     FragColor = vec4(vec3(gl_FragCoord.z), 1.0);  // 直接将曲线变化的深度值赋值给颜色
    float depth = (LinearizeDepth(gl_FragCoord.z)-near) / (far-near); // divide by far for demonstration
    FragColor = vec4(vec3(depth), 1.0);
}
