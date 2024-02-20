#include "depth_testing.h"
#include "ui_depth_testing.h"
#include <QDoubleSpinBox>

float cubeVertices_01[] = {
    // positions          // texture Coords
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
float planeVertices_01[] = {
    // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
    5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,

    5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,
    5.0f, -0.5f, -5.0f,  1.0f, 1.0f
};


DepthTesting::DepthTesting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DepthTesting)
{
    ui->setupUi(this);

    int size = sizeof(cubeVertices_01) / sizeof(float);
    for (int i = 0; i < size; i++) {
        cubeVertices.push_back(cubeVertices_01[i]);
    }
    cubeVerCount = 36;

    size = sizeof(planeVertices_01) / sizeof(float);
    for (int i = 0; i < size; i++) {
        planeVertices.push_back(planeVertices_01[i]);
    }
    planeVerCount = 6;

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

DepthTesting::~DepthTesting()
{
    delete ui;
}

void DepthTesting::initShader() {
    // shader
    bool success;
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Fragment,"../01-depth-testing/shader/light.frag");
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Vertex,"../01-depth-testing/shader/light.vert");
    success = shader_Light.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_Light.log();
    }
    updateLightShader();

    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Fragment,"../01-depth-testing/shader/shapes.frag");
    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Vertex,"../01-depth-testing/shader/shapes.vert");
    success = shader_Shape.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Shape.log();
    }
    updateShapeShader();
}

void DepthTesting::initTexture()
{
    cubeTextures.clear();
    planeTextures.clear();
    // 按照编号 0 1 2 ... 放到CPU
    // TODO: 编号应该是整个在OpenGl中的所有的texture，所以需要看下之前有没有贴图初始化，如果有的话，编号对应会顺延
    texConrainerDiffuse = new QOpenGLTexture(QImage("../01-depth-testing/img/container2.png").mirrored());
    texConrainerSpecular = new QOpenGLTexture(QImage("../01-depth-testing/img/matrix.jpg").mirrored());

    Texture tex;
    tex.path = "../01-depth-testing/img/container2.png";
    tex.id = texConrainerDiffuse->textureId();
    tex.type = "texture_diffuse";
    cubeTextures.push_back(tex);


    tex.path = "../01-depth-testing/img/matrix.jpg";
    tex.id = texConrainerSpecular->textureId();
    tex.type = "texture_diffuse";
    planeTextures.push_back(tex);
}

void DepthTesting::updateShapeShader() {
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

    //    // 将纹理信息和纹理编号对应，装入GPU
    //    texConrainerDiffuse->bind(0);
    //    texConrainerSpecular->bind(1);
}

void DepthTesting::updateLightShader()
{
    shader_Light.bind();
    shader_Light.setUniformValue("lightColor", u_lightColor);

    shader_Light.setUniformValue("projection", projection);
    shader_Light.setUniformValue("view", view);
    shader_Light.setUniformValue("model", model);
}
void DepthTesting::showWindow()
{
    show();
    updateDlg();
}

void DepthTesting::updateDlg()
{
    auto setVec3toUi = [&](QDoubleSpinBox* spinBox_X,QDoubleSpinBox* spinBox_Y,QDoubleSpinBox* spinBox_Z, QVector3D value){
        spinBox_X->setValue(value.x());
        spinBox_Y->setValue(value.y());
        spinBox_Z->setValue(value.z());
    };

//    setVec3toUi(ui->Pos_X_SpinBox, ui->Pos_Y_SpinBox, ui->Pos_Z_SpinBox, u_light.position);
//    setVec3toUi(ui->Light_X_SpinBox, ui->Light_Y_SpinBox, ui->Light_Z_SpinBox, u_lightColor);
//    setVec3toUi(ui->ligAm_X_SpinBox, ui->ligAm_Y_SpinBox, ui->ligAm_Z_SpinBox, u_light.ambient);
//    setVec3toUi(ui->ligDi_X_SpinBox, ui->ligDi_Y_SpinBox, ui->ligDi_Z_SpinBox, u_light.diffuse);
//    setVec3toUi(ui->ligSp_X_SpinBox, ui->ligSp_Y_SpinBox, ui->ligSp_Z_SpinBox, u_light.specular);
//    setVec3toUi(ui->Dir_X_SpinBox, ui->Dir_Y_SpinBox, ui->Dir_Z_SpinBox, u_light.direction);

//    ui->objShiny_spinBox->setValue(u_objectTex.shininess);
//    ui->objDi_comboBox->setCurrentIndex(1);
//    ui->objSp_comboBox->setCurrentIndex(1);

//    ui->ligCon_SpinBox->setValue(u_light.constant);
//    ui->ligLin_SpinBox->setValue(u_light.linear);
//    ui->ligQua_SpinBox->setValue(u_light.quadratic);
//    ui->cutOff_SpinBox->setValue(u_light.cutOff);
//    ui->outerCutOff_SpinBox->setValue(u_light.outerCutOff);
}

void DepthTesting::initSigSlot()
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

//    QObject::connect(ui->objShiny_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int arg){
//        u_objectTex.shininess = arg;
//    });

//    connectVec3(ui->Pos_X_SpinBox, ui->Pos_Y_SpinBox,ui->Pos_Z_SpinBox, u_light.position);
//    connectVec3(ui->Light_X_SpinBox, ui->Light_Y_SpinBox,ui->Light_Z_SpinBox, u_lightColor);

//    QObject::connect(ui->objDi_comboBox, &QComboBox::currentTextChanged, this, [&](QString name) {
//        if(name == "无") {
//            u_objectTex.diffuseTexID = 100; // 无效ID
//        }else{
//            u_objectTex.diffuseTexID = PointLightTexID10::texConrainerDiffuse10;
//        }
//    });

//    QObject::connect(ui->objSp_comboBox, &QComboBox::currentTextChanged, this, [&](QString name) {
//        if(name == "无") {
//            u_objectTex.specularTexID = 100; // 无效ID
//        }else if (name == "container2_specular"){
//            u_objectTex.specularTexID = PointLightTexID10::texConrainerSpecular10;
//        }else {
//            u_objectTex.specularTexID = PointLightTexID10::texConrainerSpecularColor10;
//        }
//    });


//    connectVec3(ui->ligAm_X_SpinBox, ui->ligAm_Y_SpinBox,ui->ligAm_Z_SpinBox, u_light.ambient);
//    connectVec3(ui->ligDi_X_SpinBox, ui->ligDi_Y_SpinBox,ui->ligDi_Z_SpinBox, u_light.diffuse);
//    connectVec3(ui->ligSp_X_SpinBox, ui->ligSp_Y_SpinBox,ui->ligSp_Z_SpinBox, u_light.specular);
//    connectVec3(ui->Dir_X_SpinBox, ui->Dir_Y_SpinBox,ui->Dir_Z_SpinBox, u_light.direction);

//    QObject::connect(ui->ligCon_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
//        u_light.constant = arg;
//    });
//    QObject::connect(ui->ligLin_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
//        u_light.linear = arg;
//    });
//    QObject::connect(ui->ligQua_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
//        u_light.quadratic = arg;
//    });

//    QObject::connect(ui->cutOff_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
//        u_light.cutOff = arg;
//    });

//    QObject::connect(ui->outerCutOff_SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double arg){
//        u_light.outerCutOff = arg;
//    });
}
