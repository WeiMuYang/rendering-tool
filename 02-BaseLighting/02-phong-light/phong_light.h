#ifndef PHONGLIGHT_H
#define PHONGLIGHT_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector>

#include "../vertices.h"

class PhongLight : public QObject
{
    Q_OBJECT
public:
    explicit PhongLight(QObject *parent = nullptr);
    void initShader() ;
    void setShader(QString name, QVector3D value);

private:

public:
    Vertices box3D;
    QOpenGLShaderProgram shader_Light;
    QOpenGLShaderProgram shader_Shape;
    QVector3D lightPos;
    QVector3D lightColor;
    QVector3D objectColor;
    float ambientStrength;
    float specularStrength;
};

#endif // PHONGLIGHT_H
