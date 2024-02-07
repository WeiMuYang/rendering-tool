#include "mult_light.h"
#include "ui_mult_light.h"

MultLight::MultLight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MultLight)
{
    ui->setupUi(this);
    // 视角的位置
    u_viewPos = {0.0f,0.0f,5.0f};

    // 材质的反射强度
    u_objectTex.diffuseTexID = 0;
    u_objectTex.specularTexID = 1;
    u_objectTex.shininess = 32.0f;

    u_lightColor ={1.0f, 1.0f, 1.0f};  //TODO
    for(int i = 0; i < 2; ++i) {
        {// spotLight
            // 光源环境光分量
            u_spotLight[i].diffuse = {0.9f, 0.9f, 0.9f};
            // 光源漫反射分量: 在环境光的基础上有一定的损失，因此需要环境光乘以一个0.2
            u_spotLight[i].ambient = {0.4f, 0.4f, 0.4f};
            // 光源镜面反射分量
            u_spotLight[i].specular = {1.0f, 1.0f, 1.0f};

            u_spotLight[i].constant = 1.0f;
            u_spotLight[i].linear = 0.09f;
            u_spotLight[i].quadratic = 0.032f;

            u_spotLight[i].direction = {0.0f, 0.0f, -1.0f};
            u_spotLight[i].position = {0.0f, 0.0f, 1.0f};
            u_spotLight[i].cutOff = 12.5f;
            u_spotLight[i].outerCutOff = 17.5f;
        }

        {// u_pointLight
//            u_pointLight[i].position = {-0.2f, -1.0f, -0.3f};
            // 光源环境光分量
            u_pointLight[i].diffuse = QVector3D(0.1,0.1,0.1);
            // 光源漫反射分量: 在环境光的基础上有一定的损失，因此需要环境光乘以一个0.2
            u_pointLight[i].ambient = QVector3D(0.1,0.1,0.1);
            // 光源镜面反射分量
            u_pointLight[i].specular = QVector3D(1.0,1.0,1.0);

            u_pointLight[i].constant = 1.0f;
            u_pointLight[i].linear = 0.09f;
            u_pointLight[i].quadratic = 0.032f;
        }
    }

    { // parallelLight
        u_parallelLight.direction ={-0.2f, -1.0f, -0.3f};
        // 光源环境光分量
        u_parallelLight.diffuse = QVector3D(0.05,0.05,0.05);
        // 光源漫反射分量: 在环境光的基础上有一定的损失，因此需要环境光乘以一个0.2
        u_parallelLight.ambient = QVector3D(0.05,0.05,0.05);
        // 光源镜面反射分量
        u_parallelLight.specular = QVector3D(0.5,0.5,0.5);
    }



    u_spotLight[0].color = {1,0,0};
    u_spotLight[1].color = {0,1,0};
    u_spotLight[0].position = {0.0f, 0.0f, 1.0f};
    u_spotLight[1].position = {1.0f, 0.0f, 0.0f};

    u_pointLight[0].color = {0,0,1};
    u_pointLight[1].color = {1,1,0};
    u_pointLight[0].position = {0.0f, 1.0f, 1.0f};
    u_pointLight[1].position = {1.0f, 1.0f, 0.0f};

//    u_parallelLight[0].color = {1,0,1};
//    u_parallelLight[1].color = {1,1,1};



//    initSigSlot();  太多了 不加界面互动了
}

MultLight::~MultLight()
{
    delete ui;
}

void MultLight::initShader() {
    // shader
    bool success;
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Fragment,"../11-mult-light/shader/light.frag");
    shader_Light.addShaderFromSourceFile(QOpenGLShader::Vertex,"../11-mult-light/shader/light.vert");
    success = shader_Light.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_Light.log();
    }
    updateLightShader();

    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Fragment,"../11-mult-light/shader/shapes.frag");
    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Vertex,"../11-mult-light/shader/shapes.vert");
    success = shader_Shape.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Shape.log();
    }
    updateShapeShader();
}

void MultLight::initTexture()
{
    // 按照编号 0 1 2 ... 放到CPU
    // TODO: 编号应该是整个在OpenGl中的所有的texture，所以需要看下之前有没有贴图初始化，如果有的话，编号对应会顺延
    texConrainerDiffuse = new QOpenGLTexture(QImage("../11-mult-light/img/container2.png").mirrored());
    texConrainerSpecular = new QOpenGLTexture(QImage("../11-mult-light/img/container2_specular.png").mirrored());
}


void MultLight::updateShapeShader() {
    shader_Shape.bind();

    // viewPos
    shader_Shape.setUniformValue("viewPos", u_viewPos);
    // material
    shader_Shape.setUniformValue("material.diffuse", u_objectTex.diffuseTexID);  // 对应纹理编号 0
    shader_Shape.setUniformValue("material.specular", u_objectTex.specularTexID); // 对应纹理编号 1
    shader_Shape.setUniformValue("material.shininess", u_objectTex.shininess);

    for(int i = 0; i < 2; ++i) {
        {  // spotLight
            // light
            QString iStr="spotLights["+QString::number(i)+"].ambient";
            shader_Shape.setUniformValue(iStr.toStdString().c_str(), u_spotLight[i].ambient);
            iStr="spotLights["+QString::number(i)+"].diffuse";
            shader_Shape.setUniformValue(iStr.toStdString().c_str(), u_spotLight[i].diffuse);
            iStr="spotLights["+QString::number(i)+"].specular";
            shader_Shape.setUniformValue(iStr.toStdString().c_str(), u_spotLight[i].specular);
            iStr="spotLights["+QString::number(i)+"].constant";
            shader_Shape.setUniformValue(iStr.toStdString().c_str(), u_spotLight[i].constant);
            iStr="spotLights["+QString::number(i)+"].linear";
            shader_Shape.setUniformValue(iStr.toStdString().c_str(), u_spotLight[i].linear);
            iStr="spotLights["+QString::number(i)+"].quadratic";
            shader_Shape.setUniformValue(iStr.toStdString().c_str(), u_spotLight[i].quadratic);
            // 聚光灯参数
            iStr="spotLights["+QString::number(i)+"].position";
            shader_Shape.setUniformValue(iStr.toStdString().c_str(), u_spotLight[i].position);
            iStr="spotLights["+QString::number(i)+"].direction";
            shader_Shape.setUniformValue(iStr.toStdString().c_str(), u_spotLight[i].direction);
            iStr="spotLights["+QString::number(i)+"].cutOff";
            shader_Shape.setUniformValue(iStr.toStdString().c_str(), angle2RadiansCos(u_spotLight[i].cutOff));
            iStr="spotLights["+QString::number(i)+"].outerCutOff";
            shader_Shape.setUniformValue(iStr.toStdString().c_str(), angle2RadiansCos(u_spotLight[i].outerCutOff));
        }
        { // PointLight
            QString iStr="pointLights["+QString::number(i)+"].ambient";
            shader_Shape.setUniformValue(iStr.toStdString().c_str(), u_pointLight[i].ambient);
            iStr="pointLights["+QString::number(i)+"].diffuse";
            shader_Shape.setUniformValue(iStr.toStdString().c_str(), u_pointLight[i].diffuse);
            iStr="pointLights["+QString::number(i)+"].specular";
            shader_Shape.setUniformValue(iStr.toStdString().c_str(), u_pointLight[i].specular);
            iStr="pointLights["+QString::number(i)+"].constant";
            shader_Shape.setUniformValue(iStr.toStdString().c_str(), u_pointLight[i].constant);
            iStr="pointLights["+QString::number(i)+"].linear";
            shader_Shape.setUniformValue(iStr.toStdString().c_str(), u_pointLight[i].linear);
            iStr="pointLights["+QString::number(i)+"].quadratic";
            shader_Shape.setUniformValue(iStr.toStdString().c_str(), u_pointLight[i].quadratic);
            iStr="pointLights["+QString::number(i)+"].position";
            shader_Shape.setUniformValue(iStr.toStdString().c_str(), u_pointLight[i].position);

        }
    }

    { // parallelLight
        shader_Shape.setUniformValue("dirLights.ambient", u_parallelLight.ambient);
        shader_Shape.setUniformValue("dirLights.diffuse", u_parallelLight.diffuse);
        shader_Shape.setUniformValue("dirLights.specular", u_parallelLight.specular);
        shader_Shape.setUniformValue("dirLights.direction", u_parallelLight.direction);
    }

    // MVP
    shader_Shape.setUniformValue("projection", projection);
    shader_Shape.setUniformValue("view", view);
    shader_Shape.setUniformValue("model", model);

    // 将纹理信息和纹理编号对应，装入GPU
    texConrainerDiffuse->bind(MltiLightTexID::texConrainerDiffuse11);
    texConrainerSpecular->bind(MltiLightTexID::texConrainerSpecular11);
}

void MultLight::updateLightShader()
{
    shader_Light.bind();
    shader_Light.setUniformValue("lightColor", u_lightColor);

    shader_Light.setUniformValue("projection", projection);
    shader_Light.setUniformValue("view", view);
    shader_Light.setUniformValue("model", model);
}

void MultLight::showWindow()
{
    show();
    updateDlg();
}

void MultLight::updateDlg()
{
    auto setVec3toUi = [&](QDoubleSpinBox* spinBox_X,QDoubleSpinBox* spinBox_Y,QDoubleSpinBox* spinBox_Z, QVector3D value){
        spinBox_X->setValue(value.x());
        spinBox_Y->setValue(value.y());
        spinBox_Z->setValue(value.z());
    };

    int i = ui->JcomboBox->currentIndex();
    setVec3toUi(ui->Pos_X_SpinBox, ui->Pos_Y_SpinBox, ui->Pos_Z_SpinBox, u_spotLight[i].position);
    setVec3toUi(ui->ligAm_X_SpinBox, ui->ligAm_Y_SpinBox, ui->ligAm_Z_SpinBox, u_spotLight[i].ambient);
    setVec3toUi(ui->ligDi_X_SpinBox, ui->ligDi_Y_SpinBox, ui->ligDi_Z_SpinBox, u_spotLight[i].diffuse);
    setVec3toUi(ui->ligSp_X_SpinBox, ui->ligSp_Y_SpinBox, ui->ligSp_Z_SpinBox, u_spotLight[i].specular);
    setVec3toUi(ui->Dir_X_SpinBox, ui->Dir_Y_SpinBox, ui->Dir_Z_SpinBox, u_spotLight[i].direction);

    ui->ligCon_SpinBox->setValue(u_spotLight[i].constant);
    ui->ligLin_SpinBox->setValue(u_spotLight[i].linear);
    ui->ligQua_SpinBox->setValue(u_spotLight[i].quadratic);
    ui->cutOff_SpinBox->setValue(u_spotLight[i].cutOff);
    ui->outerCutOff_SpinBox->setValue(u_spotLight[i].outerCutOff);


    ui->objShiny_spinBox->setValue(u_objectTex.shininess);
    ui->objDi_comboBox->setCurrentIndex(1);
    ui->objSp_comboBox->setCurrentIndex(1);
}



float MultLight::angle2RadiansCos(float deg)
{
    const double PI = 3.1415926;
    return cos(deg * PI/180);
}
