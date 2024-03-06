#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <QDialog>

#include <QObject>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <QOpenGLFunctions_3_3_Core>

#include "../mesh.h"

namespace Ui {
class FrameBuffer;
}

class FrameBuffer : public QDialog
{
    Q_OBJECT

public:
    explicit FrameBuffer(QWidget *parent = nullptr);
    ~FrameBuffer();

    std::vector<float> frameBufferVertices;
    unsigned int frameBufferVerCount;

    std::vector<Texture> FrameBufferTex;

    void initShader() ;
    void initFrameBufferTex(QOpenGLFunctions_3_3_Core *openGLFun, int width, int height);
    unsigned int fbo;
    unsigned int rbo;
    unsigned int texture; // 帧缓冲纹理
    bool isFrameBuffer{true};

    QOpenGLShaderProgram shader_Shape;

    QOpenGLTexture* glassSpecular;

    // 镜头相关
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    unsigned int diffuseTexID;

    void updateFrameBufferShader();


    void showWindow();
    void updateDlg();
    void initSigSlot();

private:
    Ui::FrameBuffer *ui;
    // 获取初始后的OpenGL函数指针
    QOpenGLFunctions_3_3_Core *m_glFuns;
};

#endif // FRAME_BUFFER_H
