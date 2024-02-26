#include "stencil_outline.h"

StencilOutLine::StencilOutLine(QObject *parent)
    : QObject{parent}
{

    // 位置
    u_lightPos ={1.2f, 1.0f, 2.0f};
    u_viewPos = {0.0f,0.0f,5.0f};

    // 材质的反射强度
    u_objectTex.diffuseTexID = 0;
    u_objectTex.specularTexID = 1;
    u_objectTex.shininess = 32.0f;

    u_lightColor ={1.0f, 1.0f, 1.0f};
    // 光源环境光分量
    u_lightTex.diffuse = QVector3D(0.9f, 0.9f, 0.9f);
    // 光源漫反射分量: 在环境光的基础上有一定的损失，因此需要环境光乘以一个0.2
    u_lightTex.ambient = QVector3D(0.4f, 0.4f, 0.4f);
    // 光源镜面反射分量
    u_lightTex.specular = QVector3D(1.0f, 1.0f, 1.0f);
    u_lightTex.direction = {-0.2f, -1.0f, -0.3f};

}

void StencilOutLine::initShader() {
    // shader
    bool success;

    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Fragment,"../05-stencil-outline/shader/shapes.frag");
    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Vertex,"../05-stencil-outline/shader/shapes.vert");
    success = shader_Shape.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Shape.log();
    }
    updateShapeShader();

    shader_Outline.addShaderFromSourceFile(QOpenGLShader::Fragment,"../05-stencil-outline/shader/singleColor.frag");
    shader_Outline.addShaderFromSourceFile(QOpenGLShader::Vertex,"../05-stencil-outline/shader/shapes.vert");
    success = shader_Outline.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Shape.log();
    }
    updateOutLineShader();
}

void StencilOutLine::updateShapeShader() {
    shader_Shape.bind();

    // viewPos
    shader_Shape.setUniformValue("viewPos", u_viewPos);
    // lightPos
    shader_Shape.setUniformValue("lightPos", u_lightPos);
    // color
    shader_Shape.setUniformValue("lightColor", u_lightColor);

    // material
    shader_Shape.setUniformValue("material.texture_diffuse", u_objectTex.diffuseTexID);  // 对应纹理编号 0
    shader_Shape.setUniformValue("material.texture_specular", u_objectTex.specularTexID); // 对应纹理编号 1
    shader_Shape.setUniformValue("material.shininess", u_objectTex.shininess);
    // light
    shader_Shape.setUniformValue("light.ambient", u_lightTex.ambient);
    shader_Shape.setUniformValue("light.diffuse", u_lightTex.diffuse);
    shader_Shape.setUniformValue("light.specular", u_lightTex.specular);
    shader_Shape.setUniformValue("light.direction", u_lightTex.direction);

    // MVP
    shader_Shape.setUniformValue("projection", projection);
    shader_Shape.setUniformValue("view", view);
    shader_Shape.setUniformValue("model", model);
}

void StencilOutLine::updateOutLineShader() {
    shader_Outline.bind();

    // MVP
    shader_Outline.setUniformValue("projection", projection);
    shader_Outline.setUniformValue("view", view);
    shader_Outline.setUniformValue("model", model);
}



