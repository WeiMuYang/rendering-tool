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
    u_lightPos ={1.2f, 1.0f, 2.0f};
    u_viewPos = {0.0f,0.0f,5.0f};

    // 材质的反射强度
    u_objectTex.diffuseTexID = 0;
    u_objectTex.specularTexID = 1;
    u_objectTex.emissionTexID = 3;
    u_objectTex.shininess = 32.0f;


    u_lightColor ={1.0f, 1.0f, 1.0f};
    // 光源环境光分量
    u_lightTex.diffuse = QVector3D(1,1,1);
    // 光源漫反射分量: 在环境光的基础上有一定的损失，因此需要环境光乘以一个0.2
    u_lightTex.ambient = QVector3D(1,1,1);
    // 光源镜面反射分量
    u_lightTex.specular = QVector3D(1.0,1.0,1.0);

    initSigSlot();
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
        if(u_objectTex.specularTexID == 1) {
            u_objectTex.specularTexID = 2;
        }else{
            u_objectTex.specularTexID = 1;
        }
    }
    if(name == "material.shininess") {
        u_objectTex.shininess = value.x();
    }

    // 光源的颜色
    if(name == "lightColor") {
        u_lightColor = value;
    }
    if(name == "lightPos") {
        u_lightPos = value;
    }
    if(name == "light.ambient") {
        u_lightTex.ambient = value;
    }
    if(name == "light.diffuse") {
        u_lightTex.diffuse = value;
    }
    if(name == "light.specular") {
        u_lightTex.specular = value;
    }
}

void TextureLight::updateShapeShader() {
    shader_Shape.bind();

    // viewPos
    shader_Shape.setUniformValue("viewPos", u_viewPos);
    // lightPos
    shader_Shape.setUniformValue("lightPos", u_lightPos);
    // color
    shader_Shape.setUniformValue("lightColor", u_lightColor);
    // material
    shader_Shape.setUniformValue("material.diffuse", u_objectTex.diffuseTexID);  // 对应纹理编号 0
    shader_Shape.setUniformValue("material.specular", u_objectTex.specularTexID); // 对应纹理编号 1
    shader_Shape.setUniformValue("material.emission", u_objectTex.emissionTexID); //
    shader_Shape.setUniformValue("material.shininess", u_objectTex.shininess);
    // light
    shader_Shape.setUniformValue("light.ambient", u_lightTex.ambient);
    shader_Shape.setUniformValue("light.diffuse", u_lightTex.diffuse);
    shader_Shape.setUniformValue("light.specular", u_lightTex.specular);

    // MVP
    shader_Shape.setUniformValue("projection", projection);
    shader_Shape.setUniformValue("view", view);
    shader_Shape.setUniformValue("model", model);

    // 将纹理信息和纹理编号对应，装入GPU
    texConrainerDiffuse->bind(TextureLighttexID::texConrainerDiffuse06);
    texConrainerSpecular->bind(TextureLighttexID::texConrainerSpecular06);
    texConrainerSpecularColor->bind(TextureLighttexID::texConrainerSpecularColor06);
    texConrainerMat->bind(TextureLighttexID::texConrainerMat06);
}

void TextureLight::updateLightShader()
{
    shader_Light.bind();
    shader_Light.setUniformValue("lightColor", u_lightColor);

    shader_Light.setUniformValue("projection", projection);
    shader_Light.setUniformValue("view", view);
    shader_Light.setUniformValue("model", model);
}

void TextureLight::showWindow()
{
    show();
    updateDlg();
}

void TextureLight::updateDlg()
{
    auto setVec3toUi = [&](QDoubleSpinBox* spinBox_X,QDoubleSpinBox* spinBox_Y,QDoubleSpinBox* spinBox_Z, QVector3D value){
        spinBox_X->setValue(value.x());
        spinBox_Y->setValue(value.y());
        spinBox_Z->setValue(value.z());
    };

    setVec3toUi(ui->Pos_X_SpinBox, ui->Pos_Y_SpinBox, ui->Pos_Z_SpinBox, u_lightPos);
    setVec3toUi(ui->Light_X_SpinBox, ui->Light_Y_SpinBox, ui->Light_Z_SpinBox, u_lightColor);
    ui->objShiny_spinBox->setValue(u_objectTex.shininess);


    ui->objDi_comboBox->setCurrentIndex(1);
    ui->objSp_comboBox->setCurrentIndex(1);
    ui->objEm_comboBox->setCurrentIndex(1);

    setVec3toUi(ui->ligAm_X_SpinBox, ui->ligAm_Y_SpinBox, ui->ligAm_Z_SpinBox, u_lightTex.ambient);
    setVec3toUi(ui->ligDi_X_SpinBox, ui->ligDi_Y_SpinBox, ui->ligDi_Z_SpinBox, u_lightTex.diffuse);
    setVec3toUi(ui->ligSp_X_SpinBox, ui->ligSp_Y_SpinBox, ui->ligSp_Z_SpinBox, u_lightTex.specular);
}

void TextureLight::initSigSlot()
{
    auto connectVec3 = [&](QDoubleSpinBox* spinBox_X, QDoubleSpinBox* spinBox_Y,QDoubleSpinBox* spinBox_Z,QVector3D& vec3Obj) {
        QObject::connect(spinBox_X, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
            vec3Obj.setX(arg);
        });
        QObject::connect(spinBox_Y, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
            vec3Obj.setY(arg);
        });
        QObject::connect(spinBox_Z, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
            vec3Obj.setZ(arg);
        });
    };

    QObject::connect(ui->objShiny_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int arg){
        u_objectTex.shininess = arg;
    });

    connectVec3(ui->Pos_X_SpinBox, ui->Pos_Y_SpinBox,ui->Pos_Z_SpinBox, u_lightPos);
    connectVec3(ui->Light_X_SpinBox, ui->Light_Y_SpinBox,ui->Light_Z_SpinBox, u_lightColor);

    QObject::connect(ui->objDi_comboBox, &QComboBox::currentTextChanged, this, [&](QString name) {
        if(name == "无") {
            u_objectTex.diffuseTexID = 100; // 无效ID
        }else{
            u_objectTex.diffuseTexID = TextureLighttexID::texConrainerDiffuse06;
        }
    });

    QObject::connect(ui->objSp_comboBox, &QComboBox::currentTextChanged, this, [&](QString name) {
        if(name == "无") {
            u_objectTex.specularTexID = 100; // 无效ID
        }else if (name == "container2_specular"){
            u_objectTex.specularTexID = TextureLighttexID::texConrainerSpecular06;
        }else {
            u_objectTex.specularTexID = TextureLighttexID::texConrainerSpecularColor06;
        }
    });

    QObject::connect(ui->objEm_comboBox, &QComboBox::currentTextChanged, this, [&](QString name) {
        if(name == "无") {
            u_objectTex.emissionTexID = 100; // 无效ID
        }else{
            u_objectTex.emissionTexID = TextureLighttexID::texConrainerMat06;
        }
    });

    connectVec3(ui->ligAm_X_SpinBox, ui->ligAm_Y_SpinBox,ui->ligAm_Z_SpinBox, u_lightTex.ambient);
    connectVec3(ui->ligDi_X_SpinBox, ui->ligDi_Y_SpinBox,ui->ligDi_Z_SpinBox, u_lightTex.diffuse);
    connectVec3(ui->ligSp_X_SpinBox, ui->ligSp_Y_SpinBox,ui->ligSp_Z_SpinBox, u_lightTex.specular);
}
