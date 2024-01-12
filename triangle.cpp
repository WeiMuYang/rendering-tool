#include "modeling/triangle.h"
#include <QDebug>
namespace Modeling {
Triangle::Triangle(QObject *parent)
    : QObject{parent}
{
    // 顶点的数据：没有解析的数据是没有意义的
    // 内存中的数据，关键是如何将内存中的数据给显卡
    float ver_data[9] = {
        // 所有的值是在[-1, 1]之间的
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };





    verticesLength_ = 9;
    verticesArr_ = new float[9];
    std::memcpy(verticesArr_, ver_data, sizeof(float) * 9);
}

Triangle::~Triangle()
{
    delete[] verticesArr_;
}

};


