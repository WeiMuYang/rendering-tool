#include "preview.h"

float vertices3DBox[] = {
    // 第一个面：Pos.xyz  texture.uv
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    // 第二个面：Pos.xyz  texture.uv
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    // 第三个面：Pos.xyz  texture.uv
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    // 第四个面：Pos.xyz  texture.uv
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    // 第五个面：Pos.xyz  texture.uv
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    // 第六个面：Pos.xyz  texture.uv
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

QVector<QVector3D> BoxPositions = {
    QVector3D( 0.0f, 0.0f, 0.0f),
    QVector3D( 2.0f, 5.0f, -15.0f),
    QVector3D(-1.5f, -2.2f, -2.5f),
    QVector3D(-3.8f, -2.0f, -12.3f),
    QVector3D( 2.4f, -0.4f, -3.5f),
    QVector3D(-1.7f, 3.0f, -7.5f),
    QVector3D( 1.3f, -2.0f, -2.5f),
    QVector3D( 1.5f, 2.0f, -2.5f),
    QVector3D( 1.5f, 0.2f, -1.5f),
    QVector3D(-1.3f, 1.0f, -1.5f)
};

QVector3D lightPos(1.2f, 1.0f, 2.0f);
QVector3D lightColor(1.0f, 1.0f, 1.0f);
QVector3D objectColor(1.0f, 0.5f, 0.31f);


float verticesAxisX[] = {
    1.0f, 0.0f, 0.0f,   // x+1
    -1.0f, 0.0f, 0.0f,  // x-1
};
float verticesAxisY[] = {
    0.0f, 1.0f, 0.0f,   // y+1
    0.0f, -1.0f, 0.0f,  // y-1
};
float verticesAxisZ[] = {
    0.0f, 0.0f, 1.0f,   // z+1
    0.0f, 0.0f, -1.0f,  // z-1
};

unsigned int indicesRect[6] = {
    // 注意索引从0开始!
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};

Preview::Preview(QWidget *parent)
    : QOpenGLWidget{parent}
{
    // 获取键盘事件
    setFocusPolicy(Qt::StrongFocus);
    // 获取鼠标事件
    setMouseTracking(true);
    initVertices();
    pCamera_ = new Camera(QVector3D(0,0,3.0));
    currentScene_ = Scene::ColorOfObject;

}

Preview::~Preview()
{
    // 非initializeGL()、resizeGL()和paintGL()中调用，如果有修改的话，需要获取状态机，
    // 再调用OpenGL的接口
    makeCurrent();
    glDeleteBuffers(1,VBO_id);
    glDeleteBuffers(1,&EBO_id);
    glDeleteVertexArrays(1,VAO_id);
    doneCurrent();
}


void Preview::axisShaderProgram() {
    bool success;
    shader_axisX_.addShaderFromSourceFile(QOpenGLShader::Vertex,"../shader/axis_X.vert");
    shader_axisX_.addShaderFromSourceFile(QOpenGLShader::Fragment,"../shader/axis_X.frag");
    success = shader_axisX_.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_axisX_.log();
    }

    shader_axisY_.addShaderFromSourceFile(QOpenGLShader::Vertex,"../shader/axis_Y.vert");
    shader_axisY_.addShaderFromSourceFile(QOpenGLShader::Fragment,"../shader/axis_Y.frag");
    success = shader_axisY_.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_axisY_.log();
    }

    shader_axisZ_.addShaderFromSourceFile(QOpenGLShader::Vertex,"../shader/axis_Z.vert");
    shader_axisZ_.addShaderFromSourceFile(QOpenGLShader::Fragment,"../shader/axis_Z.frag");
    success = shader_axisZ_.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_axisZ_.log();
    }
}
void Preview::initShaderProgram() {
    axisShaderProgram();
    bool success;
    shader_ColorOfObject_Light_.addShaderFromSourceFile(QOpenGLShader::Fragment,"../shader/ColorOfObject_light.frag");
    shader_ColorOfObject_Light_.addShaderFromSourceFile(QOpenGLShader::Vertex,"../shader/ColorOfObject_light.vert");
    success = shader_ColorOfObject_Light_.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_ColorOfObject_Light_.log();
    }
    shader_ColorOfObject_Light_.bind();
    shader_ColorOfObject_Light_.setUniformValue("lightColor",objectColor);


    shader_ColorOfObject_Shapes_.addShaderFromSourceFile(QOpenGLShader::Fragment,"../shader/ColorOfObject_shapes.frag");
    shader_ColorOfObject_Shapes_.addShaderFromSourceFile(QOpenGLShader::Vertex,"../shader/ColorOfObject_shapes.vert");
    success = shader_ColorOfObject_Shapes_.link();
    if(!success) {
        qDebug()<<"ERR:"<<shader_ColorOfObject_Shapes_.log();
    }
    shader_ColorOfObject_Shapes_.bind();
    shader_ColorOfObject_Shapes_.setUniformValue("objectColor",lightColor);
    shader_ColorOfObject_Shapes_.setUniformValue("lightColor",objectColor);
}

void Preview::initTexture() {


}

void Preview::setAxisVAO() {
    // 绘制坐标轴 X
    glBindVertexArray(VAO_id[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_id[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * axisX_.verticeLength() , axisX_.getVertices(),GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 绘制坐标轴 Y
    glBindVertexArray(VAO_id[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_id[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * axisY_.verticeLength() , axisY_.getVertices(),GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 绘制坐标轴 Z
    glBindVertexArray(VAO_id[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_id[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * axisZ_.verticeLength() , axisZ_.getVertices(),GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Preview::initializeGL()
{
    qDebug() << "initializeGL" ;
    // 1.初始化OpenGL函数，否则OpenGL函数不可调用
    initializeOpenGLFunctions();
    // ------------------------一、VAO和VBO------------------------
    // 1.创建VAO和VBO对象，并赋予ID（使用Gen）
    // 1.创建一个VBO对象(OpenGL中) 顶点缓冲对象(Vertex Buffer Objects, VBO)
    //   顶点数组对象(Vertex Array Object, VAO)可以像顶点缓冲对象那样被绑定，任何随后的顶点属性调用都会存储在这个VAO中。
    glGenVertexArrays(4, VAO_id);
    glGenBuffers(4, VBO_id);
    setAxisVAO();
    setModelVAO();

    // 2. texture
    initTexture();

    // 3. shader
    initShaderProgram();
}

void Preview::resizeGL(int w, int h)
{
    qDebug() << "resizeGL" ;
    Q_UNUSED(w)
    Q_UNUSED(h)
}

void Preview::paintGL()
{
    qDebug() << "paintGL" ;
    //    initializeOpenGLFunctions(); // 执行后，下面的函数才有执行的意义
    // 设置窗口颜色，背景颜色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // 打开深度测试，否则立方体形状无法显示立体
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawAxis();
    drawModule();
}

void Preview::keyPressEvent(QKeyEvent *event)
{
    float deltaTime = 0.1f;
    switch (event->key()) {
        case Qt::Key_W: pCamera_->ProcessKeyboard(CameraMovement::FORWARD, deltaTime); break;
        case Qt::Key_S: pCamera_->ProcessKeyboard(CameraMovement::BACKWARD, deltaTime); break;
        case Qt::Key_D: pCamera_->ProcessKeyboard(CameraMovement::RIGHT, deltaTime); break;
        case Qt::Key_A: pCamera_->ProcessKeyboard(CameraMovement::LEFT, deltaTime); break;
    default:
        break;
    }
    update();
}

void Preview::mouseMoveEvent(QMouseEvent *event)
{
    static QPoint lastPos(width()/2,height()/2);
    auto currentPos=event->pos();
    mouseDeltaPos_ = currentPos - lastPos;
    lastPos = currentPos;

    pCamera_->ProcessMouseMovement(mouseDeltaPos_.x(), -mouseDeltaPos_.y());
    update();
}

void Preview::wheelEvent(QWheelEvent *event)
{
    pCamera_->ProcessMouseScroll(event->angleDelta().y()/120);

    update();
}

void Preview::vertexData2VBO() {
    // 初始化调用的，不用添加 makeCurrent
    switch (currentScene_) {
    case Scene::ColorOfObject:
    {
        // 1.把数据放进VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * box3D_.verticeLength() , box3D_.getVertices(), GL_STATIC_DRAW);

        // 2.配置EBO相关
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);
        unsigned int* indices = box3D_.getIndices();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * box3D_.indicesLength(), indices, GL_STATIC_DRAW);

        // 3.解析数据 a_Postion
        //  GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        // 4.开启VAO管理的第一个属性值 Position 开启location = 0的属性解析
        glEnableVertexAttribArray(0);
        // 5.解析数据 a_Texture
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
        break;
    default:
        break;
    }
}

void Preview::drawAxis() {
    shader_axisX_.bind();
    glBindVertexArray(VAO_id[0]);
    glDrawArrays(GL_LINES, 0, 2);
    shader_axisY_.bind();
    glBindVertexArray(VAO_id[1]);
    glDrawArrays(GL_LINES, 0, 2);
    shader_axisZ_.bind();
    glBindVertexArray(VAO_id[2]);
    glDrawArrays(GL_LINES, 0, 2);
}


void Preview::setTexture(Scene module) {

}


// 开始绘制
void Preview::drawModule() {
    // 使用时还需要再绑定一次
    glBindVertexArray(VAO_id[3]);
    // 模式：点  线  面
    switch (currentScene_) {
    case Scene::ColorOfObject:  //
    {
        shader_ColorOfObject_Light_.bind();
        QMatrix4x4 projection;
        projection.perspective(45,(float)width()/height(),0.1f,100);
        shader_ColorOfObject_Light_.setUniformValue("projection", projection);
        QMatrix4x4 view; // 默认是单位矩阵
        view.translate(0.0,0.0,-9.0);
        shader_ColorOfObject_Light_.setUniformValue("view", view);
        QMatrix4x4 model;
        int deg = 0;
        foreach (auto item, BoxPositions) {
            model.setToIdentity();
            model.translate(item);
            model.rotate(deg, 1.0f, 5.0f, 0.5f);
            deg += 30;
            shader_ColorOfObject_Light_.setUniformValue("model", model);
            glDrawArrays(GL_TRIANGLES,0,36);
        }

    }
        break;
    default:
        break;
    }
}

void Preview::initVertices() {
    // 坐标轴
    axisX_.setVerticesArr(verticesAxisX, 6);
    axisY_.setVerticesArr(verticesAxisY, 6);
    axisZ_.setVerticesArr(verticesAxisZ, 6);

    // 3DBox
    box3D_.setVerticesArr(vertices3DBox, 180);
    box3D_.setIndices(indicesRect, 6);

}


void Preview::setModelVAO() {
    // 2.绑定VAO，开始记录属性相关
    glBindVertexArray(VAO_id[3]);
    // 3.绑定VBO(一定是先绑定VAO再绑定VBO)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_id[3]);

    // EBO ： 次序不能在VBO上面，有绑定次序的 ???????????????
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);  // 需要解绑
    glGenBuffers(1, &EBO_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);

    // 4.添加顶点数据
    vertexData2VBO();

    // 5.解绑VBO和VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

