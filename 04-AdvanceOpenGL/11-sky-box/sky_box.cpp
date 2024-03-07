#include "sky_box.h"
#include "ui_sky_box.h"

float skyboxVertices_11[] = {
    // positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};


SkyBox::SkyBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SkyBox)
{
    ui->setupUi(this);
    diffuseTexID = 0;

    // 位置
    u_lightPos ={1.2f, 1.0f, 2.0f};
    u_viewPos = {0.0f,0.0f,5.0f};

    // 材质的反射强度
    u_objectTex.diffuseTexID = 0;
    u_objectTex.specularTexID = 1;
    u_objectTex.reflectTexID = 2;
    u_objectTex.shininess = 32.0f;

    // 光源环境光分量
    u_lightTex.diffuse = QVector3D(0.9f, 0.9f, 0.9f);
    // 光源漫反射分量: 在环境光的基础上有一定的损失，因此需要环境光乘以一个0.2
    u_lightTex.ambient = QVector3D(0.9f, 0.9f, 0.9f);
    // 光源镜面反射分量
    u_lightTex.specular = QVector3D(1.0f, 1.0f, 1.0f);
    u_lightTex.direction = {-0.2f, -1.0f, -0.3f};

    currentStatus = SkyScene::Normal;

    initSigSlot();
}

SkyBox::~SkyBox()
{
    delete ui;
}

void SkyBox::initShader() {
    // shader
    bool success;
    shader_skyBox.addShaderFromSourceFile(QOpenGLShader::Fragment,"../11-sky-box/shader/skybox.frag");
    shader_skyBox.addShaderFromSourceFile(QOpenGLShader::Vertex,"../11-sky-box/shader/skybox.vert");
    success = shader_skyBox.link();
    if(!success) {
        qDebug() << "ERR:" << shader_skyBox.log();
    }
    updateSkyBoxShader();

    shader_reflect.addShaderFromSourceFile(QOpenGLShader::Fragment,"../11-sky-box/shader/reflection.frag");
    shader_reflect.addShaderFromSourceFile(QOpenGLShader::Vertex,"../11-sky-box/shader/reflection.vert");
    success = shader_reflect.link();
    if(!success) {
        qDebug() << "ERR:" << shader_reflect.log();
    }
    updateReflectShader();

    // shader_refract
    shader_refract.addShaderFromSourceFile(QOpenGLShader::Fragment,"../11-sky-box/shader/refraction.frag");
    shader_refract.addShaderFromSourceFile(QOpenGLShader::Vertex,"../11-sky-box/shader/refraction.vert");
    success = shader_refract.link();
    if(!success) {
        qDebug() << "ERR:" << shader_refract.log();
    }
    updateRefractShader();

    // shader_reflectTex
    shader_reflectTex.addShaderFromSourceFile(QOpenGLShader::Fragment,"../11-sky-box/shader/reflect-tex.frag");
    shader_reflectTex.addShaderFromSourceFile(QOpenGLShader::Vertex,"../11-sky-box/shader/reflect-tex.vert");
    success = shader_reflectTex.link();
    if(!success) {
        qDebug() << "ERR:" << shader_reflectTex.log();
    }
    updateReflectTexShader();
}

void SkyBox::initCubeMapTex()
{
    m_CubeMap = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
    QImage _right   = QImage("../11-sky-box/img/skybox/right.jpg").convertToFormat(QImage::Format_RGB888);
    QImage _left    = QImage("../11-sky-box/img/skybox/left.jpg").convertToFormat(QImage::Format_RGB888);
    QImage _top     = QImage("../11-sky-box/img/skybox/top.jpg").convertToFormat(QImage::Format_RGB888);
    QImage _bottom  = QImage("../11-sky-box/img/skybox/bottom.jpg").convertToFormat(QImage::Format_RGB888);
    QImage _front   = QImage("../11-sky-box/img/skybox/front.jpg").convertToFormat(QImage::Format_RGB888);
    QImage _back    = QImage("../11-sky-box/img/skybox/back.jpg").convertToFormat(QImage::Format_RGB888);
    m_CubeMap->setSize(_right.width(), _right.height());
    m_CubeMap->setFormat(QOpenGLTexture::RGBFormat);
    m_CubeMap->allocateStorage(QOpenGLTexture::RGB, QOpenGLTexture::UInt8);
    m_CubeMap->setData(0, 0, QOpenGLTexture::CubeMapPositiveX,QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void *)_right.bits());
    m_CubeMap->setData(0, 0, QOpenGLTexture::CubeMapNegativeX,QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void *)_left.bits());
    m_CubeMap->setData(0, 0, QOpenGLTexture::CubeMapPositiveY,QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void *)_top.bits());
    m_CubeMap->setData(0, 0, QOpenGLTexture::CubeMapNegativeY,QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void *)_bottom.bits());
    m_CubeMap->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ,QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void *)_front.bits());
    m_CubeMap->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ,QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void *)_back.bits());

    m_CubeMap->setMinificationFilter(QOpenGLTexture::Linear);     //纹理放大或缩小时，像素的取值方法 ，线性或就近抉择
    m_CubeMap->setMagnificationFilter(QOpenGLTexture::Linear);
    m_CubeMap->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);   //设置纹理边缘的扩展方法
    m_CubeMap->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);
}

void SkyBox::initSkyBoxVAO(QOpenGLFunctions_3_3_Core *openGLFun) {
    // skybox VAO
    openGLFun->glGenVertexArrays(1, &VAO_SkyBox);
    openGLFun->glGenBuffers(1, &VBO_SkyBox);
    openGLFun->glBindVertexArray(VAO_SkyBox);
    openGLFun->glBindBuffer(GL_ARRAY_BUFFER, VBO_SkyBox);
    openGLFun->glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices_11), &skyboxVertices_11, GL_STATIC_DRAW);
    openGLFun->glEnableVertexAttribArray(0);
    openGLFun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void SkyBox::drawSkyBox(QOpenGLFunctions_3_3_Core *openGLFun) {
    // draw skybox as last

    // skybox cube
    openGLFun->glBindVertexArray(VAO_SkyBox);
    openGLFun->glActiveTexture(GL_TEXTURE0);
    openGLFun->glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMap->textureId());
    openGLFun->glDrawArrays(GL_TRIANGLES, 0, 36);
    openGLFun->glBindVertexArray(0);
    openGLFun->glDepthFunc(GL_LESS); // set depth function back to default
    shader_skyBox.release();
}

void SkyBox::updateReflectTexShader() {
    shader_reflectTex.bind();
    // viewPos
    shader_reflectTex.setUniformValue("viewPos", u_viewPos);
    // lightPos
    shader_reflectTex.setUniformValue("lightPos", u_lightPos);
    // material
    shader_reflectTex.setUniformValue("material.texture_diffuse1", u_objectTex.diffuseTexID);  // 对应纹理编号 0
    shader_reflectTex.setUniformValue("material.texture_specular1", u_objectTex.specularTexID); // 对应纹理编号 1
    shader_reflectTex.setUniformValue("material.texture_reflection1", u_objectTex.reflectTexID); // 对应纹理编号 2 反射纹理
    shader_reflectTex.setUniformValue("material.shininess", u_objectTex.shininess);
    // light
    shader_reflectTex.setUniformValue("light.ambient", u_lightTex.ambient);
    shader_reflectTex.setUniformValue("light.diffuse", u_lightTex.diffuse);
    shader_reflectTex.setUniformValue("light.specular", u_lightTex.specular);
    shader_reflectTex.setUniformValue("light.direction", u_lightTex.direction);
    // MVP
    shader_reflectTex.setUniformValue("projection", projection);
    shader_reflectTex.setUniformValue("view", view);
    shader_reflectTex.setUniformValue("model", model);
}

void SkyBox::updateSkyBoxShader() {
    shader_skyBox.bind();

    // MVP
    shader_skyBox.setUniformValue("texture_diffuse1", diffuseTexID);
    shader_skyBox.setUniformValue("projection", projection);
    shader_skyBox.setUniformValue("view", view);
    shader_skyBox.setUniformValue("model", model);
}

void SkyBox::updateReflectShader() {
    shader_reflect.bind();

    // MVP
    shader_reflect.setUniformValue("viewPos", viewPos);
    shader_reflect.setUniformValue("projection", projection);
    shader_reflect.setUniformValue("view", view);
    shader_reflect.setUniformValue("model", model);
}

void SkyBox::updateRefractShader() {
    shader_refract.bind();

    // MVP
    shader_refract.setUniformValue("viewPos", viewPos);
    shader_refract.setUniformValue("projection", projection);
    shader_refract.setUniformValue("view", view);
    shader_refract.setUniformValue("model", model);
}


void SkyBox::showWindow()
{
    show();
    updateDlg();
}

void SkyBox::updateDlg()
{
    ui->skyBox_comboBox->setCurrentIndex(0);
}

void SkyBox::initSigSlot()
{
    QObject::connect(ui->skyBox_comboBox, &QComboBox::currentTextChanged, this, [&](QString name) {
        if(name == "无效果(Normal)") {
            currentStatus = SkyScene::Normal;
        }else if(name == "整个模型反射(reflect)") {
            currentStatus = SkyScene::Reflect;
        }else if(name == "整个模型折射(refract)") {
            currentStatus = SkyScene::Refract;
        }else{ // 纹理反射(reflectTex)
            currentStatus = SkyScene::ReflectTex;
        }
    });
}
