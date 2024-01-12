#include "preview.h"

Preview::Preview(QWidget *parent)
    : QOpenGLWidget{parent}
{
    currentModelType_ = Module::isRectangle;
    drawMode_ = DrawMode::isFillMode;
    pShader_ = new Shader(this);
}

void Preview::initializeGL()
{
    // 1.初始化OpenGL函数，否则OpenGL函数不可调用
    initializeOpenGLFunctions();
    // ------------------------一、VAO和VBO------------------------
    // 1.创建VAO和VBO对象，并赋予ID（使用Gen）
    // 1.创建一个VBO对象(OpenGL中) 顶点缓冲对象(Vertex Buffer Objects, VBO)
    //   顶点数组对象(Vertex Array Object, VAO)可以像顶点缓冲对象那样被绑定，任何随后的顶点属性调用都会存储在这个VAO中。
    glGenVertexArrays(1, &VAO_id);
    glGenBuffers(1, &VBO_id);

    // 2.绑定VAO，开始记录属性相关
    glBindVertexArray(VAO_id);

    // 3.绑定VBO(一定是先绑定VAO再绑定VBO)
    glBindBuffer(GL_ARRAY_BUFFER, VBO_id);

    // 4.添加顶点数据
    vertexData2VBO();

    // 5.解析数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // 6.开启location = 0的属性解析
    glEnableVertexAttribArray(0);

    // 7.解绑VBO和VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // -----------------------------end---------------------------

    // ------------------------二、着色器相关------------------------
    // 创建顶点着色器
    unsigned int vertexShader_id = glCreateShader(GL_VERTEX_SHADER);
    char* vertexShaderSource = pShader_->getVertexShader();
    glShaderSource(vertexShader_id, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader_id);

    // 创建片段着色器
    unsigned int fragmentShader_id = glCreateShader(GL_FRAGMENT_SHADER);
    char* fragmentShaderSource = pShader_->getFragmentShader();
    glShaderSource(fragmentShader_id, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader_id);
    // -----------------------------end---------------------------

    // -----------------------三、着色器程序相关----------------------
    shaderProgram_id = glCreateProgram();
    glAttachShader(shaderProgram_id, vertexShader_id);
    glAttachShader(shaderProgram_id, fragmentShader_id);
    glLinkProgram(shaderProgram_id);
    // -----------------------------end---------------------------

    // 删除顶点着色器和片段着色器(不能将着色器程序也给delete掉)
    glDeleteShader(vertexShader_id);
    glDeleteShader(fragmentShader_id);
}

void Preview::resizeGL(int w, int h)
{

}

void Preview::paintGL()
{
    // 2.initializeOpenGLFunctions();执行后，下面的函数才有执行的意义
    // 设置窗口颜色，背景颜色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 【画一个图形时需要说使用哪个着色器】
    glUseProgram(shaderProgram_id);
    // 使用时还需要再绑定一次
    glBindVertexArray(VAO_id);

    draw();
}


void Preview::vertexData2VBO() {
    switch (currentModelType_) {
    case Module::isTriangle:
    {
        // 1.把数据放进VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * triangle_.verticeLength() , triangle_.getVertices(), GL_STATIC_DRAW);
    }
        break;
    case Module::isRectangle:
    {
        // 1.把数据放进VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * rectangle_.verticeLength() , rectangle_.getVertices(), GL_STATIC_DRAW);
        // 2.配置EBO相关
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);
        int* indices = rectangle_.getIndices();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * rectangle_.indicesLength(), indices, GL_STATIC_DRAW);
    }
        break;
    default:
        break;
    }
}

// 开始绘制
void Preview::draw() {
    // 模式：点  线  面
    switch (drawMode_) {
    case DrawMode::isPointMode:
        // 函数配置OpenGL如何绘制图元。
        // 第一个参数：将其应用到所有的三角形的正面和背面；
        // 第二个参数：用线来绘制。
        // 之后的绘制调用会一直以线框模式绘制三角形，直到我们用glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)将其设置回默认模式。
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        break;
    case DrawMode::isLineMode:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    default:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    }
    // 形状： 三角形，矩形
    switch (currentModelType_) {
    case Module::isTriangle:
        glDrawArrays(GL_TRIANGLES, 0, 3);
        break;
    case Module::isRectangle:
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        break;
    default:
        break;
    }
}


