#ifndef SHADER_H
#define SHADER_H

#include <QObject>
#include <QOpenGLShader>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QOpenGLFunctions_3_3_Core>

class Shader : public QObject, QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit Shader(QObject *parent = nullptr);
    Shader(const QString& vertexShaderPath, const QString& fragmentShaderPath);
    ~Shader();

    QString loadShaderSource(const QString& filePath);
    void setShader(const QString& vertexShaderPath, const QString& fragmentShaderPath);
    void use();
    void setFloat(const QString& name, float value);
    void setVec3(const QString& name, float x, float y, float z);
    unsigned int id();
    char* QString2Chars(QString Source);
signals:

private:
    unsigned int ID;
};

#endif // SHADER_H
