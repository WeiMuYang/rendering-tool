#ifndef POST_PROCESSING_H
#define POST_PROCESSING_H

#include <QDialog>

#include <QObject>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QOpenGLTexture>

namespace Ui {
class PostProcessing;
}

class PostProcessing : public QDialog
{
    Q_OBJECT

public:
    explicit PostProcessing(QWidget *parent = nullptr);
    ~PostProcessing();

    void initShader() ;

    QOpenGLShaderProgram shader_Inversion;  // 反相
    QOpenGLShaderProgram shader_Grayscale;  // 灰度化
    QOpenGLShaderProgram shader_Weighted;   // 加权的
    QOpenGLShaderProgram shader_Sharpen;    // 核效果 锐化(Sharpen)
    QOpenGLShaderProgram shader_Blur;       // 核效果  模糊(Blur)

    QOpenGLShaderProgram* currentShader;

    // 镜头相关
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    unsigned int diffuseTexID;

    void updateShader();

    void showWindow();
    void updateDlg();
    void initSigSlot();

private:
    Ui::PostProcessing *ui;
};

#endif // POST_PROCESSING_H
