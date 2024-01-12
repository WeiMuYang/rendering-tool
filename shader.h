#ifndef SHADER_H
#define SHADER_H

#include <QObject>

class Shader : public QObject
{
    Q_OBJECT
public:
    explicit Shader(QObject *parent = nullptr);
    ~Shader();

    char* getVertexShader();
    char* getFragmentShader();
    int getVertexLen();
    int getFragLen();
    void setFrament(QString fragmentShaderSource);
    void setVertex(QString vertexShaderSource);
signals:

private:
    char* vertexShader_;
    unsigned int vertexLength_;
    char* fragmentShader_;
    unsigned int fragLength_;
};

#endif // SHADER_H
