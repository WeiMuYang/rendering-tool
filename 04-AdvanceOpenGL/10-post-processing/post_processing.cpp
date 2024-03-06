#include "post_processing.h"
#include "ui_post_processing.h"

PostProcessing::PostProcessing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PostProcessing)
{
    ui->setupUi(this);
    diffuseTexID = 0;
    initSigSlot();
}

PostProcessing::~PostProcessing()
{
    delete ui;
}

void PostProcessing::initShader() {
    // shader
    bool success;

    shader_Inversion.addShaderFromSourceFile(QOpenGLShader::Fragment,"../10-post-processing/shader/inversion.frag");
    shader_Inversion.addShaderFromSourceFile(QOpenGLShader::Vertex,"../10-post-processing/shader/shapes.vert");
    success = shader_Inversion.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Inversion.log();
    }
    currentShader = &shader_Inversion;
    updateShader();

    shader_Grayscale.addShaderFromSourceFile(QOpenGLShader::Fragment,"../10-post-processing/shader/grayscale.frag");
    shader_Grayscale.addShaderFromSourceFile(QOpenGLShader::Vertex,"../10-post-processing/shader/shapes.vert");
    success = shader_Grayscale.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Grayscale.log();
    }
    currentShader = &shader_Grayscale;
    updateShader();

    shader_Weighted.addShaderFromSourceFile(QOpenGLShader::Fragment,"../10-post-processing/shader/weighted.frag");
    shader_Weighted.addShaderFromSourceFile(QOpenGLShader::Vertex,"../10-post-processing/shader/shapes.vert");
    success = shader_Weighted.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Weighted.log();
    }
    currentShader = &shader_Weighted;
    updateShader();

    shader_Sharpen.addShaderFromSourceFile(QOpenGLShader::Fragment,"../10-post-processing/shader/sharpen.frag");
    shader_Sharpen.addShaderFromSourceFile(QOpenGLShader::Vertex,"../10-post-processing/shader/shapes.vert");
    success = shader_Sharpen.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Sharpen.log();
    }
    currentShader = &shader_Sharpen;
    updateShader();

    shader_Blur.addShaderFromSourceFile(QOpenGLShader::Fragment,"../10-post-processing/shader/blur.frag");
    shader_Blur.addShaderFromSourceFile(QOpenGLShader::Vertex,"../10-post-processing/shader/shapes.vert");
    success = shader_Blur.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Blur.log();
    }
    currentShader = &shader_Blur;
    updateShader();

    currentShader = &shader_Inversion;
}

void PostProcessing::updateShader() {
    currentShader->bind();

    // MVP
    currentShader->setUniformValue("texture_diffuse1", diffuseTexID);
    currentShader->setUniformValue("projection", projection);
    currentShader->setUniformValue("view", view);
    currentShader->setUniformValue("model", model);
}

void PostProcessing::showWindow()
{
    show();
    updateDlg();
}

void PostProcessing::updateDlg()
{
    ui->postProcess_comboBox->setCurrentIndex(0);
}

void PostProcessing::initSigSlot()
{
    QObject::connect(ui->postProcess_comboBox, &QComboBox::currentTextChanged, this, [&](QString name) {
        if(name == "反相(Inversion)") {
            currentShader = &shader_Inversion;
        }else if(name == "灰度化(Grayscale)") {
            currentShader = &shader_Grayscale;
        }else if(name == "加权的(Weighted)") {
            currentShader = &shader_Weighted;
        }else if(name == "锐化(Sharpen)") {
            currentShader = &shader_Sharpen;
        }else{ // 模糊(Blur)
            currentShader = &shader_Blur;
        }
    });
}
