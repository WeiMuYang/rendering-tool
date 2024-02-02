#include "phong_light.h"
#include <QDebug>

float vertices3DBox2[] = {
    // Position             Normal
     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
 };

unsigned int indicesRect2[6] = {
    // 注意索引从0开始!
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};


PhongLight::PhongLight(QObject *parent)
    : QObject{parent}
{
    lightPos = {1.2f, 1.0f, 2.0f};
    lightColor = {1.0f, 1.0f, 1.0f};
    objectColor = {1.0f, 0.5f, 0.3f};
    ambientStrength = 0.1f;
    specularStrength = 0.5f;
    shiny = 32;

    // vertices
    box3D.setVerticesArr(vertices3DBox2, 216);
    box3D.setIndices(indicesRect2, 6);
}

void PhongLight::initShader() {
    // shader
    bool success;
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Fragment,"../02-phong-light/shader/light.frag");
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Vertex,"../02-phong-light/shader/light.vert");
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

void PhongLight::setShader(QString name , QVector3D value) {
    // 物体颜色
    if(name == "objectColor") {
        objectColor = value;
    }
    // 光源的颜色
    if(name == "lightColor") {
        lightColor = value;
    }

    if(name == "specularStrength") {
        qDebug() << value.x();
        specularStrength = value.x();
    }

    if(name == "ambientStrength") {
        ambientStrength = value.x();
    }

    if(name == "shiny")  {//shiny
        shiny = value.x();
    }
}


