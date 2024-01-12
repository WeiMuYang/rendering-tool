#include "shader.h"

Shader::Shader(QObject *parent)
    : QObject{parent}
{
    vertexLength_ = 0;
    fragLength_ = 0;
}

char* Shader::getVertexShader() {
    return vertexShader_;
}

char* Shader::getFragmentShader() {
    return fragmentShader_;
}

int Shader::getVertexLen() {
    return vertexLength_;
}

int Shader::getFragLen() {
    return fragLength_;
}

void Shader::setFrament(QString fragmentShaderSource) {
    fragLength_ = fragmentShaderSource.length();
    fragmentShader_ = new char[fragLength_ + 1];
    std::strcpy(fragmentShader_, fragmentShaderSource.toUtf8().constData());
}

void Shader::setVertex(QString vertexShaderSource) {
    vertexLength_ = vertexShaderSource.length();
    vertexShader_ = new char[vertexLength_ + 1];
    std::strcpy(vertexShader_, vertexShaderSource.toUtf8().constData());
}

Shader::~Shader(){
    delete[] vertexShader_;
    delete[] fragmentShader_;
}
