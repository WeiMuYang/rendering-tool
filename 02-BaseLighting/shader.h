#ifndef SHADER_H
#define SHADER_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include "data_type.h"

class Shader : public QObject, public QOpenGLShaderProgram
{
    Q_OBJECT
public:
    explicit Shader(QObject *parent = nullptr);
signals:

private:
//    QOpenGLShaderProgram shaderPro_;
    QString name_;
    Scene scene_;
};

#endif // SHADER_H
