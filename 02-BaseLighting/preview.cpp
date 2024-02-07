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

void Preview::initTextureLightVAO_06()
{
    {   // 物体
        glGenVertexArrays(1, &VAO_Shape06);
        glGenBuffers(1, &VBO_Shape06);
        // 1.绑定VAO，开始记录属性相关
        glBindVertexArray(VAO_Shape06);
        // 2.绑定VBO(一定是先绑定VAO再绑定VBO)
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_Shape06);

        // 1.把数据放进VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * textureLight.box3D.verticeLength() , textureLight.box3D.getVertices(), GL_STATIC_DRAW);

        // 3.解析数据 a_Postion
        //  GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        // 4.开启VAO管理的第一个属性值 Position 开启location = 0的属性解析
        glEnableVertexAttribArray(0);
        // 5.解析数据 a_Normals
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // 5.解析数据 a_texCoords
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    {   // 光照  VAO_Light01
        // 使用 VAO_Light01即可
    }
}

void Preview::DrawTextureLight_06()
{
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    if(isTimeUsed) {
        rotateByTime = m_elapsedTime.elapsed() / 50.0;
    }
    projection.perspective(pCamera_->fov,(float)width()/height(),pCamera_->nearPlane,pCamera_->farPlane);
    view = pCamera_->GetViewMatrix();
    model.rotate(rotateByTime, rotationAxis.x(), rotationAxis.y(), rotationAxis.z());
    textureLight.projection = projection;
    textureLight.view = view;
    textureLight.model = model;
    textureLight.u_viewPos = pCamera_->Position;

    textureLight.updateShapeShader();
    glBindVertexArray(VAO_Shape06);
    glDrawArrays(GL_TRIANGLES,0,36);

    //// Shader Light
    model.setToIdentity();
    model.translate(textureLight.u_lightPos);
    model.rotate(1.0, 1.0f, 5.0f, 0.5f);
    model.scale(0.2f);
    textureLight.model = model;
    textureLight.updateLightShader();

    glBindVertexArray(VAO_Light02);
    glDrawArrays(GL_TRIANGLES,0,36);
}

void Preview::initParallelLightVAO_07()
{
    // 使用initTextureLightVAO_06();即可
}

void Preview::DrawParallelLight_07()
{
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    if(isTimeUsed) {
        rotateByTime = m_elapsedTime.elapsed() / 50.0;
    }
    projection.perspective(pCamera_->fov,(float)width()/height(),pCamera_->nearPlane,pCamera_->farPlane);
    view = pCamera_->GetViewMatrix();
    //    model.rotate(rotateByTime, rotationAxis.x(), rotationAxis.y(), rotationAxis.z());
    parallelLight.projection = projection;
    parallelLight.view = view;
    //    parallelLight.model = model;
    parallelLight.u_viewPos = pCamera_->Position;

    glBindVertexArray(VAO_Shape06);
    for(unsigned int i = 0; i < 10; i++) {
        QMatrix4x4 model;
        model.translate(ParallelLightCubePositions[i]);
        float angle = 20.0f * i;
        model.rotate(angle, QVector3D(1.0f, 0.3f, 0.5f));
        parallelLight.model = model;
        parallelLight.updateShapeShader();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    //// Shader Light
    model.setToIdentity();
    model.translate(parallelLight.u_lightDirection);
    model.rotate(1.0, 1.0f, 5.0f, 0.5f);
    model.scale(0.1f);
    parallelLight.model = model;
    parallelLight.updateLightShader();

    glBindVertexArray(VAO_Light02);
    glDrawArrays(GL_TRIANGLES,0,36);
}

void Preview::initPointLightVAO_08()
{
    // 使用initTextureLightVAO_06();即可
}

void Preview::DrawPointLight_08()
{
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    if(isTimeUsed) {
        rotateByTime = m_elapsedTime.elapsed() / 50.0;
    }
    projection.perspective(pCamera_->fov,(float)width()/height(),pCamera_->nearPlane,pCamera_->farPlane);
    view = pCamera_->GetViewMatrix();
    pointLight.projection = projection;
    pointLight.view = view;
    pointLight.u_viewPos = pCamera_->Position;

    glBindVertexArray(VAO_Shape06);
    for(unsigned int i = 0; i < 10; i++) {
        QMatrix4x4 model;
        model.translate(ParallelLightCubePositions[i]);
        float angle = 20.0f * i;
        model.rotate(angle, QVector3D(1.0f, 0.3f, 0.5f));
        pointLight.model = model;
        pointLight.updateShapeShader();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    //// Shader Light
    model.setToIdentity();
    model.translate(pointLight.u_lightPos);
    model.rotate(1.0, 1.0f, 5.0f, 0.5f);
    model.scale(0.1f);
    pointLight.model = model;
    pointLight.updateLightShader();

    glBindVertexArray(VAO_Light02);
    glDrawArrays(GL_TRIANGLES,0,36);
}

void Preview::initSpotLightVAO_09()
{
    // 使用initTextureLightVAO_06();即可
}

void Preview::DrawSpotLight_09()
{
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    if(isTimeUsed) {
        rotateByTime = m_elapsedTime.elapsed() / 50.0;
    }
    projection.perspective(pCamera_->fov,(float)width()/height(),pCamera_->nearPlane,pCamera_->farPlane);
    view = pCamera_->GetViewMatrix();
    spotLight.projection = projection;
    spotLight.view = view;
    spotLight.u_viewPos = pCamera_->Position;

    glBindVertexArray(VAO_Shape06);
    for(unsigned int i = 0; i < 10; i++) {
        QMatrix4x4 model;
        model.translate(ParallelLightCubePositions[i]);
        float angle = 20.0f * i;
        model.rotate(angle, QVector3D(1.0f, 0.3f, 0.5f));
        spotLight.model = model;
        spotLight.updateShapeShader();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    //// Shader Light
    model.setToIdentity();
    model.translate(spotLight.u_light.position);
    model.rotate(1.0, 1.0f, 5.0f, 0.5f);
    model.scale(0.1f);
    spotLight.model = model;
    spotLight.updateLightShader();

    glBindVertexArray(VAO_Light02);
    glDrawArrays(GL_TRIANGLES,0,36);
}

void Preview::initSpotLightSmoothVAO_10()
{
    // 使用initTextureLightVAO_06();即可
}

void Preview::DrawSpotLightSmooth_10()
{
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    if(isTimeUsed) {
        rotateByTime = m_elapsedTime.elapsed() / 50.0;
    }
    projection.perspective(pCamera_->fov,(float)width()/height(),pCamera_->nearPlane,pCamera_->farPlane);
    view = pCamera_->GetViewMatrix();
    spotLightSmooth.projection = projection;
    spotLightSmooth.view = view;
    spotLightSmooth.u_viewPos = pCamera_->Position;

    glBindVertexArray(VAO_Shape06);
    for(unsigned int i = 0; i < 10; i++) {
        QMatrix4x4 model;
        model.translate(ParallelLightCubePositions[i]);
        float angle = 20.0f * i;
        model.rotate(angle, QVector3D(1.0f, 0.3f, 0.5f));
        spotLightSmooth.model = model;
        spotLightSmooth.updateShapeShader();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    //// Shader Light
    model.setToIdentity();
    model.translate(spotLightSmooth.u_light.position);
    model.rotate(1.0, 1.0f, 5.0f, 0.5f);
    model.scale(0.1f);
    spotLightSmooth.model = model;
    spotLightSmooth.updateLightShader();

    glBindVertexArray(VAO_Light02);
    glDrawArrays(GL_TRIANGLES,0,36);
}

void Preview::initMultLightVAO_11()
{
    // 使用initTextureLightVAO_06();即可
}

void Preview::DrawMultLight_11()
{
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    if(isTimeUsed) {
        rotateByTime = m_elapsedTime.elapsed() / 50.0;
    }
    projection.perspective(pCamera_->fov,(float)width()/height(),pCamera_->nearPlane,pCamera_->farPlane);
    view = pCamera_->GetViewMatrix();
    multLight.projection = projection;
    multLight.view = view;
    multLight.u_viewPos = pCamera_->Position;

    glBindVertexArray(VAO_Shape06);
    for(unsigned int i = 0; i < 10; i++) {
        QMatrix4x4 model;
        model.translate(ParallelLightCubePositions[i]);
        float angle = 20.0f * i;
        model.rotate(angle, QVector3D(1.0f, 0.3f, 0.5f));
        multLight.model = model;
        multLight.updateShapeShader();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    //// Shader Light
    for(int i = 0;i < 2;i++){
        model.setToIdentity();
        model.translate(multLight.u_spotLight[i].position);
        model.rotate(1.0, 1.0f, 5.0f, 0.5f);
        model.scale(0.1f);
        multLight.model = model;
        multLight.u_lightColor = multLight.u_spotLight[i].color;
        multLight.updateLightShader();
        glBindVertexArray(VAO_Light02);
        glDrawArrays(GL_TRIANGLES,0,36);

        model.setToIdentity();
        model.rotate(1.0, 1.0f, 5.0f, 0.5f);
        model.scale(0.1f);
        multLight.model = model;
        multLight.u_lightColor = multLight.u_parallelLight[i].color;
        multLight.updateLightShader();
        glBindVertexArray(VAO_Light02);
        glDrawArrays(GL_TRIANGLES,0,36);

        model.setToIdentity();
        model.translate(multLight.u_pointLight[i].position);
        model.rotate(1.0, 1.0f, 5.0f, 0.5f);
        model.scale(0.1f);
        multLight.model = model;
        multLight.u_lightColor = multLight.u_pointLight[i].color;
        multLight.updateLightShader();
        glBindVertexArray(VAO_Light02);
        glDrawArrays(GL_TRIANGLES,0,36);
    }
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
    initTextureLightVAO_06();
    initParallelLightVAO_07();
    initPointLightVAO_08();
    initSpotLightVAO_09();
    initSpotLightSmoothVAO_10();
    initMultLightVAO_11();
    // 5.解绑VBO和VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 2. texture
    textureLight.initTexture();
    parallelLight.initTexture();
    pointLight.initTexture();
    spotLight.initTexture();
    spotLightSmooth.initTexture();
    multLight.initTexture();

    // 3. shader
    axisXYZ.initShader();
    colorObj.initShader();
    phongLight.initShader();
    gouraudLight.initShader();
    material.initShader();
    cyanPlastic.initShader();
    textureLight.initShader();
    parallelLight.initShader();
    pointLight.initShader();
    spotLight.initShader();
    spotLightSmooth.initShader();
    multLight.initShader();
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

    projection.perspective(pCamera_->fov,(float)width()/height(),0.1f,100.0f);
    view=pCamera_->GetViewMatrix();
    if(isTimeUsed) {
        rotateByTime = m_elapsedTime.elapsed() / 50.0;
    }
    model.rotate(rotateByTime, rotationAxis.x(), rotationAxis.y(), rotationAxis.z());
    colorObj.projection = projection;
    colorObj.view = view;
    colorObj.model = model;
    colorObj.updateShapeShader();
    glBindVertexArray(VAO_Shape01);
    glDrawArrays(GL_TRIANGLES,0,36);

    model.setToIdentity();
    model.translate(colorObj.u_lightPos);
    model.scale(0.2f);
    model.rotate(1.0f, rotationAxis.x(), rotationAxis.y(), rotationAxis.z());
    colorObj.model = model;
    colorObj.updateLightShader();
    glBindVertexArray(VAO_Light01);
    glDrawArrays(GL_TRIANGLES,0,36);
}

void Preview::DrawPhongLight_02() {
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    projection.perspective(pCamera_->fov,(float)width()/height(),0.1f,100.0f);
    view=pCamera_->GetViewMatrix();
    if(isTimeUsed) {
        rotateByTime = m_elapsedTime.elapsed() / 50.0;
    }
    model.rotate(rotateByTime, rotationAxis.x(), rotationAxis.y(), rotationAxis.z());
    phongLight.projection = projection;
    phongLight.view = view;
    phongLight.model = model;
    phongLight.u_lightPos.setX(cos(rotateByTime/50)*2.5);
    phongLight.u_lightPos.setZ(sin(rotateByTime/50)*2.5);

    phongLight.u_viewPos = pCamera_->Position;
    phongLight.updateShapeShader();

    glBindVertexArray(VAO_Shape02);
    glDrawArrays(GL_TRIANGLES,0,36);

    model.setToIdentity();
    model.translate(phongLight.u_lightPos);
    model.rotate(1.0f, 1.0f, 5.0f, 0.5f);
    model.scale(0.2f);
    phongLight.model = model;
    phongLight.updateLightShader();
    phongLight.updateDlg();
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
    projection.perspective(pCamera_->fov,(float)width()/height(),0.1f,100.0f);
    view = pCamera_->GetViewMatrix();
    model.rotate(rotateByTime, rotationAxis.x(), rotationAxis.y(), rotationAxis.z());
    gouraudLight.projection = projection;
    gouraudLight.view = view;
    gouraudLight.model = model;
    gouraudLight.u_lightPos.setX(cos(rotateByTime/50)*2.5);
    gouraudLight.u_lightPos.setZ(sin(rotateByTime/50)*2.5);
    gouraudLight.u_viewPos = pCamera_->Position;
    gouraudLight.updateShapeShader();

    glBindVertexArray(VAO_Shape02);
    glDrawArrays(GL_TRIANGLES,0,36);


    model.setToIdentity();
    model.translate(gouraudLight.u_lightPos);
    model.rotate(1.0f, 1.0f, 5.0f, 0.5f);
    model.scale(0.2f);
    gouraudLight.model = model;
    gouraudLight.updateLightShader();
    gouraudLight.updateDlg();

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
    projection.perspective(pCamera_->fov,(float)width()/height(),0.1f,100.0f);
    view = pCamera_->GetViewMatrix();
    model.rotate(rotateByTime, rotationAxis.x(), rotationAxis.y(), rotationAxis.z());
    material.projection = projection;
    material.view = view;
    material.model = model;

    material.u_light.ambient = material.u_light.diffuse * QVector3D(0.2f,0.2f,0.2f);
    material.u_viewPos = pCamera_->Position;
    material.updateShapeShader();
    glBindVertexArray(VAO_Shape02);
    glDrawArrays(GL_TRIANGLES,0,36);

    //// Shader Light
    material.u_lightPos.setX(cos(rotateByTime/50)*2.5);
    material.u_lightPos.setZ(sin(rotateByTime/50)*2.5);
    model.setToIdentity();
    model.translate(material.u_lightPos);
    model.rotate(1.0, 1.0f, 5.0f, 0.5f);
    model.scale(0.2f);
    material.model = model;
    material.updateLightShader();
    material.updateDlg();

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
    projection.perspective(pCamera_->fov,(float)width()/height(),0.1f,100.0f);
    view = pCamera_->GetViewMatrix();
    model.rotate(rotateByTime, rotationAxis.x(), rotationAxis.y(), rotationAxis.z());
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
    case Scene::TextureLight:
        DrawTextureLight_06();
        break;
    case Scene::ParallelLight:
        DrawParallelLight_07();
        break;
    case Scene::PointLight:
        DrawPointLight_08();
        break;
    case Scene::SpotLight:
        DrawSpotLight_09();
        break;
    case Scene::SpotLightSmooth:
        DrawSpotLightSmooth_10();
        break;
    case Scene::MultLight:
        DrawMultLight_11();
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
    colorObj.close();
    phongLight.close();
    gouraudLight.close();
    material.close();
    cyanPlastic.close();
    textureLight.close();
    parallelLight.close();
    pointLight.close();
    spotLight.close();
    spotLightSmooth.close();
    multLight.close();
    currentScene_ = s;
    switch (currentScene_) {
    case Scene::ColorOfObject:
        colorObj.showWindow();
        break;
    case Scene::PhongLight:
        phongLight.showWindow();
        break;
    case Scene::GouraudLight:
        gouraudLight.showWindow();
        break;
    case Scene::Material:
        material.showWindow();
        break;
    case Scene::CyanPlastic:
        //        colorObj.showWindow();
        break;
    case Scene::TextureLight:
        textureLight.showWindow();
        break;
    case Scene::ParallelLight:
        parallelLight.showWindow();
        break;
    case Scene::PointLight:
        pointLight.showWindow();
        break;
    case Scene::SpotLight:
        spotLight.showWindow();
        break;
    case Scene::SpotLightSmooth:
        spotLightSmooth.showWindow();
        break;
    case Scene::MultLight:
        multLight.showWindow();
        break;
    default:
        break;
    }
}
void Preview::on_timeout()
{
    update();
}

void Preview::timeStartStop() {
    isTimeUsed = !isTimeUsed;
}

