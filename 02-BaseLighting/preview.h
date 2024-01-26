#ifndef PREVIEW_H
#define PREVIEW_H

#include <QWidget>
// 1.引入相关库
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QKeyEvent>
#include <QVector3D>

#include "data_type.h"
#include "vertices.h"
#include "camera.h"
#include "shader.h"


// 2.继承相关类
class Preview : public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit Preview(QWidget *parent = nullptr);
    ~Preview();
    // 可以绘制多个
    unsigned int VAO_id[4],VBO_id[4],EBO_id;

    // 坐标轴
    unsigned int VAO_Axis[3],VBO_Axis[3];

    void vertexData2VBO();
    void drawModule();
    void drawAxis();
    void setTexture(Scene module);

    void setDrawMode(DrawMode mode);

    void setWrap(TexWrap texWrap);

    void initVertices();


    void initShaderProgram();
    void axisShaderProgram();
    void initTexture();

    void setModelVAO();
    void setAxisVAO();


    void setMinFilter(TexFilter TexF);
    void setMagFilter(TexFilter TexF);
protected:
    // 3.重载三个相关虚函数, 无需调用，会自动的调用执行
    // 1）initializeGL() : 设置OpenGL资源和状态，最先调用且调用一次。
    virtual void initializeGL();
    // 2）resize() ：设置OpenGL视口、投影等，当widget调整大小(或首次显示)时调用；
    virtual void resizeGL(int w, int h);
    // 3）paintGL() ：渲染OpenGL窗口，当窗口widget需要更新时调用；
    //      a）在paintGL()以外的地方调用绘制函数是没有意义的，因为绘制图像最终将被paintGL()覆盖；
    //      b）若需要从paintGL()以外的位置触发重新绘制(e.g. 使用计时器设置场景动画)，则应调用widget的update()函数来安排更新。
    virtual void paintGL();

    void keyPressEvent(QKeyEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void wheelEvent(QWheelEvent *event);

signals:
    void sigPosition(QVector3D pos);
    void sigYawPitch(float yaw, float pitch);
    void sigFrontRightUp(QVector3D f,QVector3D r, QVector3D u,QVector3D wu);

private:
    Scene currentScene_;
    // 坐标系
    Vertices axisX_;
    Shader shader_axisX_;
    Vertices axisY_;
    Shader shader_axisY_;
    Vertices axisZ_;
    Shader shader_axisZ_;
    // -----
    Vertices box3D_;
    Shader shader_ColorOfObject_Light_;
    Shader shader_ColorOfObject_Shapes_;

    Camera* pCamera_;
    QPoint mouseDeltaPos_;
};

#endif // PREVIEW_H
