#ifndef COLOROFOBJECT_H
#define COLOROFOBJECT_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector>

#include "../vertices.h"
class ColorOfObject : public QObject
{
    Q_OBJECT
public:
    explicit ColorOfObject(QObject *parent = nullptr);
    void initShader() ;

public:
    Vertices box3D;
    QOpenGLShaderProgram shader_Light;
    QOpenGLShaderProgram shader_Shape;
    QVector3D lightPos;
    QVector3D lightColor;
    QVector3D objectColor;
    void setShader(QString name, QVector3D value);
};


#endif // COLOROFOBJECT_H
