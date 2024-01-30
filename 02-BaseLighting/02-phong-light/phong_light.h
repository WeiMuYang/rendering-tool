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

    Vertices box3D;
    QOpenGLShaderProgram shader_Light;
    QOpenGLShaderProgram shader_Shape;
    QVector3D lightPos;
    QVector3D lightColor;
    QVector3D objectColor;
    float ambientStrength;
    float specularStrength;
    int shiny; // 2 4 8 16 32 64 128
};

#endif // PHONGLIGHT_H
