#ifndef SKY_BOX_H
#define SKY_BOX_H

#include <QDialog>

#include <QObject>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <QOpenGLFunctions_3_3_Core>

namespace Ui {
class SkyBox;
}

class SkyBox : public QDialog
{
    Q_OBJECT

public:
    explicit SkyBox(QWidget *parent = nullptr);
    ~SkyBox();

//    std::vector<float> skyboxVertices;
//    unsigned int skyboxVerCount;

    unsigned int VAO_SkyBox;
    unsigned int VBO_SkyBox;

    void initShader();
    void initCubeMapTex();

//    QOpenGLShaderProgram shader_shapes; // 无折射和反射效果
    QOpenGLShaderProgram shader_skyBox; // 天空盒子
    QOpenGLTexture * m_CubeMap;

    // 镜头相关
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    unsigned int diffuseTexID;

    void showWindow();
    void updateDlg();
    void initSigSlot();

    void updateShapesShader();
    void updateSkyBoxShader();
    void drawSkyBox(QOpenGLFunctions_3_3_Core *openGLFun);
    void initSkyBoxVAO(QOpenGLFunctions_3_3_Core *openGLFun);
private:
    Ui::SkyBox *ui;
};

#endif // SKY_BOX_H
