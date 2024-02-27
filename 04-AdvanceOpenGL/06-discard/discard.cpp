#include "discard.h"

float grassVertices_06[] = {
    // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
    0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
    0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
    1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

    0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
    1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
    1.0f,  0.5f,  0.0f,  1.0f,  0.0f
};

Discard::Discard(QObject *parent)
    : QObject{parent}
{
    specularTexID = 0;

    int size = sizeof(grassVertices_06) / sizeof(float);
    for (int i = 0; i < size; i++) {
        grassVertices.push_back(grassVertices_06[i]);
    }
    grassVerCount = 6;

    vegetation.push_back(QVector3D(-1.5f, 0.0f, -0.48f));
    vegetation.push_back(QVector3D( 1.5f, 0.0f, 0.51f));
    vegetation.push_back(QVector3D( 0.0f, 0.0f, 0.7f));
    vegetation.push_back(QVector3D(-0.3f, 0.0f, -2.3f));
    vegetation.push_back(QVector3D( 0.5f, 0.0f, -0.6f));
}
void Discard::initTexture()
{

    cubeTextures.clear();
    // 按照编号 0 1 2 ... 放到CPU
    // TODO: 编号应该是整个在OpenGl中的所有的texture，所以需要看下之前有没有贴图初始化，如果有的话，编号对应会顺延
    glassSpecular = new QOpenGLTexture(QImage("../06-discard/img/grass.png"));

    Texture tex;
    tex.path = "../06-discard/img/grass.png";
    tex.id = glassSpecular->textureId();
    tex.type = "texture_specular";
    cubeTextures.push_back(tex);
}

void Discard::initShader() {
    // shader
    bool success;

    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Fragment,"../06-discard/shader/shapes.frag");
    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Vertex,"../06-discard/shader/shapes.vert");
    success = shader_Shape.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Shape.log();
    }
    updateDiscardShader();

}

void Discard::updateDiscardShader() {
    shader_Shape.bind();

    // MVP
    shader_Shape.setUniformValue("texture_diffuse1", specularTexID);
    shader_Shape.setUniformValue("projection", projection);
    shader_Shape.setUniformValue("view", view);
    shader_Shape.setUniformValue("model", model);
}
