#include "interface_block.h"

InterfaceBlock::InterfaceBlock(QObject *parent)
    : QObject{parent}
{
    diffuseTexID = 0;

    // 位置
    u_lightPos ={1.2f, 1.0f, 2.0f};
    u_viewPos = {0.0f,0.0f,5.0f};

    // 材质的反射强度
    u_objectTex.diffuseTexID = 0;
    u_objectTex.specularTexID = 1;
    u_objectTex.reflectTexID = 2;
    u_objectTex.shininess = 32.0f;

    // 光源环境光分量
    u_lightTex.diffuse = QVector3D(0.9f, 0.9f, 0.9f);
    // 光源漫反射分量: 在环境光的基础上有一定的损失，因此需要环境光乘以一个0.2
    u_lightTex.ambient = QVector3D(0.9f, 0.9f, 0.9f);
    // 光源镜面反射分量
    u_lightTex.specular = QVector3D(1.0f, 1.0f, 1.0f);
    u_lightTex.direction = {-0.2f, -1.0f, -0.3f};
}

void InterfaceBlock::initShader() {
    // shader
    bool success;
    shader_InterfaceBlock.addShaderFromSourceFile(QOpenGLShader::Fragment,"../14-interface-block/shader/shapes.frag");
    shader_InterfaceBlock.addShaderFromSourceFile(QOpenGLShader::Vertex,"../14-interface-block/shader/shapes.vert");
    success = shader_InterfaceBlock.link();
    if(!success) {
        qDebug() << "ERR:" << shader_InterfaceBlock.log();
    }
    updateShader();
}

void InterfaceBlock::updateShader() {
    shader_InterfaceBlock.bind();
    // viewPos
    shader_InterfaceBlock.setUniformValue("viewPos", u_viewPos);
    // lightPos
    shader_InterfaceBlock.setUniformValue("lightPos", u_lightPos);
    // material
    shader_InterfaceBlock.setUniformValue("material.texture_diffuse1", u_objectTex.diffuseTexID);  // 对应纹理编号 0
    shader_InterfaceBlock.setUniformValue("material.texture_specular1", u_objectTex.specularTexID); // 对应纹理编号 1
    shader_InterfaceBlock.setUniformValue("material.texture_reflection1", u_objectTex.reflectTexID); // 对应纹理编号 2 反射纹理
    shader_InterfaceBlock.setUniformValue("material.shininess", u_objectTex.shininess);
    // light
    shader_InterfaceBlock.setUniformValue("light.ambient", u_lightTex.ambient);
    shader_InterfaceBlock.setUniformValue("light.diffuse", u_lightTex.diffuse);
    shader_InterfaceBlock.setUniformValue("light.specular", u_lightTex.specular);
    shader_InterfaceBlock.setUniformValue("light.direction", u_lightTex.direction);
    // MVP
    shader_InterfaceBlock.setUniformValue("projection", projection);
    shader_InterfaceBlock.setUniformValue("view", view);
    shader_InterfaceBlock.setUniformValue("model", model);
}
