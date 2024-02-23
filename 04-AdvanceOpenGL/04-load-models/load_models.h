#ifndef LOADMODELS_H
#define LOADMODELS_H

#include <QObject>
#include <QOpenGLTexture>
#include "../01-depth-testing/depth_testing.h"

class LoadModels : public QObject
{
    Q_OBJECT
public:
    explicit LoadModels(QObject *parent = nullptr);

    void initShader();

    QOpenGLShaderProgram shader_Shape;

    Texture texPlane;

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

    void initTexture();
};

#endif // LOADMODELS_H
