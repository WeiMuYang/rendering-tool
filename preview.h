#ifndef PREVIEW_H
#define PREVIEW_H

#include <QWidget>
// 1.引入相关库
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#include "modeling/triangle.h"
#include "modeling/rectangle.h"
#include "shader.h"
#include "data_type.h"
#include <QVector>

// 2.继承相关类
class Preview : public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit Preview(QWidget *parent = nullptr);

    // 可以绘制多个
    unsigned int VAO_id,VBO_id,EBO_id;
    // 着色器变量
    unsigned int shaderProgram_id;

    void vertexData2VBO();
    void draw();

    void setModuleType(Module type) {
        currentModelType_ = type;
    }

    void setDrawMode(DrawMode mode) {
        drawMode_ = mode;
    }

    void setShader(Shader* s) {
        pShader_ = s;
    }

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
    Modeling::Triangle triangle_;
    Modeling::Rectangle rectangle_;
    Shader* pShader_{nullptr};
    Module currentModelType_;
    DrawMode drawMode_;
};

#endif // PREVIEW_H
