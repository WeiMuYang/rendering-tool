#include "preview.h"

Preview::Preview(QWidget *parent)
    : QOpenGLWidget{parent}
{
    // 获取键盘事件
    setFocusPolicy(Qt::StrongFocus);
    // 获取鼠标事件
    setMouseTracking(true);
    // 初始化镜头位置
    pCamera_ = new Camera(QVector3D(0,0,5.0));
    pCamera_->fov = 45.0f;
    pCamera_->aspectRatio = (float)width()/height();
    pCamera_->nearPlane = 0.1f;
    pCamera_->farPlane = 100.0f;

    currentScene_ = Scene::ColorOfObject;

    rotationAxis = {1.0f, 1.0f, 0.5f};

    connect(&m_timer,SIGNAL(timeout()),this,SLOT(on_timeout()));
    m_timer.start(50);
    m_elapsedTime.start();
}

Preview::~Preview()
{
    // 非initializeGL()、resizeGL()和paintGL()中调用，如果有修改的话，需要获取状态机，
    // 再调用OpenGL的接口
    makeCurrent();
    glDeleteBuffers(3,VBO_Axis);
    glDeleteVertexArrays(3,VAO_Axis);
    doneCurrent();
}


void Preview::initAxisVAO() {
    glGenVertexArrays(3, VAO_Axis);
    glGenBuffers(3, VBO_Axis);
    // 绘制坐标轴 X
    glBindVertexArray(VAO_Axis[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Axis[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * axisXYZ.axisX_.verticeLength() , axisXYZ.axisX_.getVertices(),GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 绘制坐标轴 Y
    glBindVertexArray(VAO_Axis[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Axis[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * axisXYZ.axisY_.verticeLength() , axisXYZ.axisY_.getVertices(),GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 绘制坐标轴 Z
    glBindVertexArray(VAO_Axis[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Axis[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * axisXYZ.axisZ_.verticeLength() , axisXYZ.axisZ_.getVertices(),GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}


void Preview::initializeGL()
{
    // 1.初始化OpenGL函数，否则OpenGL函数不可调用
    initializeOpenGLFunctions();
    // 2.
    initAxisVAO();
    // 5.解绑VBO和VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 2. texture


    // 3. shader
    axisXYZ.initShader();

}

void Preview::resizeGL(int w, int h)
{
    qDebug() << "resizeGL" ;
    Q_UNUSED(w)
    Q_UNUSED(h)
}

void Preview::paintGL()
{
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
    if(event->buttons() & Qt::RightButton) {
        auto currentPos = event->pos();
        mouseDeltaPos_ = currentPos - lastPos;
        lastPos = currentPos;
        pCamera_->ProcessMouseMovement(mouseDeltaPos_.x(), -mouseDeltaPos_.y());
        update();
    }
}

void Preview::wheelEvent(QWheelEvent *event)
{
    pCamera_->ProcessMouseScroll(event->angleDelta().y()/120);

    update();
}

void Preview::drawAxis() {
    axisXYZ.shader_axisX.bind();
    glBindVertexArray(VAO_Axis[0]);
    glDrawArrays(GL_LINES, 0, 2);
    axisXYZ.shader_axisY.bind();
    glBindVertexArray(VAO_Axis[1]);
    glDrawArrays(GL_LINES, 0, 2);
    axisXYZ.shader_axisZ.bind();
    glBindVertexArray(VAO_Axis[2]);
    glDrawArrays(GL_LINES, 0, 2);
}




// 开始绘制
void Preview::drawModule() {
//    switch (currentScene_) {

//    case Scene::MultLight:
//        DrawMultLight_11();
//        break;
//    default:
//        break;
//    }
}




void Preview::setCurrentScene(Scene s)
{
//    colorObj.close();
    currentScene_ = s;
//    switch (currentScene_) {
//    case Scene::ColorOfObject:
//        colorObj.showWindow();
//        break;
//    default:
//        break;
//    }
}
void Preview::on_timeout()
{
    update();
}

void Preview::timeStartStop() {
    isTimeUsed = !isTimeUsed;
}

