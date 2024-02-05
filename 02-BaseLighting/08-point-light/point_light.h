#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <QDialog>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QMatrix4x4>
#include <QOpenGLTexture>

namespace Ui {
class PointLight;
}

struct TexShapeMaterial08 {
    // ambient和diffuse的取值一样，因此不用特意的添加ambient的纹理
    unsigned int diffuseTexID;
    unsigned int specularTexID;
    float shininess;
};

struct LightMaterial08 {
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;

    float constant;
    float linear;
    float quadratic;
};

enum PointLightTexID{
    texConrainerDiffuse08 = 0,
    texConrainerSpecular08 = 1,
    texConrainerSpecularColor08 = 2,
    texConrainerMat08 = 3
};

class PointLight : public QDialog
{
    Q_OBJECT

public:
    explicit PointLight(QWidget *parent = nullptr);
    ~PointLight();

    void initShader() ;
    void initTexture() ;

    QOpenGLShaderProgram shader_Light;
    QOpenGLShaderProgram shader_Shape;

    QOpenGLTexture* texConrainerDiffuse;
    QOpenGLTexture* texConrainerSpecular;

    // 光线的颜色
    QVector3D u_lightColor;

    // 镜头相关
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    // 光照相关
    QVector3D u_lightPos; // 只需要方向即可
    QVector3D u_viewPos;
    TexShapeMaterial08 u_objectTex;
    LightMaterial08 u_light;

    void updateShapeShader();
    void updateLightShader();

    void showWindow();
    void updateDlg();
    void initSigSlot();

private:
    Ui::PointLight *ui;
};

#endif // POINT_LIGHT_H
