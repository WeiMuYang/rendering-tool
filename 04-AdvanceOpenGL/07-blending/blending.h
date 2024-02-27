#ifndef BLENDING_H
#define BLENDING_H

#include <QDialog>

#include <QObject>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QOpenGLTexture>

#include "../mesh.h"
#include "../data_type.h"

namespace Ui {
class Blending;
}

class Blending : public QDialog
{
    Q_OBJECT

public:
    explicit Blending(QWidget *parent = nullptr);
    ~Blending();

    std::vector<Texture> cubeTextures;

    void initShader() ;
    void initTexture();

    QOpenGLShaderProgram shader_Shape;

    QOpenGLTexture* blendingSpecular;

    BlendingType srcBlending;
    BlendingType desBlending;

    // 镜头相关
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    unsigned int specularTexID;

    void updateBlendingShader();

    void showWindow();
    void updateDlg();
public slots:
    void initSigSlot();
private:
    Ui::Blending *ui;
};

#endif // BLENDING_H
