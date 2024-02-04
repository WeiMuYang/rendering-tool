#include "texture_light.h"
#include "ui_texture_light.h"

float vertices3DBox6[] = {
    // positions          // normals          // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
 };




TextureLight::TextureLight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextureLight)
{
    ui->setupUi(this);
    // vertices
    box3D.setVerticesArr(vertices3DBox6, 288);

    // 位置
    lightPos ={1.2f, 1.0f, 2.0f};
    viewPos = {0.0f,0.0f,5.0f};

    // 材质的反射强度
    objectMaterial.diffuseTexNum = 0;
    objectMaterial.specularTexNum = 1;
    objectMaterial.emissionTexNum = 3;
    objectMaterial.shininess = 32.0f;


    lightColor ={1.0f, 1.0f, 1.0f};
    // 光源环境光分量
    light.diffuse = QVector3D(1,1,1);
    // 光源漫反射分量: 在环境光的基础上有一定的损失，因此需要环境光乘以一个0.2
    light.ambient = QVector3D(1,1,1);
    // 光源镜面反射分量
    light.specular = QVector3D(1.0,1.0,1.0);
}

TextureLight::~TextureLight()
{
    delete ui;
}


void TextureLight::initShader() {
    // shader
    bool success;
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Fragment,"../06-texture-light/shader/light.frag");
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Vertex,"../06-texture-light/shader/light.vert");
    success = shader_Light.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_Light.log();
    }
    updateLightShader();

    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Fragment,"../06-texture-light/shader/shapes.frag");
    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Vertex,"../06-texture-light/shader/shapes.vert");
    success = shader_Shape.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Shape.log();
    }
//    shader_Shape.bind();
//    shader_Shape.setUniformValue("material.diffuse", 0);
//    shader_Shape.setUniformValue("material.specular", 1);
    updateShapeShader();
}

void TextureLight::initTexture()
{
    // 按照编号 0 1 2 ... 放到CPU
    // TODO: 编号应该是整个在OpenGl中的所有的texture，所以需要看下之前有没有贴图初始化，如果有的话，编号对应会顺延
    texConrainerDiffuse = new QOpenGLTexture(QImage("../06-texture-light/img/container2.png").mirrored());
    texConrainerSpecular = new QOpenGLTexture(QImage("../06-texture-light/img/container2_specular.png").mirrored());
    texConrainerSpecularColor = new QOpenGLTexture(QImage("../06-texture-light/img/lighting_maps_specular_color.png").mirrored());
    texConrainerMat = new QOpenGLTexture(QImage("../06-texture-light/img/matrix.jpg").mirrored());
}

void TextureLight::setShader(QString name , QVector3D value) {
    if(name == "material.specularTex") {
        if(objectMaterial.specularTexNum == 1) {
            objectMaterial.specularTexNum = 2;
        }else{
            objectMaterial.specularTexNum = 1;
        }
    }
    if(name == "material.shininess") {
        objectMaterial.shininess = value.x();
    }

    // 光源的颜色
    if(name == "lightColor") {
        lightColor = value;
    }
    if(name == "lightPos") {
        lightPos = value;
    }
    if(name == "light.ambient") {
        light.ambient = value;
    }
    if(name == "light.diffuse") {
        light.diffuse = value;
    }
    if(name == "light.specular") {
        light.specular = value;
    }
}

void TextureLight::updateShapeShader() {
    shader_Shape.bind();

    // viewPos
    shader_Shape.setUniformValue("viewPos", viewPos);
    // lightPos
    shader_Shape.setUniformValue("lightPos", lightPos);
    // color
    shader_Shape.setUniformValue("lightColor", lightColor);
    // material
    shader_Shape.setUniformValue("material.diffuse", objectMaterial.diffuseTexNum);  // 对应纹理编号 0
    shader_Shape.setUniformValue("material.specular", objectMaterial.specularTexNum); // 对应纹理编号 1
    shader_Shape.setUniformValue("material.emission", objectMaterial.emissionTexNum);
    shader_Shape.setUniformValue("material.shininess", objectMaterial.shininess);
    // light
    shader_Shape.setUniformValue("light.ambient", light.ambient);
    shader_Shape.setUniformValue("light.diffuse", light.diffuse);
    shader_Shape.setUniformValue("light.specular", light.specular);

    // MVP
    shader_Shape.setUniformValue("projection", projection);
    shader_Shape.setUniformValue("view", view);
    shader_Shape.setUniformValue("model", model);

    // 将纹理信息和纹理编号对应，装入GPU
    texConrainerDiffuse->bind(0);
    texConrainerSpecular->bind(1);
    texConrainerSpecularColor->bind(2);
    texConrainerMat->bind(3);
}

void TextureLight::updateLightShader()
{
    shader_Light.bind();
    shader_Light.setUniformValue("lightColor", lightColor);

    shader_Light.setUniformValue("projection", projection);
    shader_Light.setUniformValue("view", view);
    shader_Light.setUniformValue("model", model);
}
