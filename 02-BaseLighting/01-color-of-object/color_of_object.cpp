#include "color_of_object.h"
#include "ui_color_of_object.h"
#include <QMatrix4x4>
#include <QVector3D>

float vertices3DBox1[] = {
    // 第一个面：Pos.xyz  texture.uv
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    // 第二个面：Pos.xyz  texture.uv
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    // 第三个面：Pos.xyz  texture.uv
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    // 第四个面：Pos.xyz  texture.uv
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    // 第五个面：Pos.xyz  texture.uv
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    // 第六个面：Pos.xyz  texture.uv
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};



unsigned int indicesRect1[6] = {
    // 注意索引从0开始!
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};



ColorOfObject::ColorOfObject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorOfObject)
{
    ui->setupUi(this);
    u_lightPos = {1.2f, 1.0f, 2.0f};
    u_lightColor = {1.0f, 1.0f, 1.0f};
    u_objectColor = {1.0f, 0.5f, 0.3f};

    // vertices
    box3D.setVerticesArr(vertices3DBox1, 180);
    box3D.setIndices(indicesRect1, 6);

    initSigSlot();
}

ColorOfObject::~ColorOfObject()
{
    delete ui;
}

template<class T>
void connectSpinBox(QDoubleSpinBox* spinBox, T& value, void (T::*setter)(float))
{
    QObject::connect(spinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [&](double arg){
        (value.*setter)(arg);
    });
}

void ColorOfObject::initSigSlot() {
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

}


void ColorOfObject::initShader() {
    // shader
    bool success;
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Fragment,"../01-color-of-object/shader/ColorOfObject_light.frag");
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Vertex,"../01-color-of-object/shader/ColorOfObject_light.vert");
    success = shader_Light.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_Light.log();
    }
    updateLightShader();

    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Fragment,"../01-color-of-object/shader/ColorOfObject_shapes.frag");
    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Vertex,"../01-color-of-object/shader/ColorOfObject_shapes.vert");
    success = shader_Shape.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_Shape.log();
    }
    updateShapeShader();
}

void ColorOfObject::showWindow()
{
    show();
    updateDlg();
}

void ColorOfObject::updateShapeShader()
{
    shader_Shape.bind();

    shader_Shape.setUniformValue("projection", projection);
    shader_Shape.setUniformValue("view", view);
    shader_Shape.setUniformValue("model", model);

    shader_Shape.setUniformValue("objectColor",u_objectColor);
    shader_Shape.setUniformValue("lightColor",u_lightColor);
}

void ColorOfObject::updateLightShader()
{
    shader_Light.bind();
    shader_Light.setUniformValue("projection", projection);
    shader_Light.setUniformValue("view", view);
    shader_Light.setUniformValue("model", model);
    shader_Light.setUniformValue("lightColor",u_lightColor);
}


// 在类外修改的数据更新到UI
void ColorOfObject::updateDlg() {
    ui->Pos_X_SpinBox->setValue(u_lightPos.x());
    ui->Pos_Y_SpinBox->setValue(u_lightPos.y());
    ui->Pos_Z_SpinBox->setValue(u_lightPos.z());

    ui->Light_X_SpinBox->setValue(u_lightColor.x());
    ui->Light_Y_SpinBox->setValue(u_lightColor.y());
    ui->Light_Z_SpinBox->setValue(u_lightColor.z());

    ui->Obj_X_SpinBox->setValue(u_objectColor.x());
    ui->Obj_X_SpinBox->setValue(u_objectColor.y());
    ui->Obj_X_SpinBox->setValue(u_objectColor.z());
}







