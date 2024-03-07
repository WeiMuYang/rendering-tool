#ifndef SKY_BOX_H
#define SKY_BOX_H

#include <QDialog>

#include <QObject>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <QOpenGLFunctions_3_3_Core>

enum SkyScene{
    Normal, Reflect, Refract, ReflectTex
};

struct ModelShapeMaterial {
    // ambient和diffuse的取值一样，因此不用特意的添加ambient的纹理
    unsigned int diffuseTexID;
    unsigned int specularTexID;
    unsigned int reflectTexID;
    float shininess;
};

struct ModelLightMaterial {
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
    QVector3D direction;
};

namespace Ui {
class SkyBox;
}

class SkyBox : public QDialog
{
    Q_OBJECT

public:
    explicit SkyBox(QWidget *parent = nullptr);
    ~SkyBox();

    unsigned int VAO_SkyBox;
    unsigned int VBO_SkyBox;

    void initShader();
    void initCubeMapTex();

    QOpenGLShaderProgram shader_skyBox; // 天空盒子
    QOpenGLTexture * m_CubeMap;
    QOpenGLShaderProgram shader_reflect; // 反射效果
    QOpenGLShaderProgram shader_refract; // 折射效果
    QOpenGLShaderProgram shader_reflectTex; // 反射效果

    QVector3D viewPos;

    // 镜头相关
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    unsigned int diffuseTexID;

    // 光照相关
    QVector3D u_lightPos;
    QVector3D u_viewPos;
    ModelShapeMaterial u_objectTex;
    ModelLightMaterial u_lightTex;

    void showWindow();
    void updateDlg();
    void initSigSlot();

    void updateReflectShader();
    void updateSkyBoxShader();
    void drawSkyBox(QOpenGLFunctions_3_3_Core *openGLFun);
    void initSkyBoxVAO(QOpenGLFunctions_3_3_Core *openGLFun);
    void updateRefractShader();
    void updateReflectTexShader();

    SkyScene currentStatus;
private:
    Ui::SkyBox *ui;
};

#endif // SKY_BOX_H
