#include "glsl_variable.h"

GLSLVariable::GLSLVariable(QObject *parent)
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

void GLSLVariable::initShader() {
    // shader
    bool success;
    shader_GLSLVar.addShaderFromSourceFile(QOpenGLShader::Fragment,"../13-glsl-variable/shader/shapes.frag");
    shader_GLSLVar.addShaderFromSourceFile(QOpenGLShader::Vertex,"../13-glsl-variable/shader/shapes.vert");
    success = shader_GLSLVar.link();
    if(!success) {
        qDebug() << "ERR:" << shader_GLSLVar.log();
    }
    updateShader();
}

void GLSLVariable::updateShader() {
    shader_GLSLVar.bind();
    // viewPos
    shader_GLSLVar.setUniformValue("viewPos", u_viewPos);
    // lightPos
    shader_GLSLVar.setUniformValue("lightPos", u_lightPos);
    // material
    shader_GLSLVar.setUniformValue("material.texture_diffuse1", u_objectTex.diffuseTexID);  // 对应纹理编号 0
    shader_GLSLVar.setUniformValue("material.texture_specular1", u_objectTex.specularTexID); // 对应纹理编号 1
    shader_GLSLVar.setUniformValue("material.texture_reflection1", u_objectTex.reflectTexID); // 对应纹理编号 2 反射纹理
    shader_GLSLVar.setUniformValue("material.shininess", u_objectTex.shininess);
    // light
    shader_GLSLVar.setUniformValue("light.ambient", u_lightTex.ambient);
    shader_GLSLVar.setUniformValue("light.diffuse", u_lightTex.diffuse);
    shader_GLSLVar.setUniformValue("light.specular", u_lightTex.specular);
    shader_GLSLVar.setUniformValue("light.direction", u_lightTex.direction);
    // MVP
    shader_GLSLVar.setUniformValue("projection", projection);
    shader_GLSLVar.setUniformValue("view", view);
    shader_GLSLVar.setUniformValue("model", model);
}
