#ifndef PHONGLIGHT_H
#define PHONGLIGHT_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector>
#include <QMatrix4x4>

#include "../vertices.h"

#include <QDialog>

namespace Ui {
class PhongLight;
}

class PhongLight : public QDialog
{
    Q_OBJECT

public:
    explicit PhongLight(QWidget *parent = nullptr);
    ~PhongLight();
    void initShader() ;
    void updateDlg();
    void initSigSlot();
    void updateShapeShader();
    void updateLightShader();

    Vertices box3D;
    QOpenGLShaderProgram shader_Light;
    QOpenGLShaderProgram shader_Shape;

    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;
    QVector3D u_lightPos;
    QVector3D u_viewPos;

    QVector3D u_lightColor;
    QVector3D u_objectColor;
    float u_ambientStrength;
    float u_specularStrength;
    int u_shiny; // 2 4 8 16 32 64 128

    void showWindow();
private:
    Ui::PhongLight *ui;
};


#endif // PHONGLIGHT_H
