#ifndef AXIS_H
#define AXIS_H

#include <QObject>
#include <QOpenGLShaderProgram>

#include "../vertices.h"

class Axis : public QObject
{
    Q_OBJECT
public:
    explicit Axis(QObject *parent = nullptr);

    void initShader();
signals:

public:
    // 坐标系
    Vertices axisX_;
    QOpenGLShaderProgram shader_axisX;

    Vertices axisY_;
    QOpenGLShaderProgram shader_axisY;

    Vertices axisZ_;
    QOpenGLShaderProgram shader_axisZ;
};

#endif // AXIS_H
