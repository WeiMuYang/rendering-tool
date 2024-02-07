#ifndef MULT_LIGHT_H
#define MULT_LIGHT_H

#include <QDialog>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QMatrix4x4>
#include <QOpenGLTexture>

namespace Ui {
class MultLight;
}

struct ShapeMaterial {
    // ambient和diffuse的取值一样，因此不用特意的添加ambient的纹理
    unsigned int diffuseTexID;
    unsigned int specularTexID;
    float shininess;
};

struct MultSpotLight {  //聚光灯
    QVector3D color;
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;

    // 计算光源衰减
    float constant;
    float linear;
    float quadratic;

    QVector3D position;
    // 聚光灯方向
    QVector3D direction;
    // 投射的圆锥的角度
    float cutOff;
    // 投射的圆锥外围模糊的角度
    float outerCutOff;
};

struct MultDirLight {  // 平行光
    QVector3D color;
    QVector3D direction;
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
};

struct MultPointLight { // 点光源
    QVector3D color;
    QVector3D position;
    float constant;
    float linear;
    float quadratic;
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
};

enum MltiLightTexID{
    texConrainerDiffuse11 = 0,
    texConrainerSpecular11 = 1,
    texConrainerSpecularColor11 = 2,
};

class MultLight : public QDialog
{
    Q_OBJECT

public:
    explicit MultLight(QWidget *parent = nullptr);
    ~MultLight();

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
    QVector3D u_viewPos;
    ShapeMaterial u_objectTex;
    MultSpotLight u_spotLight[2];
    MultDirLight u_parallelLight;
    MultPointLight u_pointLight[2];

    void updateShapeShader();
    void updateLightShader();

    void showWindow();
    void updateDlg();
    float angle2RadiansCos(float deg);

private:
    Ui::MultLight *ui;
};

#endif // MULT_LIGHT_H
