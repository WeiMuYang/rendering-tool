#ifndef DEPTH_TESTING_H
#define DEPTH_TESTING_H

#include <QDialog>

#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QOpenGLTexture>

#include "mesh.h"



struct Box3DShapeMaterial {
    // ambient和diffuse的取值一样，因此不用特意的添加ambient的纹理
    unsigned int diffuseTexID;
    unsigned int specularTexID;
    float shininess;
};

struct Box3DLightMaterial {
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
    QVector3D direction;
};

namespace Ui {
class DepthTesting;
}

class DepthTesting : public QDialog
{
    Q_OBJECT

public:
    explicit DepthTesting(QWidget *parent = nullptr);
    ~DepthTesting();

    std::vector<float> cubeVertices;
    unsigned int cubeVerCount;
    std::vector<Texture> cubeTextures;
    std::vector<float> planeVertices;
    unsigned int planeVerCount;
    std::vector<Texture> planeTextures;

    void initShader() ;
    void initTexture() ;
    void setShader(QString name, QVector3D value);

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
    QVector3D u_lightPos;
    QVector3D u_viewPos;
    Box3DShapeMaterial u_objectTex;
    Box3DLightMaterial u_lightTex;

    void updateShapeShader();
    void updateLightShader();

    void showWindow();
    void updateDlg();
    void initSigSlot();

private:
    Ui::DepthTesting *ui;
};

#endif // DEPTH_TESTING_H
