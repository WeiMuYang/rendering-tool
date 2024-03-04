#include "frame_buffer.h"
#include "ui_frame_buffer.h"

float frameBufferVertices_09[] = {
    // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
    0.0f,  -2.5f,  0.0f,  0.0f,  0.0f,
    0.0f, 2.5f,  0.0f,  0.0f,  1.0f,
    5.0f, 2.5f,  0.0f,  1.0f,  1.0f,

    0.0f,  -2.5f,  0.0f,  0.0f,  0.0f,
    5.0f, 2.5f,  0.0f,  1.0f,  1.0f,
    5.0f,  -2.5f,  0.0f,  1.0f,  0.0f
};

FrameBuffer::FrameBuffer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrameBuffer)
{
    ui->setupUi(this);
    int size = sizeof(frameBufferVertices_09) / sizeof(float);
    for (int i = 0; i < size; i++) {
        frameBufferVertices.push_back(frameBufferVertices_09[i]);
    }
    frameBufferVerCount = 6;
    diffuseTexID = 0;

    initSigSlot();
}

void FrameBuffer::initShader() {
    // shader
    bool success;

    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Fragment,"../09-frame-buffer/shader/shapes.frag");
    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Vertex,"../09-frame-buffer/shader/shapes.vert");
    success = shader_Shape.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Shape.log();
    }
    updateFrameBufferShader();
}

void FrameBuffer::initFrameBufferTex(QOpenGLFunctions_3_3_Core * openGLFun, int width, int height)
{
    m_glFuns = openGLFun;

    // 创建一个自定义的帧缓冲
    m_glFuns->glGenFramebuffers(1, &fbo);
    m_glFuns->glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // 创建一个纹理并
    m_glFuns->glGenTextures(1, &texture);
    m_glFuns->glBindTexture(GL_TEXTURE_2D, texture);
    m_glFuns->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    m_glFuns->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_glFuns->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 作为帧缓冲的附件
    m_glFuns->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    // 创建深度、模板缓冲对象，使用渲染缓冲对象
    m_glFuns->glGenRenderbuffers(1, &rbo);
    m_glFuns->glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    // 指定存储在 renderbuffer 中图像的宽高以及颜色格式，并按照此规格为之分配存储空间
    m_glFuns->glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

    // 最后一件事就是附加这个渲染缓冲对象
    m_glFuns->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    // 善后工作
    if (m_glFuns->glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        qDebug() << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;


    Texture tex;
    tex.id = texture;
    tex.path = "";
    tex.type = "texture_diffuse";
    FrameBufferTex.push_back(tex);
}

void FrameBuffer::updateFrameBufferShader() {
    shader_Shape.bind();

    // MVP
    shader_Shape.setUniformValue("texture_diffuse1", texture);
    shader_Shape.setUniformValue("projection", projection);
    shader_Shape.setUniformValue("view", view);
    shader_Shape.setUniformValue("model", model);
}

FrameBuffer::~FrameBuffer()
{
    delete ui;
}

void FrameBuffer::showWindow()
{
    show();
    updateDlg();
}

void FrameBuffer::updateDlg()
{
    ui->useFrameBuffer_comboBox->setCurrentIndex(0);
}

void FrameBuffer::initSigSlot()
{
    QObject::connect(ui->useFrameBuffer_comboBox, &QComboBox::currentTextChanged, this, [&](QString name) {
        if(name == "true") {
            isFrameBuffer = true;
        }else {
            isFrameBuffer = false;;
        }
    });
}

