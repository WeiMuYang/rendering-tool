#ifndef PREVIEW_H
#define PREVIEW_H

#include <QWidget>
// 1.引入相关库
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include "vertices.h"
#include <QVector>
#include "data_type.h"


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
    unsigned int VAO_Axis,VBO_Axis;

    void vertexData2VBO();
    void drawModule();
    void drawAxis();
    void setTexture(Module module);

    void setModuleType(Module type);

    void setDrawMode(DrawMode mode);

    void setWrap(TexWrap texWrap);

    void initVertices();

    void set_shaderProRectUniform_Uniform(char* uniformName, QVector4D color);
    void set_shaderProRectTex_Uniform(char* uniformName, float value);
    void set_shaderProTransRotaScale_Uniform( QMatrix4x4 value);

    void initShaderProgram();
    void initTexture();

    void setModelVAO();
    void setAxisVAO();

    void texTureWrap();
    void texTureMinFilter();
    void texTureMagFilter();

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

signals:

private:
    Module currentModelType_;
    DrawMode drawMode_;
    Vertices triangle_;         // 创建一个 triangle 对象           →   shaderProTri
    Vertices rectanglePos_;     // 创建一个 rectanglePos_ 对象      →   shaderProRectUniform
    Vertices rectanglePosCol_;  // 创建一个 rectanglePosCol_ 对象   →   shaderProRectACol
    Vertices rectanglePosColTex_; //                              →   shaderProRectTex
    Vertices rectanglePosColTexFilter_;                        // →   shaderProRectTexFilter
    Vertices rectTranRotatScale_;




    Vertices axisX_;
    Vertices axisY_;
    Vertices axisZ_;

    QOpenGLShaderProgram shaderProRectUniform;
    QOpenGLShaderProgram shaderProTri;
    QOpenGLShaderProgram shaderProRectACol;
    QOpenGLShaderProgram shaderProAxis;
    QOpenGLShaderProgram shaderProRectTex;
    QOpenGLShaderProgram shaderProRectTexFilter;
    QOpenGLShaderProgram shaderProTransRotaScale;

    QOpenGLTexture* textureWall;
    QOpenGLTexture* textureSmile;
    QOpenGLTexture* textureSmall;

    TexWrap texWrap_;
    TexFilter texMinFilter_;
    TexFilter texMagFilter_;
};

#endif // PREVIEW_H
