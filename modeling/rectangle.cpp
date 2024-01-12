#include "rectangle.h"
#define VERTICES_SIZE   12
#define INDICES_SIZE    6
namespace Modeling {

Rectangle::Rectangle(QObject *parent)
    : QObject{parent}
{
    // 顶点的数据：没有解析的数据是没有意义的
    // 内存中的数据，关键是如何将内存中的数据给显卡
    float vertices[VERTICES_SIZE] = {
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
    };

    unsigned int indices[INDICES_SIZE] = {
        // 注意索引从0开始!
        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
        // 这样可以由下标代表顶点组合成矩形
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    verticesLength_ = VERTICES_SIZE;
    verticesArr_ = new float[VERTICES_SIZE];
    std::memcpy(verticesArr_, vertices, sizeof(float) * VERTICES_SIZE);

    indicesLength_ = INDICES_SIZE;
    indices_ = new int[INDICES_SIZE];
    std::memcpy(indices_, indices, sizeof(int) * INDICES_SIZE);
}

Rectangle::~Rectangle()
{
    delete[] verticesArr_;
    delete[] indices_;
}

}
