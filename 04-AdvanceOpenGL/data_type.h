#ifndef DATA_TYPE_H
#define DATA_TYPE_H
#include <QString>

enum Scene {
    DepthTestingScene, DepthTestingPreciseScene, MousePickingScene, ModelsControlScene,
    StencilOutLineScene, DisCardScene, BlendingScene, FaceCullingScene, FrameBufferScene,
    PostProcessingScene, SkyBoxScene, AdvancedDataScene, GLSLVariableScene, InterfaceBlockScene
};

enum BlendingType{
    ZERO = 0, ONE = 1, SRC_COLOR = 0x0300, ONE_MINUS_SRC_COLOR = 0x0301, SRC_ALPHA = 0x0302,
    ONE_MINUS_SRC_ALPHA = 0x0303, DST_ALPHA = 0x0304, ONE_MINUS_DST_ALPHA = 0x0305
};

enum FaceCullingType{
    FaceCullingFRONT = 0x0404, FaceCullingBACK = 0x0405, FaceCullingLEFT = 0x0406, FaceCullingRIGHT = 0x0407, FRONT_AND_BACK = 0x0408
};

enum FaceCullingOri{
    ClockWise = 0x0900, antiClockwise = 0x0901
};

enum DepthTestType{
    None, NEVER, LESS, EQUAL, LEQUAL, GREATER, NOTEQUAL, GEQUAL, ALWAYS
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
