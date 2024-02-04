#include "material.h"

#include "ui_material.h"

Material::Material(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Material)
{
    ui->setupUi(this);

    // 颜色
    objectColor = {1.0f, 0.5f, 0.3f};
    lightColor = {1.0f, 1.0f, 1.0f};
    // 位置
    lightPos ={1.2f, 1.0f, 2.0f};
    viewPos = {0.0f,0.0f,5.0f};

    // 材质的环境光颜色：可以是物体颜色
    objectMaterial.ambient = {1.0f, 1.0f, 1.0f};
    // 材质的漫反射颜色： 可以是物体颜色
    objectMaterial.diffuse = {1.0f, 1.0f, 1.0f};
    // 材质的镜面反射颜色
    objectMaterial.specular = {0.5f, 0.5f, 0.5f};
    // 材质的反射强度
    objectMaterial.shininess = 32.0f;

    // 光源环境光分量
    light.diffuse = QVector3D(0.5,0.5,0.5);
    // 光源漫反射分量: 在环境光的基础上有一定的损失，因此需要环境光乘以一个0.2
    light.ambient = QVector3D(0.2,0.2,0.2);
    // 光源镜面反射分量
    light.specular = QVector3D(1.0,1.0,1.0);
}

Material::~Material()
{
    delete ui;
}

void Material::initShader() {
    // shader
    bool success;
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Fragment,"../04-material/shader/light.frag");
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Vertex,"../04-material/shader/light.vert");
    success = shader_Light.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_Light.log();
    }
    shader_Light.bind();
    shader_Light.setUniformValue("lightColor",lightColor);

    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Fragment,"../04-material/shader/shapes.frag");
    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Vertex,"../04-material/shader/shapes.vert");
    success = shader_Shape.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_Shape.log();
    }
    updateShapeShader();
}

void Material::setShader(QString name , QVector3D value) {
//    // 物体颜色
//    if(name == "objectColor") {
//        objectColor = value;
//    }
//    // 光源的颜色
//    if(name == "lightColor") {
//        lightColor = value;
//    }
}

void Material::updateShapeShader() {
    shader_Shape.bind();
    // viewPos
    shader_Shape.setUniformValue("viewPos", viewPos);
    // lightPos
    shader_Shape.setUniformValue("lightPos", lightPos);
    // color
    shader_Shape.setUniformValue("objectColor", objectColor);
    shader_Shape.setUniformValue("lightColor", lightColor);
    // material
    shader_Shape.setUniformValue("objectMaterial.ambient", objectMaterial.ambient);
    shader_Shape.setUniformValue("objectMaterial.diffuse", objectMaterial.diffuse);
    shader_Shape.setUniformValue("objectMaterial.specular", objectMaterial.specular);
    shader_Shape.setUniformValue("objectMaterial.shininess", objectMaterial.shininess);
    // light
    shader_Shape.setUniformValue("light.ambient", light.ambient);
    shader_Shape.setUniformValue("light.diffuse", light.diffuse);
    shader_Shape.setUniformValue("light.specular", light.specular);

    // MVP
    shader_Shape.setUniformValue("projection", projection);
    shader_Shape.setUniformValue("view", view);
    shader_Shape.setUniformValue("model", model);
}

void Material::updateLightShader()
{
    shader_Light.bind();
    shader_Light.setUniformValue("lightColor", lightColor);

    shader_Light.setUniformValue("projection", projection);
    shader_Light.setUniformValue("view", view);
    shader_Light.setUniformValue("model", model);
}
