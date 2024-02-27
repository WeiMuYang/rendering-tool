#ifndef DISCARD_H
#define DISCARD_H

#include <QObject>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QOpenGLTexture>

#include "../mesh.h"

class Discard : public QObject
{
    Q_OBJECT
public:
    explicit Discard(QObject *parent = nullptr);

    std::vector<float> grassVertices;
    unsigned int grassVerCount;

    std::vector<Texture> cubeTextures;

    vector<QVector3D> vegetation;

    void initShader() ;
    void initTexture();

    QOpenGLShaderProgram shader_Shape;

    QOpenGLTexture* glassSpecular;


    // 镜头相关
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    unsigned int specularTexID;

    void updateDiscardShader();

};

#endif // DISCARD_H
