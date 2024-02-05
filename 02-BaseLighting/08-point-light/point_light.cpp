#include "point_light.h"
#include "ui_point_light.h"

PointLight::PointLight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointLight)
{
    ui->setupUi(this);

    // 位置  改成方向
    u_lightPos ={-0.2f, -1.0f, -0.3f};
    u_viewPos = {0.0f,0.0f,5.0f};

    // 材质的反射强度
    u_objectTex.diffuseTexID = 0;
    u_objectTex.specularTexID = 1;
    u_objectTex.shininess = 32.0f;


    u_lightColor ={1.0f, 1.0f, 1.0f};
    // 光源环境光分量
    u_light.diffuse = QVector3D(1,1,1);
    // 光源漫反射分量: 在环境光的基础上有一定的损失，因此需要环境光乘以一个0.2
    u_light.ambient = QVector3D(1,1,1);
    // 光源镜面反射分量
    u_light.specular = QVector3D(1.0,1.0,1.0);

    u_light.constant = 1.0f;
    u_light.linear = 0.09f;
    u_light.quadratic = 0.032f;

    initSigSlot();
}

PointLight::~PointLight()
{
    delete ui;
}

void PointLight::initShader() {
    // shader
    bool success;
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Fragment,"../08-point-light/shader/light.frag");
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Vertex,"../08-point-light/shader/light.vert");
    success = shader_Light.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_Light.log();
    }
    updateLightShader();

    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Fragment,"../08-point-light/shader/shapes.frag");
    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Vertex,"../08-point-light/shader/shapes.vert");
    success = shader_Shape.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Shape.log();
    }
    updateShapeShader();
}

void PointLight::initTexture()
{
    // 按照编号 0 1 2 ... 放到CPU
    // TODO: 编号应该是整个在OpenGl中的所有的texture，所以需要看下之前有没有贴图初始化，如果有的话，编号对应会顺延
    texConrainerDiffuse = new QOpenGLTexture(QImage("../08-point-light/img/container2.png").mirrored());
    texConrainerSpecular = new QOpenGLTexture(QImage("../08-point-light/img/container2_specular.png").mirrored());
}


void PointLight::updateShapeShader() {
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
    shader_Shape.setUniformValue("material.shininess", u_objectTex.shininess);
    // light
    shader_Shape.setUniformValue("light.ambient", u_light.ambient);
    shader_Shape.setUniformValue("light.diffuse", u_light.diffuse);
    shader_Shape.setUniformValue("light.specular", u_light.specular);

    shader_Shape.setUniformValue("light.constant", u_light.constant);
    shader_Shape.setUniformValue("light.linear", u_light.linear);
    shader_Shape.setUniformValue("light.quadratic", u_light.quadratic);

    // MVP
    shader_Shape.setUniformValue("projection", projection);
    shader_Shape.setUniformValue("view", view);
    shader_Shape.setUniformValue("model", model);

    // 将纹理信息和纹理编号对应，装入GPU
    texConrainerDiffuse->bind(PointLightTexID::texConrainerDiffuse08);
    texConrainerSpecular->bind(PointLightTexID::texConrainerSpecular08);
}

void PointLight::updateLightShader()
{
    shader_Light.bind();
    shader_Light.setUniformValue("lightColor", u_lightColor);

    shader_Light.setUniformValue("projection", projection);
    shader_Light.setUniformValue("view", view);
    shader_Light.setUniformValue("model", model);
}

void PointLight::showWindow()
{
    show();
    updateDlg();
}

void PointLight::updateDlg()
{
    auto setVec3toUi = [&](QDoubleSpinBox* spinBox_X,QDoubleSpinBox* spinBox_Y,QDoubleSpinBox* spinBox_Z, QVector3D value){
        spinBox_X->setValue(value.x());
        spinBox_Y->setValue(value.y());
        spinBox_Z->setValue(value.z());
    };

    setVec3toUi(ui->Pos_X_SpinBox, ui->Pos_Y_SpinBox, ui->Pos_Z_SpinBox, u_lightPos);
    setVec3toUi(ui->Light_X_SpinBox, ui->Light_Y_SpinBox, ui->Light_Z_SpinBox, u_lightColor);
    setVec3toUi(ui->ligAm_X_SpinBox, ui->ligAm_Y_SpinBox, ui->ligAm_Z_SpinBox, u_light.ambient);
    setVec3toUi(ui->ligDi_X_SpinBox, ui->ligDi_Y_SpinBox, ui->ligDi_Z_SpinBox, u_light.diffuse);
    setVec3toUi(ui->ligSp_X_SpinBox, ui->ligSp_Y_SpinBox, ui->ligSp_Z_SpinBox, u_light.specular);

    ui->objShiny_spinBox->setValue(u_objectTex.shininess);
    ui->objDi_comboBox->setCurrentIndex(1);
    ui->objSp_comboBox->setCurrentIndex(1);

    ui->ligCon_SpinBox->setValue(u_light.constant);
    ui->ligLin_SpinBox->setValue(u_light.linear);
    ui->ligQua_SpinBox->setValue(u_light.quadratic);
}

void PointLight::initSigSlot()
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
            u_objectTex.diffuseTexID = PointLightTexID::texConrainerDiffuse08;
        }
    });

    QObject::connect(ui->objSp_comboBox, &QComboBox::currentTextChanged, this, [&](QString name) {
        if(name == "无") {
            u_objectTex.specularTexID = 100; // 无效ID
        }else if (name == "container2_specular"){
            u_objectTex.specularTexID = PointLightTexID::texConrainerSpecular08;
        }else {
            u_objectTex.specularTexID = PointLightTexID::texConrainerSpecularColor08;
        }
    });


    connectVec3(ui->ligAm_X_SpinBox, ui->ligAm_Y_SpinBox,ui->ligAm_Z_SpinBox, u_light.ambient);
    connectVec3(ui->ligDi_X_SpinBox, ui->ligDi_Y_SpinBox,ui->ligDi_Z_SpinBox, u_light.diffuse);
    connectVec3(ui->ligSp_X_SpinBox, ui->ligSp_Y_SpinBox,ui->ligSp_Z_SpinBox, u_light.specular);

    QObject::connect(ui->ligCon_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
        u_light.constant = arg;
    });
    QObject::connect(ui->ligLin_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
        u_light.linear = arg;
    });
    QObject::connect(ui->ligQua_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
        u_light.quadratic = arg;
    });
}

