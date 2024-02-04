#ifndef GOURAUDLIGHT_H
#define GOURAUDLIGHT_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector>

#include "../vertices.h"

#include <QDialog>

namespace Ui {
class GouraudLight;
}

class GouraudLight : public QDialog
{
    Q_OBJECT

public:
    explicit GouraudLight(QWidget *parent = nullptr);
    ~GouraudLight();

    void initShader() ;
    void setShader(QString name, QVector3D value);

    Vertices box3D;
    QOpenGLShaderProgram shader_Light;
    QOpenGLShaderProgram shader_Shape;
    QVector3D lightPos;
    QVector3D lightColor;
    QVector3D objectColor;
    float ambientStrength;
    float specularStrength;

private:
    Ui::GouraudLight *ui;
};



#endif // GOURAUDLIGHT_H
