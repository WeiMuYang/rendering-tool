#ifndef DATA_TYPE_H
#define DATA_TYPE_H
#include <QString>

#define VERTICES_RECT_SIZE   12
#define INDICES_RECT_SIZE    6

// 顶点的数据：没有解析的数据是没有意义的
// 内存中的数据，关键是如何将内存中的数据给显卡
float verticesRect[VERTICES_RECT_SIZE] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};

unsigned int indicesRect[INDICES_RECT_SIZE] = {
    // 注意索引从0开始!
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};

// 顶点的数据：没有解析的数据是没有意义的
// 内存中的数据，关键是如何将内存中的数据给显卡
float verDataTri[9] = {
    // 所有的值是在[-1, 1]之间的
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};


// 后期可以改成根据路径，选择文件
QString vertexShaderSource =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
        "}\n\0";
// 后期可以改成根据路径，选择文件
QString fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";


enum Module {
    isTriangle = 0, isRectangle = 1
};


// 点模式 线框模式 填充模式
enum DrawMode {
    isPointMode = 0, isLineMode = 1, isFillMode = 2
};


#endif // DATA_TYPE_H
