#include "phong_light.h"
#include "ui_phong_light.h"
#include <QDebug>

float vertices3DBox2[] = {
    // Position             Normal
     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
 };

unsigned int indicesRect2[6] = {
    // 注意索引从0开始!
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};



PhongLight::PhongLight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PhongLight)
{
    ui->setupUi(this);
    u_lightPos = {1.2f, 1.0f, 2.0f};
    u_lightColor = {1.0f, 1.0f, 1.0f};
    u_objectColor = {1.0f, 0.5f, 0.3f};
    u_ambientStrength = 0.1f;
    u_specularStrength = 0.5f;
    u_shiny = 32;

    // vertices
    box3D.setVerticesArr(vertices3DBox2, 216);
    box3D.setIndices(indicesRect2, 6);

    initSigSlot();
}

PhongLight::~PhongLight()
{
    delete ui;
}

void PhongLight::showWindow()
{
    show();
    updateDlg();
}

void PhongLight::initShader() {
    // shader
    bool success;
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Fragment,"../02-phong-light/shader/light.frag");
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Vertex,"../02-phong-light/shader/light.vert");
    success = shader_Light.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_Light.log();
    }
    updateLightShader();

    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Fragment,"../02-phong-light/shader/shapes.frag");
    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Vertex,"../02-phong-light/shader/shapes.vert");
    success = shader_Shape.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_Shape.log();
    }
    updateShapeShader();
}

void PhongLight::updateShapeShader()
{
    shader_Shape.bind();
    shader_Shape.setUniformValue("projection", projection);
    shader_Shape.setUniformValue("view", view);
    shader_Shape.setUniformValue("model", model);

    shader_Shape.setUniformValue("objectColor", u_objectColor);
    shader_Shape.setUniformValue("lightColor", u_lightColor);
    shader_Shape.setUniformValue("viewPos", u_viewPos);
    shader_Shape.setUniformValue("lightPos", u_lightPos);
    // ambientStrength
    shader_Shape.setUniformValue("ambientStrength", u_ambientStrength);
    shader_Shape.setUniformValue("specularStrength", u_specularStrength);
    shader_Shape.setUniformValue("shiny", u_shiny);
}

void PhongLight::updateLightShader()
{
    shader_Light.bind();
    shader_Light.setUniformValue("lightColor",u_lightColor);

    shader_Light.setUniformValue("projection", projection);
    shader_Light.setUniformValue("view", view);
    shader_Light.setUniformValue("model", model);
}

void PhongLight::updateDlg()
{
    ui->Pos_X_SpinBox->setValue(u_lightPos.x());
    ui->Pos_Y_SpinBox->setValue(u_lightPos.y());
    ui->Pos_Z_SpinBox->setValue(u_lightPos.z());

    ui->Light_X_SpinBox->setValue(u_lightColor.x());
    ui->Light_Y_SpinBox->setValue(u_lightColor.y());
    ui->Light_Z_SpinBox->setValue(u_lightColor.z());

    ui->Obj_X_SpinBox->setValue(u_objectColor.x());
    ui->Obj_X_SpinBox->setValue(u_objectColor.y());
    ui->Obj_X_SpinBox->setValue(u_objectColor.z());

    ui->PhongAmbient_SpinBox->setValue(u_ambientStrength);
    ui->PhongSpecular_SpinBox->setValue(u_specularStrength);
    ui->shiny_spinBox->setValue(u_shiny);

}

void PhongLight::initSigSlot()
{
    QObject::connect(ui->Pos_X_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
        u_lightPos.setX((float)arg);
    });
    QObject::connect(ui->Pos_Y_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
        u_lightPos.setY((float)arg);
    });
    QObject::connect(ui->Pos_Z_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
        u_lightPos.setZ((float)arg);
    });

    QObject::connect(ui->Light_X_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
        u_lightColor.setX((float)arg);
    });
    QObject::connect(ui->Light_Y_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
        u_lightColor.setY((float)arg);
    });
    QObject::connect(ui->Light_Z_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
        u_lightColor.setZ((float)arg);
    });

    QObject::connect(ui->Obj_X_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
        u_objectColor.setX((float)arg);
    });
    QObject::connect(ui->Obj_Y_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
        u_objectColor.setY((float)arg);
    });
    QObject::connect(ui->Obj_Z_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
        u_objectColor.setZ((float)arg);
    });

    // PhongAmbient_SpinBox
    QObject::connect(ui->PhongAmbient_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
        u_ambientStrength = arg;
    });

    QObject::connect(ui->PhongSpecular_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
        u_specularStrength = arg;
    });

    QObject::connect(ui->shiny_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int arg){
        u_shiny = arg;
    });
}

