#include "axis.h"


float verticesAxisX1[] = {
    1.0f, 0.0f, 0.0f,   // x+1
    -1.0f, 0.0f, 0.0f,  // x-1
};
float verticesAxisY1[] = {
    0.0f, 1.0f, 0.0f,   // y+1
    0.0f, -1.0f, 0.0f,  // y-1
};
float verticesAxisZ1[] = {
    0.0f, 0.0f, 1.0f,   // z+1
    0.0f, 0.0f, -1.0f,  // z-1
};


Axis::Axis(QObject *parent)
    : QObject{parent}
{
    // 坐标轴
    axisX_.setVerticesArr(verticesAxisX1, 6);
    axisY_.setVerticesArr(verticesAxisY1, 6);
    axisZ_.setVerticesArr(verticesAxisZ1, 6);
}

void Axis::initShader()
{
    bool success;
    shader_axisX.addShaderFromSourceFile(QOpenGLShader::Vertex,"../00-axis/shader/axis_X.vert");
    shader_axisX.addShaderFromSourceFile(QOpenGLShader::Fragment,"../00-axis/shader/axis_X.frag");
    success = shader_axisX.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_axisX.log();
    }

    shader_axisY.addShaderFromSourceFile(QOpenGLShader::Vertex,"../00-axis/shader/axis_Y.vert");
    shader_axisY.addShaderFromSourceFile(QOpenGLShader::Fragment,"../00-axis/shader/axis_Y.frag");
    success = shader_axisY.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_axisY.log();
    }

    shader_axisZ.addShaderFromSourceFile(QOpenGLShader::Vertex,"../00-axis/shader/axis_Z.vert");
    shader_axisZ.addShaderFromSourceFile(QOpenGLShader::Fragment,"../00-axis/shader/axis_Z.frag");
    success = shader_axisZ.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_axisZ.log();
    }
}
