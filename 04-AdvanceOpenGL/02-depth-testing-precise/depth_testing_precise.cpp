#include "depth_testing_precise.h"
#include "ui_depth_testing_precise.h"

DepthTestingPrecise::DepthTestingPrecise(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DepthTestingPrecise)
{
    ui->setupUi(this);

    u_viewPos = {0.0f,0.0f,5.0f};

    initSigSlot();
}

DepthTestingPrecise::~DepthTestingPrecise()
{
    delete ui;
}

void DepthTestingPrecise::initShader() {
    // shader
    bool success;

    shader_Shape_NotLinear.addShaderFromSourceFile(QOpenGLShader::Fragment,"../02-depth-testing-precise/shader/shapes-not-linear.frag");
    shader_Shape_NotLinear.addShaderFromSourceFile(QOpenGLShader::Vertex,"../02-depth-testing-precise/shader/shapes-not-linear.vert");
    success = shader_Shape_NotLinear.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Shape_NotLinear.log();
    }
    current_Shader_Shape = &shader_Shape_NotLinear;

    shader_Shape_Linear.addShaderFromSourceFile(QOpenGLShader::Fragment,"../02-depth-testing-precise/shader/shapes-linear.frag");
    shader_Shape_Linear.addShaderFromSourceFile(QOpenGLShader::Vertex,"../02-depth-testing-precise/shader/shapes-linear.vert");
    success = shader_Shape_Linear.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Shape_Linear.log();
    }
}

void DepthTestingPrecise::showWindow()
{
    show();
    updateDlg();
}

void DepthTestingPrecise::updateDlg()
{
    ui->depthTestingPrecise_comboBox->setCurrentIndex(0);
}

void DepthTestingPrecise::initSigSlot()
{
    QObject::connect(ui->depthTestingPrecise_comboBox, &QComboBox::currentTextChanged, this, [&](QString name) {
        // NEVER, LESS, EQUAL, LEQUAL, GREATER, NOTEQUAL, GEQUAL, ALWAYS
        if(name == "Linear") {
            current_Shader_Shape = &shader_Shape_Linear;
        }else
            current_Shader_Shape = &shader_Shape_NotLinear;
    });
}

void DepthTestingPrecise::updateShapeShader() {
    current_Shader_Shape->bind();

//    current_Shader_Shape.setUniformValue("viewPos", u_viewPos);
    // MVP
    current_Shader_Shape->setUniformValue("projection", projection);
    current_Shader_Shape->setUniformValue("view", view);
    current_Shader_Shape->setUniformValue("model", model);
}
