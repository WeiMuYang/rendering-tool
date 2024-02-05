#ifndef PARALLEL_LIGHT_H
#define PARALLEL_LIGHT_H

#include <QDialog>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QMatrix4x4>
#include <QOpenGLTexture>

static  QVector3D ParallelLightCubePositions[] = {
    QVector3D( 0.0f, 0.0f, 0.0f),
    QVector3D( 2.0f, 5.0f, -15.0f),
    QVector3D(-1.5f, -2.2f, -2.5f),
    QVector3D(-3.8f, -2.0f, -12.3f),
    QVector3D( 2.4f, -0.4f, -3.5f),
    QVector3D(-1.7f, 3.0f, -7.5f),
    QVector3D( 1.3f, -2.0f, -2.5f),
    QVector3D( 1.5f, 2.0f, -2.5f),
    QVector3D( 1.5f, 0.2f, -1.5f),
    QVector3D(-1.3f, 1.0f, -1.5f)
};

struct TexShapeMaterial07 {
    // ambient和diffuse的取值一样，因此不用特意的添加ambient的纹理
    unsigned int diffuseTexID;
    unsigned int specularTexID;
    unsigned int emissionTexID;      // 自发光效果
    float shininess;
};

struct TexLightMaterial07 {
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
};


namespace Ui {
class Parallel_Light;
}

enum ParallelLightTexID{
    texConrainerDiffuse07 = 0,
    texConrainerSpecular07 = 1,
    texConrainerSpecularColor07 = 2,
    texConrainerMat07 = 3
};

class Parallel_Light : public QDialog
{
    Q_OBJECT

public:
    explicit Parallel_Light(QWidget *parent = nullptr);
    ~Parallel_Light();

    void initShader() ;
    void initTexture() ;

    QOpenGLShaderProgram shader_Light;
    QOpenGLShaderProgram shader_Shape;

    QOpenGLTexture* texConrainerDiffuse;
    QOpenGLTexture* texConrainerSpecular;
    QOpenGLTexture* texConrainerSpecularColor;
    QOpenGLTexture* texConrainerMat;  // 自发光纹理

    // 光线的颜色
    QVector3D u_lightColor;

    // 镜头相关
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    // 光照相关
    QVector3D u_lightDirection; // 只需要方向即可
    QVector3D u_viewPos;
    TexShapeMaterial07 u_objectTex;
    TexLightMaterial07 u_lightTex;

    void updateShapeShader();
    void updateLightShader();

    void showWindow();
    void updateDlg();
    void initSigSlot();

private:
    Ui::Parallel_Light *ui;
};

#endif // PARALLEL_LIGHT_H
