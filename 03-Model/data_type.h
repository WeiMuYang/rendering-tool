#ifndef DATA_TYPE_H
#define DATA_TYPE_H
#include <QString>

enum Scene {
    Box3D, LoadModel
};

// 点模式 线框模式 填充模式
enum DrawMode {
    isPointMode = 0, isLineMode = 1, isFillMode = 2
};

enum TexWrap {
    REPEAT, MIRRORED_REPEAT, CLAMP_TO_BORDER, CLAMP_TO_EDGE
};

enum TexFilter {
    NEAREST,  LINEAR, NEAREST_MIPMAP_NEAREST, LINEAR_MIPMAP_NEAREST , NEAREST_MIPMAP_LINEAR , LINEAR_MIPMAP_LINEAR
};


#endif // DATA_TYPE_H
