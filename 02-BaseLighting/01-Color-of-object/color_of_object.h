#ifndef COLOROFOBJECT_H
#define COLOROFOBJECT_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QDoubleSpinBox>
#include <QVector3D>
#include <QVector>

#include "../vertices.h"

#include <QDialog>

namespace Ui {
class ColorOfObject;
}

class ColorOfObject : public QDialog
{
    Q_OBJECT

public:
    explicit ColorOfObject(QWidget *parent = nullptr);
    ~ColorOfObject();
    void initShader() ;

    void showWindow();
    // 镜头相关
    QVector3D lightPos;
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    Vertices box3D;
    QOpenGLShaderProgram shader_Light;
    QOpenGLShaderProgram shader_Shape;
    void updateShapeShader();
    void updateLightShader();

    QVector3D u_lightPos;
    QVector3D u_lightColor;
    QVector3D u_objectColor;

    void updateDlg();
    void initSigSlot();
private slots:


private:
    Ui::ColorOfObject *ui;
};





#endif // COLOROFOBJECT_H
