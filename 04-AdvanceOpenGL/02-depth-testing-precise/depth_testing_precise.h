#ifndef DEPTH_TESTING_PRECISE_H
#define DEPTH_TESTING_PRECISE_H

#include <QDialog>

#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QOpenGLTexture>


namespace Ui {
class DepthTestingPrecise;
}

class DepthTestingPrecise : public QDialog
{
    Q_OBJECT

public:
    explicit DepthTestingPrecise(QWidget *parent = nullptr);
    ~DepthTestingPrecise();

    void initShader() ;
    void initTexture() ;
    void setShader(QString name, QVector3D value);

    QOpenGLShaderProgram shader_Shape_NotLinear;
    QOpenGLShaderProgram shader_Shape_Linear;

    QOpenGLShaderProgram* current_Shader_Shape;

    QVector3D u_viewPos;

    // 镜头相关
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;


    void updateShapeShader();

    void showWindow();
    void updateDlg();
    void initSigSlot();

private:
    Ui::DepthTestingPrecise *ui;
};

#endif // DEPTH_TESTING_PRECISE_H
