#ifndef TEXTURELIGHT_H
#define TEXTURELIGHT_H

#include <QObject>
#include <QDialog>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include "../vertices.h"

struct TexShapeMaterial {
    // ambient和diffuse的取值一样，因此不用特意的添加ambient的纹理
    unsigned int diffuseTexNum;
    unsigned int specularTexNum;
    unsigned int emissionTexNum;      // 自发光效果
    float shininess;
};

struct TexLightMaterial {
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
};



namespace Ui {
class TextureLight;
}

class TextureLight : public QDialog
{
    Q_OBJECT

public:
    explicit TextureLight(QWidget *parent = nullptr);
    ~TextureLight();

    Vertices box3D;

    void initShader() ;
    void initTexture() ;
    void setShader(QString name, QVector3D value);

    QOpenGLShaderProgram shader_Light;
    QOpenGLShaderProgram shader_Shape;

    QOpenGLTexture* texConrainerDiffuse;
    QOpenGLTexture* texConrainerSpecular;
    QOpenGLTexture* texConrainerSpecularColor;
    QOpenGLTexture* texConrainerMat;  // 自发光纹理


    // 光线的颜色
    QVector3D lightColor;

    // 镜头相关
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    // 光照相关
    QVector3D lightPos;
    QVector3D viewPos;
    TexShapeMaterial objectMaterial;
    TexLightMaterial light;

    void updateShapeShader();
    void updateLightShader();

private:
    Ui::TextureLight *ui;
};


#endif // TEXTURELIGHT_H
