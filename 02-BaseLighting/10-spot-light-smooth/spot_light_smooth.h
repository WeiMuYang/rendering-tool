#ifndef SPOT_LIGHT_SMOOTH_H
#define SPOT_LIGHT_SMOOTH_H

#include <QDialog>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QMatrix4x4>
#include <QOpenGLTexture>

namespace Ui {
class SpotLightSmooth;
}

struct TexShapeMaterial10 {
    // ambient和diffuse的取值一样，因此不用特意的添加ambient的纹理
    unsigned int diffuseTexID;
    unsigned int specularTexID;
    float shininess;
};

struct LightMaterial10 {
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

enum PointLightTexID10{
    texConrainerDiffuse10 = 0,
    texConrainerSpecular10 = 1,
    texConrainerSpecularColor10 = 2,
};

class SpotLightSmooth : public QDialog
{
    Q_OBJECT

public:
    explicit SpotLightSmooth(QWidget *parent = nullptr);
    ~SpotLightSmooth();
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
    TexShapeMaterial10 u_objectTex;
    LightMaterial10 u_light;

    void updateShapeShader();
    void updateLightShader();

    void showWindow();
    void updateDlg();
    void initSigSlot();
    float angle2RadiansCos(float deg);

private:
    Ui::SpotLightSmooth *ui;
};

#endif // SPOT_LIGHT_SMOOTH_H
