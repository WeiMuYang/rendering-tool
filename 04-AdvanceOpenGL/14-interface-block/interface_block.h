#ifndef INTERFACEBLOCK_H
#define INTERFACEBLOCK_H

#include <QObject>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include "../11-sky-box/sky_box.h"

class InterfaceBlock : public QObject
{
    Q_OBJECT
public:
    explicit InterfaceBlock(QObject *parent = nullptr);

    QOpenGLShaderProgram shader_InterfaceBlock; // 反射效果
    void initShader();

    QVector3D viewPos;

    // 镜头相关
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    unsigned int diffuseTexID;

    ModelShapeMaterial u_objectTex;
    ModelLightMaterial u_lightTex;

    // 光照相关
    QVector3D u_lightPos;
    QVector3D u_viewPos;

    void updateShader();

};

#endif // INTERFACEBLOCK_H
