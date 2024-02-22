#include "mouse_picking.h"
#include "ui_mouse_picking.h"

MousePicking::MousePicking(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MousePicking)
{
    ui->setupUi(this);

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

MousePicking::~MousePicking()
{
    delete ui;
}

void MousePicking::initShader() {
    // shader
    bool success;
    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Fragment,"../03-mouse-picking/shader/shapes.frag");
    shader_Shape.addShaderFromSourceFile(QOpenGLShader::Vertex,"../03-mouse-picking/shader/shapes.vert");
    success = shader_Shape.link();
    if(!success) {
        qDebug() << "ERR:" << shader_Shape.log();
    }
    updateShapeShader();
}

void MousePicking::initTexture()
{
    // 按照编号 0 1 2 ... 放到CPU
    // TODO: 编号应该是整个在OpenGl中的所有的texture，所以需要看下之前有没有贴图初始化，如果有的话，编号对应会顺延
    texConrainerDiffuse = new QOpenGLTexture(QImage("../03-mouse-picking/img/container2.png").mirrored());
    texConrainerSpecular = new QOpenGLTexture(QImage("../03-mouse-picking/img/matrix.jpg").mirrored());
}

void MousePicking::updateShapeShader() {
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
}

void MousePicking::showWindow()
{
    show();
    updateDlg();
}

void MousePicking::updateDlg()
{
    auto float2QString = [&](float value) {
        QString result = QString::number(value, 'f', 2);
        return result;
    };

    auto vec22QString = [&](QVector2D value ) {
        QString result = " x: " + QString::number(value.x(), 'f', 2) + " y: " + QString::number(value.y(), 'f', 2);
        return result;
    };

    auto vec42QString = [&](QVector4D value ) {
        QString result = " x: " + QString::number(value.x(), 'f', 2) + " y: " + QString::number(value.y(), 'f', 2) +
                         " z: " + QString::number(value.z(), 'f', 2) + " w: " + QString::number(value.w(), 'f', 2);
        return result;
    };

    ui->clickPos->setText(vec22QString(pickingPixelData.MousePressPos));
    ui->pixelZ->setText(float2QString(pickingPixelData.PixelZ));
    ui->ViewPos2ClickPosW->setText(float2QString(pickingPixelData.PixelW));
    ui->ClipPos->setText(vec42QString(pickingPixelData.ClipPos));
    ui->WorldPos->setText(vec42QString(pickingPixelData.WorldPos));
}


