#include "gouraud_light.h"

GouraudLight::GouraudLight(QObject *parent)
    : QObject{parent}
{
    lightPos = {1.2f, 1.0f, 2.0f};
    lightColor = {1.0f, 1.0f, 1.0f};
    objectColor = {1.0f, 0.5f, 0.3f};
    ambientStrength = 0.1;
    specularStrength = 0.5;
}

void GouraudLight::initShader() {
    // shader
    bool success;
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Fragment,"../03-gourand-light/shader/light.frag");
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Vertex,"../03-gourand-light/shader/light.vert");
    success = shader_Light.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_Light.log();
    }
    shader_Light.bind();
    shader_Light.setUniformValue("lightColor",lightColor);

    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Fragment,"../02-phong-light/shader/shapes.frag");
    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Vertex,"../02-phong-light/shader/shapes.vert");
    success = shader_Shape.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_Shape.log();
    }
    shader_Shape.bind();
    shader_Shape.setUniformValue("objectColor", objectColor);
    shader_Shape.setUniformValue("lightColor", lightColor);
    shader_Shape.setUniformValue("viewPos", QVector3D(0.0,0.0,6.0));
    shader_Shape.setUniformValue("lightPos", lightPos);
    // ambientStrength
    shader_Shape.setUniformValue("ambientStrength", ambientStrength);
    shader_Shape.setUniformValue("specularStrength", specularStrength);
}

void GouraudLight::setShader(QString name , QVector3D value) {
    // 物体颜色
    if(name == "objectColor") {
        objectColor = value;
    }
    // 光源的颜色
    if(name == "lightColor") {
        lightColor = value;
    }

    if(name == "specularStrength") {
        specularStrength = value.x();
    }

    if(name == "ambientStrength") {
        ambientStrength = value.x();
    }
}

