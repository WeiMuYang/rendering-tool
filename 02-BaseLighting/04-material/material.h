#ifndef MATERIAL_H
#define MATERIAL_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QMatrix4x4>

#include <QDialog>

namespace Ui {
class Material;
}

//#include "../vertices.h"

struct MaterialShapeShader {
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
    float shininess;
};

struct MaterialLightShader {
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
};


class Material : public QDialog
{
    Q_OBJECT

public:
    explicit Material(QWidget *parent = nullptr);
    ~Material();
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
    MaterialShapeShader objectMaterial;
    MaterialLightShader light;

    void updateShapeShader();
    void updateLightShader();

private:
    Ui::Material *ui;
};


#endif // MATERIAL_H
