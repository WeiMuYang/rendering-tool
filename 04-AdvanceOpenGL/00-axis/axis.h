#ifndef AXIS_H
#define AXIS_H

#include <QObject>
#include <QOpenGLShaderProgram>


class Axis : public QObject
{
    Q_OBJECT
public:
    explicit Axis(QObject *parent = nullptr);

    void initShader();
signals:

public:
    // 坐标系
    QOpenGLShaderProgram shader_axisX;

    QOpenGLShaderProgram shader_axisY;

    QOpenGLShaderProgram shader_axisZ;
};

#endif // AXIS_H
