#ifndef MOUSE_PICKING_H
#define MOUSE_PICKING_H

#include <QDialog>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include "../01-depth-testing/depth_testing.h"

namespace Ui {
class MousePicking;
}

struct PickingPixelData {
    QVector2D MousePressPos; // 点击屏幕的位置
    float PixelZ;  // 像素深度值
    float PixelW;  // 相机到点击位置 W
    QVector4D ClipPos;  // 裁剪坐标
    QVector4D WorldPos;  // 裁剪坐标
};

class MousePicking : public QDialog
{
    Q_OBJECT

public:
    explicit MousePicking(QWidget *parent = nullptr);
    ~MousePicking();
    void initShader() ;
    void initTexture() ;
    void setShader(QString name, QVector3D value);

    QOpenGLShaderProgram shader_Shape;

    QOpenGLTexture* texConrainerDiffuse;
    QOpenGLTexture* texConrainerSpecular;

    // 光线的颜色
    QVector3D u_lightColor;

    // 镜头相关
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    // 光照相关
    QVector3D u_lightPos;
    QVector3D u_viewPos;
    Box3DShapeMaterial u_objectTex;
    Box3DLightMaterial u_lightTex;

    void updateShapeShader();
    void updateLightShader();

    void showWindow();
    void updateDlg();

    PickingPixelData pickingPixelData;
private:
    Ui::MousePicking *ui;
};

#endif // MOUSE_PICKING_H
