#ifndef MATERIAL_H
#define MATERIAL_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QMatrix4x4>

//#include "../vertices.h"

struct MaterialShader {
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
    float shininess;
};

struct LightShader {
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
};

class Material : public QObject
{
    Q_OBJECT
public:
    explicit Material(QObject *parent = nullptr);

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
    MaterialShader material;
    LightShader light;

    void updateShapeShader();
    void updateLightShader();
};

#endif // MATERIAL_H
