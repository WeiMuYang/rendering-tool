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
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>

#include "data_type.h"
#include "camera.h"

#include "04-material/material.h"
#include "03-gourand-light/gouraud_light.h"
#include "02-phong-light/phong_light.h"
#include "01-color-of-object/color_of_object.h"
#include "00-axis/axis.h"


// 2.继承相关类
class Preview : public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit Preview(QWidget *parent = nullptr);
    ~Preview();
    // 坐标轴
    unsigned int VAO_Axis[3],VBO_Axis[3];

    void setCurrentScene(Scene s);
    void timeStartStop();

    // 01
    unsigned int VAO_Shape01,VBO_Shape01,EBO_Shape01;
    unsigned int VAO_Light01,VBO_Light01,EBO_Light01;
    void initColorofObjectVAO_01();
    void DrawColorOfObject_01();
    void setShaderColorObj_01(QString name, QVector3D value);

    void drawModule();
    void drawAxis();
    void initTexture();
    void initAxisVAO();
    // 02
    unsigned int VAO_Shape02,VBO_Shape02,EBO_Shape02;
    unsigned int VAO_Light02,VBO_Light02,EBO_Light02;
    void DrawPhongLight_02();
    void initPhongLightVAO_02();
    void setShaderPhongLight_02(QString name, QVector3D value);
    // 03
    void DrawGouraudLight_03();
    void initGouraudLightVAO_03();
    void setShaderGouraudLight_03(QString name, QVector3D value);
    // 04
    void setShaderMaterial_04(QString name, QVector3D value);
    void DrawMaterial_04();
    void initMaterialVAO_04();
public slots:
    void on_timeout();
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
    QTimer m_timer;
    QElapsedTimer m_elapsedTime;
    float rotateByTime;
    bool isTimeUsed{true};
    Camera* pCamera_;
    QPoint mouseDeltaPos_;
    class ColorOfObject colorObj;
    class Axis axisXYZ;
    class PhongLight phongLight;
    class GouraudLight gouraudLight;
    class Material material;
};

#endif // PREVIEW_H
