#include "blending.h"
#include "ui_blending.h"

#include <QComboBox>

Blending::Blending(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Blending)
{
    ui->setupUi(this);

    srcBlending = BlendingType::SRC_ALPHA;
    desBlending = BlendingType::ONE_MINUS_SRC_ALPHA;

    specularTexID = 0;

    initSigSlot();
}

Blending::~Blending()
{
    delete ui;
}

void Blending::initTexture()
{
    cubeTextures.clear();
    // 按照编号 0 1 2 ... 放到CPU
    // TODO: 编号应该是整个在OpenGl中的所有的texture，所以需要看下之前有没有贴图初始化，如果有的话，编号对应会顺延
    blendingSpecular = new QOpenGLTexture(QImage("../07-blending/img/blending_transparent_window.png"));

    Texture tex;
    tex.path = "../07-blending/img/blending_transparent_window.png";
    tex.id = blendingSpecular->textureId();
    tex.type = "texture_specular";
    cubeTextures.push_back(tex);
}

void Blending::initShader() {
    // shader
    bool success;

    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Fragment,"../07-blending/shader/shapes.frag");
    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Vertex,"../07-blending/shader/shapes.vert");
    success = shader_Shape.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Shape.log();
    }
    updateBlendingShader();
}

void Blending::updateBlendingShader() {
    shader_Shape.bind();

    // MVP
    shader_Shape.setUniformValue("texture_diffuse1", specularTexID);
    shader_Shape.setUniformValue("projection", projection);
    shader_Shape.setUniformValue("view", view);
    shader_Shape.setUniformValue("model", model);
}

void Blending::showWindow()
{
    show();
    updateDlg();
}

void Blending::updateDlg()
{
    ui->srcBlending_comboBox->setCurrentIndex(4);
    ui->desBlending_comboBox->setCurrentIndex(5);
}

void Blending::initSigSlot()
{
    QObject::connect(ui->srcBlending_comboBox, &QComboBox::currentTextChanged, this, [&](QString name) {
        if(name == "ZERO") {
            srcBlending = BlendingType::ZERO;
        }else if(name == "ONE"){
            srcBlending = BlendingType::ONE;
        }else if(name == "SRC_COLOR"){
            srcBlending = BlendingType::SRC_COLOR;
        }else if(name == "ONE_MINUS_SRC_COLOR"){
            srcBlending = BlendingType::ONE_MINUS_SRC_COLOR;
        }else if(name == "SRC_ALPHA"){
            srcBlending = BlendingType::SRC_ALPHA;
        }else if(name == "ONE_MINUS_SRC_ALPHA"){
            srcBlending = BlendingType::ONE_MINUS_SRC_ALPHA;
        }else if(name == "DST_ALPHA"){
            srcBlending = BlendingType::DST_ALPHA;
        }else {
            srcBlending = BlendingType::ONE_MINUS_DST_ALPHA;
        }
    });

    QObject::connect(ui->desBlending_comboBox, &QComboBox::currentTextChanged, this, [&](QString name) {
        if(name == "ZERO") {
            desBlending = BlendingType::ZERO;
        }else if(name == "ONE"){
            desBlending = BlendingType::ONE;
        }else if(name == "SRC_COLOR"){
            desBlending = BlendingType::SRC_COLOR;
        }else if(name == "ONE_MINUS_SRC_COLOR"){
            desBlending = BlendingType::ONE_MINUS_SRC_COLOR;
        }else if(name == "SRC_ALPHA"){
            desBlending = BlendingType::SRC_ALPHA;
        }else if(name == "ONE_MINUS_SRC_ALPHA"){
            desBlending = BlendingType::ONE_MINUS_SRC_ALPHA;
        }else if(name == "DST_ALPHA"){
            desBlending = BlendingType::DST_ALPHA;
        }else {
            desBlending = BlendingType::ONE_MINUS_DST_ALPHA;
        }
    });
}
