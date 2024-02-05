#include "material.h"

#include "ui_material.h"

Material::Material(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Material)
{
    ui->setupUi(this);

    // 颜色
    u_objectColor = {1.0f, 0.5f, 0.3f};
    u_lightColor = {1.0f, 1.0f, 1.0f};
    // 位置
    u_lightPos ={1.2f, 1.0f, 2.0f};
    u_viewPos = {0.0f,0.0f,5.0f};

    // 材质的环境光颜色：可以是物体颜色
    u_object.ambient = {1.0f, 1.0f, 1.0f};
    // 材质的漫反射颜色： 可以是物体颜色
    u_object.diffuse = {1.0f, 1.0f, 1.0f};
    // 材质的镜面反射颜色
    u_object.specular = {0.5f, 0.5f, 0.5f};
    // 材质的反射强度
    u_object.shininess = 32.0f;

    // 光源环境光分量
    u_light.diffuse = QVector3D(0.5f,0.5f,0.5f);
    // 光源漫反射分量: 在环境光的基础上有一定的损失，因此需要环境光乘以一个0.2
    u_light.ambient = QVector3D(0.2f,0.2f,0.2f);
    // 光源镜面反射分量
    u_light.specular = QVector3D(1.0f,1.0f,1.0f);

    initSigSlot();
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
    shader_Light.setUniformValue("lightColor",u_lightColor);

    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Fragment,"../04-material/shader/shapes.frag");
    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Vertex,"../04-material/shader/shapes.vert");
    success = shader_Shape.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_Shape.log();
    }
    updateShapeShader();
}


void Material::updateShapeShader() {
    shader_Shape.bind();
    // viewPos
    shader_Shape.setUniformValue("viewPos", u_viewPos);
    // lightPos
    shader_Shape.setUniformValue("lightPos", u_lightPos);
    // color
    shader_Shape.setUniformValue("objectColor", u_objectColor);
    shader_Shape.setUniformValue("lightColor", u_lightColor);
    // material
    shader_Shape.setUniformValue("objectMaterial.ambient", u_object.ambient);
    shader_Shape.setUniformValue("objectMaterial.diffuse", u_object.diffuse);
    shader_Shape.setUniformValue("objectMaterial.specular", u_object.specular);
    shader_Shape.setUniformValue("objectMaterial.shininess", u_object.shininess);
    // light
    shader_Shape.setUniformValue("light.ambient", u_light.ambient);
    shader_Shape.setUniformValue("light.diffuse", u_light.diffuse);
    shader_Shape.setUniformValue("light.specular", u_light.specular);

    // MVP
    shader_Shape.setUniformValue("projection", projection);
    shader_Shape.setUniformValue("view", view);
    shader_Shape.setUniformValue("model", model);
}

void Material::updateLightShader()
{
    shader_Light.bind();
    shader_Light.setUniformValue("lightColor", u_lightColor);

    shader_Light.setUniformValue("projection", projection);
    shader_Light.setUniformValue("view", view);
    shader_Light.setUniformValue("model", model);
}

void Material::showWindow()
{
    show();
    updateDlg();
}


void Material::updateDlg()
{
    auto setVec3toUi = [&](QDoubleSpinBox* spinBox_X,QDoubleSpinBox* spinBox_Y,QDoubleSpinBox* spinBox_Z, QVector3D value){
        spinBox_X->setValue(value.x());
        spinBox_Y->setValue(value.y());
        spinBox_Z->setValue(value.z());
    };

    setVec3toUi(ui->Pos_X_SpinBox, ui->Pos_Y_SpinBox, ui->Pos_Z_SpinBox, u_lightPos);
    setVec3toUi(ui->Light_X_SpinBox, ui->Light_Y_SpinBox, ui->Light_Z_SpinBox, u_lightColor);
    setVec3toUi(ui->Obj_X_SpinBox, ui->Obj_Y_SpinBox, ui->Obj_Z_SpinBox, u_objectColor);
    ui->objShiny_spinBox->setValue(u_object.shininess);

    setVec3toUi(ui->objAm_X_SpinBox, ui->objAm_Y_SpinBox, ui->objAm_Z_SpinBox, u_object.ambient);
    setVec3toUi(ui->objDi_X_SpinBox, ui->objDi_Y_SpinBox, ui->objDi_Z_SpinBox, u_object.diffuse);
    setVec3toUi(ui->objSp_X_SpinBox, ui->objSp_Y_SpinBox, ui->objSp_Z_SpinBox, u_object.specular);

    setVec3toUi(ui->ligAm_X_SpinBox, ui->ligAm_Y_SpinBox, ui->ligAm_Z_SpinBox, u_light.ambient);
    setVec3toUi(ui->ligDi_X_SpinBox, ui->ligDi_Y_SpinBox, ui->ligDi_Z_SpinBox, u_light.diffuse);
    setVec3toUi(ui->ligSp_X_SpinBox, ui->ligSp_Y_SpinBox, ui->ligSp_Z_SpinBox, u_light.specular);
}

void Material::initSigSlot()
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
        u_object.shininess = arg;
    });

    connectVec3(ui->Pos_X_SpinBox, ui->Pos_Y_SpinBox,ui->Pos_Z_SpinBox, u_lightPos);
    connectVec3(ui->Light_X_SpinBox, ui->Light_Y_SpinBox,ui->Light_Z_SpinBox, u_lightColor);
    connectVec3(ui->Obj_X_SpinBox, ui->Obj_Y_SpinBox,ui->Obj_Z_SpinBox, u_objectColor);
    connectVec3(ui->objAm_X_SpinBox, ui->objAm_Y_SpinBox,ui->objAm_Z_SpinBox, u_object.ambient);
    connectVec3(ui->objDi_X_SpinBox, ui->objDi_Y_SpinBox,ui->objDi_Z_SpinBox, u_object.diffuse);
    connectVec3(ui->objSp_X_SpinBox, ui->objSp_Y_SpinBox,ui->objSp_Z_SpinBox,  u_object.specular);
    connectVec3(ui->ligAm_X_SpinBox, ui->ligAm_Y_SpinBox,ui->ligAm_Z_SpinBox, u_light.ambient);
    connectVec3(ui->ligDi_X_SpinBox, ui->ligDi_Y_SpinBox,ui->ligDi_Z_SpinBox, u_light.diffuse);
    connectVec3(ui->ligSp_X_SpinBox, ui->ligSp_Y_SpinBox,ui->ligSp_Z_SpinBox, u_light.specular);
}
