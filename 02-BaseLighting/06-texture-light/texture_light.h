#ifndef TEXTURELIGHT_H
#define TEXTURELIGHT_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QMatrix4x4>

struct CyanPlasticShapeMaterial {
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
    float shininess;
};

struct CyanPlasticLight {
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
};

class TexTureLight : public QObject
{
    Q_OBJECT
public:
    explicit TexTureLight(QObject *parent = nullptr);

    void initShader() ;
    void setShader(QString name, QVector3D value);

    QOpenGLShaderProgram shader_Light;
    QOpenGLShaderProgram shader_Shape;

    // 镜头相关
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    // 光照相关
    QVector3D lightPos;
    QVector3D viewPos;
    QVector3D lightColor;
    QVector3D objectColor;
    CyanPlasticShapeMaterial objectMaterial;
    CyanPlasticLight light;

    void updateShapeShader();
    void updateLightShader();

};

#endif // TEXTURELIGHT_H
