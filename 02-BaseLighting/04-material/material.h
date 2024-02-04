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

struct MaterialShape {
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
    float shininess;
};

struct MaterialLight {
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

    QOpenGLShaderProgram shader_Light;
    QOpenGLShaderProgram shader_Shape;

    // 镜头相关
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    // 光照相关
    QVector3D u_lightColor;
    QVector3D u_objectColor;

    QVector3D u_lightPos;
    QVector3D u_viewPos;

    MaterialShape u_object;
    MaterialLight u_light;

    void updateShapeShader();
    void updateLightShader();

    void showWindow();
    void updateDlg();
    void initSigSlot();
private:
    Ui::Material *ui;
};


#endif // MATERIAL_H
