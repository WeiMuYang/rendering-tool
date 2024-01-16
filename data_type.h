#ifndef DATA_TYPE_H
#define DATA_TYPE_H
#include <QString>

#define VERTICES_RECT_SIZE   12
#define INDICES_RECT_SIZE    6


enum Module {
    isTriangle = 0, isRectanglePos = 1, isRectanglePosCol = 2
};


// 点模式 线框模式 填充模式
enum DrawMode {
    isPointMode = 0, isLineMode = 1, isFillMode = 2
};

enum ShaderProgram {
    Base, BaseWithUniform, BaseWithAColor
};


#endif // DATA_TYPE_H
