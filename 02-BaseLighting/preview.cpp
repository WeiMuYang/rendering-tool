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
    currentScene_ = Scene::ColorOfObject;

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



void Preview::initTexture() {

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

void Preview::setShaderColorObj_01(QString name, QVector3D value)
{
    colorObj.setShader(name, value);
    update();
}

void Preview::setShaderPhongLight_02(QString name, QVector3D value)
{
    phongLight.setShader(name, value);
    update();
}

void Preview::setShaderGouraudLight_03(QString name, QVector3D value)
{
    gouraudLight.setShader(name, value);
    update();
}

void Preview::setShaderMaterial_04(QString name, QVector3D value)
{
    material.setShader(name, value);
    update();
}

void Preview::setShaderCyanPlastic_05(QString name, QVector3D value)
{
    cyanPlastic.setShader(name, value);
    update();
}

void Preview::initializeGL()
{
    // 1.初始化OpenGL函数，否则OpenGL函数不可调用
    initializeOpenGLFunctions();
    // 2.
    initAxisVAO();
    initColorofObjectVAO_01();
    initPhongLightVAO_02();
    initGouraudLightVAO_03();
    initMaterialVAO_04();
    initCyanPlastic_05();
    // 5.解绑VBO和VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 2. texture
    initTexture();

    // 3. shader
    axisXYZ.initShader();
    colorObj.initShader();
    phongLight.initShader();
    gouraudLight.initShader();
    material.initShader();
    cyanPlastic.initShader();
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

void Preview::DrawColorOfObject_01() {
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;
    if(isTimeUsed) {
        rotateByTime = m_elapsedTime.elapsed() / 50.0;
    }
    projection.perspective(pCamera_->Zoom,(float)width()/height(),0.1f,100.0f);
    view=pCamera_->GetViewMatrix();

    colorObj.shader_Shape.bind();
    colorObj.shader_Shape.setUniformValue("projection", projection);
    colorObj.shader_Shape.setUniformValue("view", view);
    model.rotate(rotateByTime, 1.0f, 5.0f, 0.5f);
    colorObj.shader_Shape.setUniformValue("model", model);
    colorObj.shader_Shape.setUniformValue("objectColor",colorObj.objectColor);
    colorObj.shader_Shape.setUniformValue("lightColor",colorObj.lightColor);
    glBindVertexArray(VAO_Shape01);
    glDrawArrays(GL_TRIANGLES,0,36);

    colorObj.shader_Light.bind();
    colorObj.shader_Light.setUniformValue("projection", projection);
    colorObj.shader_Light.setUniformValue("view", view);
    model.setToIdentity();
    model.translate(colorObj.lightPos);
    model.rotate(1.0f, 1.0f, 5.0f, 0.5f);
    model.scale(0.2f);
    colorObj.shader_Light.setUniformValue("model", model);
    colorObj.shader_Light.setUniformValue("lightColor",colorObj.lightColor);
    glBindVertexArray(VAO_Light01);
    glDrawArrays(GL_TRIANGLES,0,36);
}

void Preview::DrawPhongLight_02() {
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    if(isTimeUsed) {
        rotateByTime = m_elapsedTime.elapsed() / 50.0;
    }
    projection.perspective(pCamera_->Zoom,(float)width()/height(),0.1f,100.0f);
    view=pCamera_->GetViewMatrix();

    phongLight.shader_Shape.bind();
    phongLight.shader_Shape.setUniformValue("projection", projection);
    phongLight.shader_Shape.setUniformValue("view", view);
    model.rotate(rotateByTime, 1.0f, 5.0f, 0.5f);
    phongLight.lightPos.setX(cos(rotateByTime/50)*2.5);
    phongLight.lightPos.setZ(sin(rotateByTime/50)*2.5);
    phongLight.shader_Shape.setUniformValue("lightPos",phongLight.lightPos);
    phongLight.shader_Shape.setUniformValue("model", model);
    phongLight.shader_Shape.setUniformValue("objectColor",phongLight.objectColor);
    phongLight.shader_Shape.setUniformValue("lightColor",phongLight.lightColor);
    phongLight.shader_Shape.setUniformValue("specularStrength",phongLight.specularStrength);
    phongLight.shader_Shape.setUniformValue("ambientStrength",phongLight.ambientStrength);
    phongLight.shader_Shape.setUniformValue("shiny",phongLight.shiny);
    phongLight.shader_Shape.setUniformValue("viewPos", pCamera_->Position);
    glBindVertexArray(VAO_Shape02);
    glDrawArrays(GL_TRIANGLES,0,36);

    phongLight.shader_Light.bind();
    phongLight.shader_Light.setUniformValue("projection", projection);
    phongLight.shader_Light.setUniformValue("view", view);
    model.setToIdentity();
    model.translate(phongLight.lightPos);
    model.rotate(1.0f, 1.0f, 5.0f, 0.5f);
    model.scale(0.2f);
    phongLight.shader_Light.setUniformValue("model", model);
    phongLight.shader_Light.setUniformValue("lightColor",phongLight.lightColor);

    phongLight.shader_Light.setUniformValue("lightPos",phongLight.lightPos);

    glBindVertexArray(VAO_Light02);
    glDrawArrays(GL_TRIANGLES,0,36);
}

void Preview::DrawGouraudLight_03() {
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    if(isTimeUsed) {
        rotateByTime = m_elapsedTime.elapsed() / 50.0;
    }
    projection.perspective(pCamera_->Zoom,(float)width()/height(),0.1f,100.0f);
    view = pCamera_->GetViewMatrix();

    gouraudLight.shader_Shape.bind();
    gouraudLight.shader_Shape.setUniformValue("projection", projection);
    gouraudLight.shader_Shape.setUniformValue("view", view);
    model.rotate(rotateByTime, 1.0f, 5.0f, 0.5f);
    gouraudLight.lightPos.setX(cos(rotateByTime/50.0)*2.5);
    gouraudLight.lightPos.setZ(sin(rotateByTime/50.0)*2.5);
    gouraudLight.shader_Shape.setUniformValue("lightPos",gouraudLight.lightPos);
    gouraudLight.shader_Shape.setUniformValue("model", model);
    gouraudLight.shader_Shape.setUniformValue("objectColor",gouraudLight.objectColor);
    gouraudLight.shader_Shape.setUniformValue("lightColor",gouraudLight.lightColor);
    gouraudLight.shader_Shape.setUniformValue("viewPos", pCamera_->Position);
    glBindVertexArray(VAO_Shape02);
    glDrawArrays(GL_TRIANGLES,0,36);

    gouraudLight.shader_Light.bind();
    gouraudLight.shader_Light.setUniformValue("projection", projection);
    gouraudLight.shader_Light.setUniformValue("view", view);
    model.setToIdentity();
    model.translate(gouraudLight.lightPos);
    model.rotate(1.0f, 1.0f, 5.0f, 0.5f);
    model.scale(0.2f);
    gouraudLight.shader_Light.setUniformValue("model", model);
    gouraudLight.shader_Light.setUniformValue("lightColor",gouraudLight.lightColor);

    gouraudLight.shader_Light.setUniformValue("lightPos",gouraudLight.lightPos);

    glBindVertexArray(VAO_Light02);
    glDrawArrays(GL_TRIANGLES,0,36);
}

void Preview::DrawMaterial_04() {
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    if(isTimeUsed) {
        rotateByTime = m_elapsedTime.elapsed() / 50.0;
    }
    projection.perspective(pCamera_->Zoom,(float)width()/height(),0.1f,100.0f);
    view = pCamera_->GetViewMatrix();
    model.rotate(rotateByTime, 1.0f, 5.0f, 0.5f);
    material.projection = projection;
    material.view = view;
    material.model = model;
    material.lightColor.setX(sin(m_elapsedTime.elapsed() / 200 * 2.0f));
    material.lightColor.setY(sin(m_elapsedTime.elapsed() / 200 * 0.7f));
    material.lightColor.setZ(sin(m_elapsedTime.elapsed() / 200 * 1.3f));
    material.light.diffuse = QVector3D(0.5f,0.5f,0.5f);
    material.light.ambient = material.light.diffuse * QVector3D(0.2f,0.2f,0.2f);
    material.viewPos = pCamera_->Position;
    material.updateShapeShader();
    glBindVertexArray(VAO_Shape02);
    glDrawArrays(GL_TRIANGLES,0,36);

    //// Shader Light
    model.setToIdentity();
    model.translate(material.lightPos);
    model.rotate(1.0, 1.0f, 5.0f, 0.5f);
    model.scale(0.2f);
    material.model = model;
    material.updateLightShader();

    glBindVertexArray(VAO_Light02);
    glDrawArrays(GL_TRIANGLES,0,36);
}

void Preview::DrawCyanPlastic_05() {
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    if(isTimeUsed) {
        rotateByTime = m_elapsedTime.elapsed() / 50.0;
    }
    projection.perspective(pCamera_->Zoom,(float)width()/height(),0.1f,100.0f);
    view = pCamera_->GetViewMatrix();
    model.rotate(rotateByTime, 1.0f, 5.0f, 0.5f);
    cyanPlastic.projection = projection;
    cyanPlastic.view = view;
    cyanPlastic.model = model;
    cyanPlastic.viewPos = pCamera_->Position;
    cyanPlastic.updateShapeShader();
    glBindVertexArray(VAO_Shape02);
    glDrawArrays(GL_TRIANGLES,0,36);

    //// Shader Light
    model.setToIdentity();
    model.translate(cyanPlastic.lightPos);
    model.rotate(1.0, 1.0f, 5.0f, 0.5f);
    model.scale(0.2f);
    cyanPlastic.model = model;
    cyanPlastic.updateLightShader();

    glBindVertexArray(VAO_Light02);
    glDrawArrays(GL_TRIANGLES,0,36);
}


// 开始绘制
void Preview::drawModule() {
    switch (currentScene_) {
    case Scene::ColorOfObject:
        DrawColorOfObject_01();
        break;
    case Scene::PhongLight:
        DrawPhongLight_02();
        break;
    case Scene::GouraudLight:
        DrawGouraudLight_03();
        break;
    case Scene::Material:
        DrawMaterial_04();
        break;
    case Scene::CyanPlastic:
        DrawCyanPlastic_05();
        break;
    default:
        break;
    }
}


void Preview::initColorofObjectVAO_01() {
    {   // 物体
        glGenVertexArrays(1, &VAO_Shape01);
        glGenBuffers(1, &VBO_Shape01);
        // 1.绑定VAO，开始记录属性相关
        glBindVertexArray(VAO_Shape01);
        // 2.绑定VBO(一定是先绑定VAO再绑定VBO)
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_Shape01);
        // 3.EBO ： 次序不能在VBO上面，有绑定次序的
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glGenBuffers(1, &EBO_Shape01);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Shape01);

        // 1.把数据放进VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * colorObj.box3D.verticeLength() , colorObj.box3D.getVertices(), GL_STATIC_DRAW);

        // 2.配置EBO相关
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Shape01);
        unsigned int* indices = colorObj.box3D.getIndices();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * colorObj.box3D.indicesLength(), indices, GL_STATIC_DRAW);

        // 3.解析数据 a_Postion
        //  GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        // 4.开启VAO管理的第一个属性值 Position 开启location = 0的属性解析
        glEnableVertexAttribArray(0);
        // 5.解析数据 a_Texture
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    {   // 光照
        glGenVertexArrays(1, &VAO_Light01);
        glGenBuffers(1, &VBO_Light01);
        // 1.绑定VAO，开始记录属性相关
        glBindVertexArray(VAO_Light01);
        // 2.绑定VBO(一定是先绑定VAO再绑定VBO)
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_Light01);
        // 3.EBO ： 次序不能在VBO上面，有绑定次序的
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glGenBuffers(1, &EBO_Light01);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Light01);

        // 1.把数据放进VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * colorObj.box3D.verticeLength() , colorObj.box3D.getVertices(), GL_STATIC_DRAW);
        // 2.配置EBO相关
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Light01);
        unsigned int* indices = colorObj.box3D.getIndices();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * colorObj.box3D.indicesLength(), indices, GL_STATIC_DRAW);
        // 3.解析数据 a_Postion
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        // 4.开启VAO管理的第一个属性值 Position 开启location = 0的属性解析
        glEnableVertexAttribArray(0);
        // 5.解析数据 a_Texture
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
}

void Preview::initPhongLightVAO_02() {
    {   // 物体
        glGenVertexArrays(1, &VAO_Shape02);
        glGenBuffers(1, &VBO_Shape02);
        // 1.绑定VAO，开始记录属性相关
        glBindVertexArray(VAO_Shape02);
        // 2.绑定VBO(一定是先绑定VAO再绑定VBO)
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_Shape02);
        // 3.EBO ： 次序不能在VBO上面，有绑定次序的
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glGenBuffers(1, &EBO_Shape02);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Shape02);

        // 1.把数据放进VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * phongLight.box3D.verticeLength() , phongLight.box3D.getVertices(), GL_STATIC_DRAW);

        // 2.配置EBO相关
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Shape02);
        unsigned int* indices = phongLight.box3D.getIndices();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * phongLight.box3D.indicesLength(), indices, GL_STATIC_DRAW);

        // 3.解析数据 a_Postion
        //  GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        // 4.开启VAO管理的第一个属性值 Position 开启location = 0的属性解析
        glEnableVertexAttribArray(0);
        // 5.解析数据 a_Texture
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    {   // 光照
        glGenVertexArrays(1, &VAO_Light02);
        glGenBuffers(1, &VBO_Light02);
        // 1.绑定VAO，开始记录属性相关
        glBindVertexArray(VAO_Light02);
        // 2.绑定VBO(一定是先绑定VAO再绑定VBO)
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_Light02);
        // 3.EBO ： 次序不能在VBO上面，有绑定次序的
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glGenBuffers(1, &EBO_Light02);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Light02);

        // 1.把数据放进VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * phongLight.box3D.verticeLength() , phongLight.box3D.getVertices(), GL_STATIC_DRAW);
        // 2.配置EBO相关
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Light02);
        unsigned int* indices = phongLight.box3D.getIndices();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * phongLight.box3D.indicesLength(), indices, GL_STATIC_DRAW);
        // 3.解析数据 a_Postion
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        // 4.开启VAO管理的第一个属性值 Position 开启location = 0的属性解析
        glEnableVertexAttribArray(0);
        // 5.解析数据 a_Texture
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
}

void Preview::initGouraudLightVAO_03() {
    // 使用VAO_02即可
//    initPhongLightVAO_02();
}

void Preview::initMaterialVAO_04() {
    // 使用VAO_02即可
//    initPhongLightVAO_02();
}

void Preview::initCyanPlastic_05() {
    // 使用VAO_02即可
//    initPhongLightVAO_02();
}

void Preview::setCurrentScene(Scene s)
{
    currentScene_ = s;
}
void Preview::on_timeout()
{
    update();
}

void Preview::timeStartStop() {
    isTimeUsed = !isTimeUsed;
}

