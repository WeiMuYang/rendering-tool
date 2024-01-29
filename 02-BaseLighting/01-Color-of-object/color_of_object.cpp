#include "color_of_object.h"
#include <QMatrix4x4>
#include <QVector3D>

float vertices3DBox1[] = {
    // 第一个面：Pos.xyz  texture.uv
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    // 第二个面：Pos.xyz  texture.uv
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    // 第三个面：Pos.xyz  texture.uv
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    // 第四个面：Pos.xyz  texture.uv
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    // 第五个面：Pos.xyz  texture.uv
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    // 第六个面：Pos.xyz  texture.uv
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};



unsigned int indicesRect1[6] = {
    // 注意索引从0开始!
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};



ColorOfObject::ColorOfObject(QObject *parent)
    : QObject{parent}
{
    lightPos = {1.2f, 1.0f, 2.0f};
    lightColor = {1.0f, 1.0f, 1.0f};
    objectColor = {1.0f, 0.5f, 0.3f};

    // vertices
    box3D.setVerticesArr(vertices3DBox1, 180);
    box3D.setIndices(indicesRect1, 6);
}

void ColorOfObject::initShader() {
    // shader
    bool success;
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Fragment,"../01-color-of-object/shader/ColorOfObject_light.frag");
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Vertex,"../01-color-of-object/shader/ColorOfObject_light.vert");
    success = shader_Light.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_Light.log();
    }
    shader_Light.bind();
    shader_Light.setUniformValue("lightColor",lightColor);

    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Fragment,"../01-color-of-object/shader/ColorOfObject_shapes.frag");
    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Vertex,"../01-color-of-object/shader/ColorOfObject_shapes.vert");
    success = shader_Shape.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_Shape.log();
    }
    shader_Shape.bind();
    // FragColor = vec4(lightColor * objectColor, 1.0);
    // 分量相乘，对应的元素相乘
    shader_Shape.setUniformValue("objectColor",objectColor);
    shader_Shape.setUniformValue("lightColor",lightColor);
}

void ColorOfObject::setShader(QString name , QVector3D value) {
    // 物体颜色
    if(name == "objectColor") {
        objectColor = value;
    }
    // 光源的颜色
    if(name == "lightColor") {
        lightColor = value;
    }
}


