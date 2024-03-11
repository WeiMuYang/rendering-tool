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
#include "mesh.h"
#include "model.h"

#include "00-axis/axis.h"
#include "01-depth-testing/depth_testing.h"
#include "02-depth-testing-precise/depth_testing_precise.h"
#include "03-mouse-picking/mouse_picking.h"
#include "04-load-models/load_models.h"
#include "05-stencil-outline/stencil_outline.h"
#include "06-discard/discard.h"
#include "07-blending/blending.h"
#include "08-culling/face_culling.h"
#include "09-frame-buffer/frame_buffer.h"
#include "10-post-processing/post_processing.h"
#include "11-sky-box/sky_box.h"
#include "12-advanced-data/modify_data_buffer.h"
#include "13-glsl-variable/glsl_variable.h"

struct ModelInfo{
    Model *model;
    QVector3D worldPos;
    float pitch;
    float yaw;
    float roll;
    bool isSelected;
    QString name;
};

// 2.继承相关类
class Preview : public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit Preview(QWidget *parent = nullptr);
    ~Preview();
    // 坐标轴
    unsigned int VAO_Axis[3],VBO_Axis[3];
    void drawAxis();
    void initAxisVAO();
    void setCurrentScene(Scene s);
    void timeStartStop();
    Mesh* processMesh(std::vector<float> vertices,int sizeOfVer, vector<Texture> textures);

    void loadModel(string path);
    QVector3D cameraPosInit(float maxY, float minY);

    void DrawDepthTesting_01();
    void DepthTesting(DepthTestType depthType);

    void DrawDepthTestingPrecise_02();


    QVector4D worldPosFromViewPort(int posX, int posY);
    void DrawMousePicking_03();

    void DrawLoadModelsControl_04();
    void DrawStencilOutLineControl_05();
    void DrawDiscard_06();
    void DrawBlending_07();
    void DrawCulling_08();
    void openBlending();
    void openFaceCulling();
    void DrawFrameBuffer_09();
    void DrawPostProcessing_10();
    void DrawSkyBox_11();
    void DrawModifyData_12();
    void DrawGLSLVariable_13();
public slots:
    void on_timeout();
    void setDepthTestingSlot(DepthTestType type);
signals:
    void mousePickingPos(QVector3D wolrdpos);
protected:

    //////  需要修改的 ////
    void drawModule();
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
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void sigPosition(QVector3D pos);
    void sigYawPitch(float yaw, float pitch);
    void sigFrontRightUp(QVector3D f,QVector3D r, QVector3D u,QVector3D wu);

private:
    Scene currentScene_;
    DepthTestType currentDepthTesting_;
    QTimer m_timer;
    QElapsedTimer m_elapsedTime;
    QVector3D rotationAxis;
    float rotateByTime;
    bool isTimeUsed{true};
    Camera* pCamera_;
    QPoint mouseDeltaPos_;
    bool m_modelMoving;

    class Axis axisXYZ;
    class DepthTesting depthTesting;
    class DepthTestingPrecise depthTestingPrecise;
    class MousePicking mousePicking;
    class LoadModels loadModels;
    class StencilOutLine stencilOutLine;
    class Discard discard;
    class Blending blending;
    class FaceCulling faceCulling;
    class FrameBuffer frameBuffer;
    class PostProcessing postProcessing;
    class SkyBox skyBox;
    class ModifyDataBuffer modifyDataBuffer;
    class GLSLVariable glslVer;
    // name ,  model
    QMap<QString, ModelInfo> m_Models;
    Mesh * m_CubeMesh;
    Mesh * m_PlaneMesh;
    Mesh * m_grassMesh;
    Mesh * m_blendingMesh;
    Mesh * m_frameBufferMesh;
    Model* m_model = NULL;
};

#endif // PREVIEW_H
