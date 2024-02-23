#include "load_models.h"

LoadModels::LoadModels(QObject *parent)
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

void LoadModels::initTexture()
{
    // 按照编号 0 1 2 ... 放到CPU
    // TODO: 编号应该是整个在OpenGl中的所有的texture，所以需要看下之前有没有贴图初始化，如果有的话，编号对应会顺延
    QOpenGLTexture *OpenGLtexPlane = new QOpenGLTexture(QImage("../04-load-models/img/wall.jpg").mirrored());

    texPlane.path = "../04-load-models/img/wall.jpg";
    texPlane.id = OpenGLtexPlane->textureId();
    texPlane.type = "texture_diffuse";
}

void LoadModels::initShader() {
    // shader
    bool success;

    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Fragment,"../04-load-models/shader/shapes.frag");
    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Vertex,"../04-load-models/shader/shapes.vert");
    success = shader_Shape.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Shape.log();
    }
    updateShapeShader();
}


void LoadModels::updateShapeShader() {
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
