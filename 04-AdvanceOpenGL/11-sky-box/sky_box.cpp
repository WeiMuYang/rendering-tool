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

//    int size = sizeof(skyboxVertices_11) / sizeof(float);
//    for (int i = 0; i < size; i++) {
//        skyboxVertices.push_back(skyboxVertices_11[i]);
//    }
//    skyboxVerCount = 36;
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

//void SkyBox::updateShapesShader() {
//    shader_shapes.bind();

//    // MVP
//    shader_shapes.setUniformValue("texture_diffuse1", diffuseTexID);
//    shader_shapes.setUniformValue("projection", projection);
//    shader_shapes.setUniformValue("view", view);
//    shader_shapes.setUniformValue("model", model);
//}

void SkyBox::updateSkyBoxShader() {
    shader_skyBox.bind();

    // MVP
    shader_skyBox.setUniformValue("texture_diffuse1", diffuseTexID);
    shader_skyBox.setUniformValue("projection", projection);
    shader_skyBox.setUniformValue("view", view);
    shader_skyBox.setUniformValue("model", model);
}

void SkyBox::showWindow()
{
    show();
    updateDlg();
}

void SkyBox::updateDlg()
{
//    ui->postProcess_comboBox->setCurrentIndex(0);
}

void SkyBox::initSigSlot()
{
//    QObject::connect(ui->postProcess_comboBox, &QComboBox::currentTextChanged, this, [&](QString name) {
//        if(name == "反相(Inversion)") {
//            currentShader = &shader_shapes;
//        }else if(name == "灰度化(Grayscale)") {
//            currentShader = &shader_Grayscale;
//        }else if(name == "加权的(Weighted)") {
//            currentShader = &shader_Weighted;
//        }else if(name == "锐化(Sharpen)") {
//            currentShader = &shader_Sharpen;
//        }else{ // 模糊(Blur)
//            currentShader = &shader_Blur;
//        }
//    });
}
