#include "preview.h"

QVector3D viewInitPos(0.0f,0.0f,6.0f);

QPoint lastPos;



unsigned int fbo;
unsigned int rbo;
unsigned int texture; // 帧缓冲纹理

Preview::Preview(QWidget *parent)
    : QOpenGLWidget{parent}
{
    // 获取键盘事件
    setFocusPolicy(Qt::StrongFocus);
    // 获取鼠标事件
    setMouseTracking(true);
    // 初始化镜头位置
    pCamera_ = new Camera(viewInitPos);
    pCamera_->fov = 45.0f;
    pCamera_->aspectRatio = (float)width()/height();
    pCamera_->nearPlane = 0.1f;
    pCamera_->farPlane = 100.0f;

    currentScene_ = Scene::DepthTestingScene;
    currentDepthTesting_ = DepthTestType::LESS;

    rotationAxis = {1.0f, 1.0f, 0.5f};

    connect(&m_timer,SIGNAL(timeout()),this,SLOT(on_timeout()));
    m_timer.start(50);
    m_elapsedTime.start();

    connect(&depthTesting, &DepthTesting::sigChangeDepthTest, this, &Preview::setDepthTestingSlot);
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
    float verticesAxisX1[] = {
        1.0f, 0.0f, 0.0f,   // x+1
        -1.0f, 0.0f, 0.0f,  // x-1
    };
    float verticesAxisY1[] = {
        0.0f, 1.0f, 0.0f,   // y+1
        0.0f, -1.0f, 0.0f,  // y-1
    };
    float verticesAxisZ1[] = {
        0.0f, 0.0f, 1.0f,   // z+1
        0.0f, 0.0f, -1.0f,  // z-1
    };
    glGenVertexArrays(3, VAO_Axis);
    glGenBuffers(3, VBO_Axis);
    // 绘制坐标轴 X
    glBindVertexArray(VAO_Axis[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Axis[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 , verticesAxisX1,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 绘制坐标轴 Y
    glBindVertexArray(VAO_Axis[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Axis[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 , verticesAxisY1 ,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 绘制坐标轴 Z
    glBindVertexArray(VAO_Axis[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Axis[2]);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(float) * 6 , verticesAxisZ1 ,GL_STATIC_DRAW);
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
    depthTesting.initTexture();
    mousePicking.initTexture();
    loadModels.initTexture();
    discard.initTexture();
    blending.initTexture();

    // 帧缓冲，相当于将画面放到一个纹理中
    frameBuffer.initFrameBufferTex(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>(), width(), height());
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());

    // 3. shader
    axisXYZ.initShader();
    depthTesting.initShader();
    depthTestingPrecise.initShader();
    mousePicking.initShader();
    loadModels.initShader();
    stencilOutLine.initShader();
    discard.initShader();
    blending.initShader();
    frameBuffer.initShader();

    m_CubeMesh = processMesh(depthTesting.cubeVertices, depthTesting.cubeVerCount, depthTesting.cubeTextures);
    m_PlaneMesh = processMesh(depthTesting.planeVertices, depthTesting.planeVerCount, depthTesting.planeTextures);
    m_grassMesh = processMesh(discard.grassVertices, discard.grassVerCount, discard.cubeTextures);
    m_blendingMesh = processMesh(discard.grassVertices, discard.grassVerCount, blending.cubeTextures);
    m_frameBufferMesh = processMesh(frameBuffer.frameBufferVertices, frameBuffer.frameBufferVerCount, frameBuffer.FrameBufferTex);
}

void Preview::resizeGL(int w, int h)
{
    qDebug() << "resizeGL" ;
    Q_UNUSED(w)
    Q_UNUSED(h)
}

void Preview::DepthTesting(DepthTestType depthType) {

    switch (depthType) {
    case DepthTestType::None:
        glClear(GL_COLOR_BUFFER_BIT);
        break;
    case DepthTestType::LESS:
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        break;
    case DepthTestType::ALWAYS:
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        break;
    case DepthTestType::EQUAL:
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_EQUAL);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        break;
    case DepthTestType::GEQUAL:
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_GEQUAL);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        break;
    case DepthTestType::GREATER:
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_GREATER);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        break;
    case DepthTestType::LEQUAL:
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        break;
    case DepthTestType::NEVER:
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_NEVER);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        break;
    case DepthTestType::NOTEQUAL:
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_NOTEQUAL);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        break;
    default:
        break;
    }
}

void Preview::DrawDepthTestingPrecise_02()
{
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    projection.perspective(pCamera_->fov,(float)width()/height(),pCamera_->nearPlane,pCamera_->farPlane);
    view = pCamera_->GetViewMatrix();
    depthTestingPrecise.projection = projection;
    depthTestingPrecise.view = view;
    depthTestingPrecise.updateShapeShader();
    m_CubeMesh->Draw(*depthTestingPrecise.current_Shader_Shape);
    m_PlaneMesh->Draw(*depthTestingPrecise.current_Shader_Shape);
}

void Preview::DrawMousePicking_03() {
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    projection.perspective(pCamera_->fov,(float)width()/height(),pCamera_->nearPlane,pCamera_->farPlane);
    view = pCamera_->GetViewMatrix();
    mousePicking.projection = projection;
    mousePicking.view = view;
    mousePicking.u_viewPos = pCamera_->Position;
    mousePicking.updateShapeShader();
    m_CubeMesh->Draw(mousePicking.shader_Shape);
    m_PlaneMesh->Draw(mousePicking.shader_Shape);
}


void Preview::DrawLoadModelsControl_04() {
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    projection.perspective(pCamera_->fov,(float)width()/height(),pCamera_->nearPlane,pCamera_->farPlane);
    view = pCamera_->GetViewMatrix();
    depthTesting.projection = projection;
    depthTesting.view = view;
    depthTesting.u_viewPos = pCamera_->Position;

    depthTesting.projection = projection;
    depthTesting.view = view;


    depthTesting.updateShapeShader();
    m_PlaneMesh->textures[0] = loadModels.texPlane; // 修改Plane原来的纹理图片
    m_PlaneMesh->Draw(depthTesting.shader_Shape);

    loadModels.projection = projection;
    loadModels.view = view;
    loadModels.u_viewPos = pCamera_->Position;
    foreach(auto modelInfo, m_Models){
        model.setToIdentity();
        model.translate(modelInfo.worldPos);
        model.rotate(modelInfo.pitch,QVector3D(1.0,0.0,0.0));
        model.rotate(modelInfo.yaw,QVector3D(0.0,1.0,0.0));
        model.rotate(modelInfo.roll,QVector3D(0.0,0.0,1.0));
        loadModels.model = model;
        loadModels.updateShapeShader();
        // 所有的模型都只用这一套shader即可
        modelInfo.model->Draw(loadModels.shader_Shape);
    }
}

void Preview::DrawStencilOutLineControl_05() {
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glStencilMask(0x00);

    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    projection.perspective(pCamera_->fov,(float)width()/height(),pCamera_->nearPlane,pCamera_->farPlane);
    view = pCamera_->GetViewMatrix();
    depthTesting.projection = projection;
    depthTesting.view = view;
    depthTesting.u_viewPos = pCamera_->Position;

    depthTesting.projection = projection;
    depthTesting.view = view;

    depthTesting.updateShapeShader();
    m_PlaneMesh->textures[0] = loadModels.texPlane; // 修改Plane原来的纹理图片
    m_PlaneMesh->Draw(depthTesting.shader_Shape);

    stencilOutLine.projection = projection;
    stencilOutLine.view = view;
    stencilOutLine.u_viewPos = pCamera_->Position;
    foreach(auto modelInfo, m_Models){
        model.setToIdentity();
        model.translate(modelInfo.worldPos);
        model.rotate(modelInfo.pitch,QVector3D(1.0,0.0,0.0));
        model.rotate(modelInfo.yaw,QVector3D(0.0,1.0,0.0));
        model.rotate(modelInfo.roll,QVector3D(0.0,0.0,1.0));
        stencilOutLine.model = model;
        stencilOutLine.model = model;
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
        stencilOutLine.updateShapeShader();
        // 所有的模型都只用这一套shader即可
        modelInfo.model->Draw(stencilOutLine.shader_Shape);
        stencilOutLine.shader_Shape.release();

        if(modelInfo.isSelected==false)
            continue;
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        float height=modelInfo.model->m_maxY-modelInfo.model->m_minY;
        float width=modelInfo.model->m_maxX-modelInfo.model->m_minX;
        if(modelInfo.model->m_minY>=0)
            model.translate(0.0f,height/2,0.0f);
        model.scale(1.1f,1.0+0.1*(width/height));
        if(modelInfo.model->m_minY>=0)
            model.translate(0.0f,-height/2,0.0f);

        stencilOutLine.model = model;
        stencilOutLine.updateOutLineShader();
        modelInfo.model->Draw(stencilOutLine.shader_Outline);
        stencilOutLine.shader_Outline.release();
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
    }
}

void Preview::setDepthTestingSlot(DepthTestType type) {
    currentDepthTesting_ = type;
    update();
}

void Preview::mousePressEvent(QMouseEvent *event)
{
    bool hasSelected=false;
    makeCurrent();
    lastPos=event->pos();
    if(event->buttons()&Qt::LeftButton){
        QVector4D worldPosition = worldPosFromViewPort(event->pos().x(), event->pos().y());
        emit mousePickingPos(QVector3D(worldPosition));
        // 判断选取模型
        for(QMap<QString, ModelInfo>::iterator iter=m_Models.begin();iter != m_Models.end();iter++){
            ModelInfo* modelInfo = &iter.value();
            float r = (modelInfo->model->m_maxY - modelInfo->model->m_minY) / 2; // 选取球体半径
            if(modelInfo->worldPos.distanceToPoint(QVector3D(worldPosition)) < r && !hasSelected){
                modelInfo->isSelected = true;
                hasSelected = true;
            } else {
                modelInfo->isSelected = false;
            }
        }
    }
    doneCurrent();
}

// 鼠标点击像素对应的世界坐标
QVector4D Preview::worldPosFromViewPort(int posX, int posY)
{
    PickingPixelData pickingPixelData;
    float winZ;
    // 获取深度值 winZ
    glReadPixels(
                posX,
                this->height()-posY
                ,1,1
                ,GL_DEPTH_COMPONENT,GL_FLOAT
                ,&winZ);
    // 标准化到 -1,1  NDC坐标
    float x = (2.0f*posX)/this->width()-1.0f;
    float y = 1.0f-(2.0f*posY)/this->height();
    float z = winZ * 2.0 - 1.0f;

    // w：眼睛到单击点的距离，通过像素的深度值可以求得
    float w = (2.0 * pCamera_->nearPlane * pCamera_->farPlane) / (pCamera_->farPlane + pCamera_->nearPlane - z * (pCamera_->farPlane - pCamera_->nearPlane));
    //float w= _near*_far/(_near*winZ-_far*winZ+_far);
    QVector4D wolrdPostion(x,y,z,1);

    pickingPixelData.MousePressPos.setX(posX);
    pickingPixelData.MousePressPos.setY(posY);
    pickingPixelData.PixelZ = winZ;
    pickingPixelData.PixelW = w;

    // 乘以w获得 裁剪空间中的值
    wolrdPostion = w * wolrdPostion;

    pickingPixelData.ClipPos = wolrdPostion;

    QMatrix4x4 projection;
    QMatrix4x4 view;
    projection.perspective(pCamera_->fov,(float)width()/height(),pCamera_->nearPlane,pCamera_->farPlane);
    view = pCamera_->GetViewMatrix();

    QVector4D worldPosition = view.inverted() * projection.inverted() * wolrdPostion;

    pickingPixelData.WorldPos = worldPosition;

    mousePicking.pickingPixelData = pickingPixelData;
    mousePicking.updateDlg();
    // 回到 视口坐标  →   世界坐标
    return worldPosition;
}

void Preview::paintGL()
{
    // 设置窗口颜色，背景颜色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // 打开深度测试，否则立方体形状无法显示立体
    DepthTesting(currentDepthTesting_);

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
    makeCurrent();
    if(m_modelMoving){
        for(auto iter=m_Models.begin();iter!=m_Models.end();iter++){
            ModelInfo *modelInfo=&iter.value();
            if(!modelInfo->isSelected) continue;
            modelInfo->worldPos=
                    QVector3D(worldPosFromViewPort(event->pos().x(),event->pos().y()));
        }
    }else
        if(event->buttons() & Qt::RightButton
                || event->buttons() & Qt::LeftButton
                || event->buttons() & Qt::MiddleButton){

            auto currentPos=event->pos();
            QPoint deltaPos=currentPos - lastPos;
            lastPos=currentPos;
            if(event->buttons() & Qt::RightButton)
                pCamera_->ProcessMouseMovement(deltaPos.x(),-deltaPos.y());
            else
                for(auto iter=m_Models.begin();iter!=m_Models.end();iter++){
                    ModelInfo *modelInfo=&iter.value();
                    if(!modelInfo->isSelected)
                        continue;
                    if(event->buttons() & Qt::MiddleButton){
                        modelInfo->roll+=deltaPos.x();
                    }
                    else if(event->buttons() & Qt::LeftButton){
                        modelInfo->yaw+=deltaPos.x();
                        modelInfo->pitch+=deltaPos.y();
                    }
                }

        }
    doneCurrent();
}

void Preview::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(m_modelMoving){
        //再次双击取消移动
        m_modelMoving = false;
    }else
        foreach(auto modelInfo, m_Models) {
            //双击启动移动
            if(modelInfo.isSelected) {
                m_modelMoving=true;
            }
            qDebug()<<modelInfo.name<<modelInfo.isSelected;
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

void Preview::DrawDepthTesting_01(){
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    projection.perspective(pCamera_->fov,(float)width()/height(),pCamera_->nearPlane,pCamera_->farPlane);
    view = pCamera_->GetViewMatrix();
    depthTesting.projection = projection;
    depthTesting.view = view;
    depthTesting.u_viewPos = pCamera_->Position;
    depthTesting.updateShapeShader();
    m_CubeMesh->Draw(depthTesting.shader_Shape);
    m_PlaneMesh->Draw(depthTesting.shader_Shape);
}

void Preview::DrawDiscard_06(){
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    projection.perspective(pCamera_->fov,(float)width()/height(),pCamera_->nearPlane,pCamera_->farPlane);
    view = pCamera_->GetViewMatrix();
    discard.projection = projection;
    discard.view = view;

    foreach (auto item, discard.vegetation) {
        model.setToIdentity();
        model.translate(item);
        discard.model = model;
        discard.updateDiscardShader();
        m_grassMesh->Draw(discard.shader_Shape);
    }
}


void Preview::openBlending() {
    glEnable(GL_BLEND);
    glBlendFunc(blending.srcBlending, blending.desBlending);
}



void Preview::DrawBlending_07()
{
    openBlending();

    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    projection.perspective(pCamera_->fov,(float)width()/height(),pCamera_->nearPlane,pCamera_->farPlane);
    view = pCamera_->GetViewMatrix();
    blending.projection = projection;
    blending.view = view;
    // 1. 先渲染不透明的物理Model，再渲染半透明的物体
    depthTesting.projection = projection;
    depthTesting.view = view;
    depthTesting.u_viewPos = pCamera_->Position;
    depthTesting.updateShapeShader();
    m_CubeMesh->Draw(depthTesting.shader_Shape);

    // 2. 半透明混合时需要有先后次序，根据距离镜头的远近排序: 距离镜头越近需要后面渲染
    map<float, QVector3D> sorted;
    foreach(auto item,discard.vegetation) {
        float distance = pCamera_->Position.distanceToPoint(item);
        sorted[distance] = item;
    }

    for(map<float, QVector3D>::reverse_iterator riter = sorted.rbegin();
        riter != sorted.rend(); riter++){
        model.setToIdentity();
        model.translate(riter->second);
        blending.model = model;
        blending.updateBlendingShader();
        m_blendingMesh->Draw(blending.shader_Shape);
    }
}

void Preview::openFaceCulling() {
    // 开启面剔除: 默认剔除反面
    glEnable(GL_CULL_FACE);
    // 剔除方式
    glCullFace(faceCulling.cullingType);
    // 正面判断规则
    glFrontFace(faceCulling.cullingOri);
}

void Preview::DrawCulling_08() {
    openBlending();
    openFaceCulling();

    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    projection.perspective(pCamera_->fov,(float)width()/height(),pCamera_->nearPlane,pCamera_->farPlane);
    view = pCamera_->GetViewMatrix();
    blending.projection = projection;
    blending.view = view;
    // 1. 先渲染不透明的物理Model，再渲染半透明的物体
    depthTesting.projection = projection;
    depthTesting.view = view;
    depthTesting.u_viewPos = pCamera_->Position;
    depthTesting.updateShapeShader();
    m_CubeMesh->Draw(depthTesting.shader_Shape);
    m_PlaneMesh->Draw(depthTesting.shader_Shape);

    // 2. 半透明混合时需要有先后次序，根据距离镜头的远近排序: 距离镜头越近需要后面渲染
    map<float, QVector3D> sorted;
    foreach(auto item,discard.vegetation) {
        float distance = pCamera_->Position.distanceToPoint(item);
        sorted[distance] = item;
    }

    for(map<float, QVector3D>::reverse_iterator riter = sorted.rbegin();
        riter != sorted.rend(); riter++){
        model.setToIdentity();
        model.translate(riter->second);
        blending.model = model;
        blending.updateBlendingShader();
        m_blendingMesh->Draw(blending.shader_Shape);
    }
}

void Preview::DrawFrameBuffer_09() {
    openBlending();

    // first pass: 渲染到帧缓中
glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer.fbo);
// 打开深度测试
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    QMatrix4x4 projection;
    QMatrix4x4 view; // 默认是单位矩阵
    QMatrix4x4 model;

    projection.perspective(pCamera_->fov,(float)width()/height(),pCamera_->nearPlane,pCamera_->farPlane);
    view = pCamera_->GetViewMatrix();
    frameBuffer.projection = projection;
    frameBuffer.view = view;
    // 1. 先渲染不透明的物理Model，再渲染半透明的物体
    depthTesting.projection = projection;
    depthTesting.view = view;
    depthTesting.u_viewPos = pCamera_->Position;
    depthTesting.updateShapeShader();
    m_PlaneMesh->Draw(depthTesting.shader_Shape);

    loadModels.projection = projection;
    loadModels.view = view;
    loadModels.u_viewPos = pCamera_->Position;
    foreach(auto modelInfo, m_Models){
        model.setToIdentity();
        model.translate(modelInfo.worldPos);
        model.rotate(modelInfo.pitch,QVector3D(1.0,0.0,0.0));
        model.rotate(modelInfo.yaw,QVector3D(0.0,1.0,0.0));
        model.rotate(modelInfo.roll,QVector3D(0.0,0.0,1.0));
        loadModels.model = model;
        loadModels.updateShapeShader();
        // 所有的模型都只用这一套shader即可
        modelInfo.model->Draw(loadModels.shader_Shape);
    }

    // second pass： 渲染到屏幕
    glBindFramebuffer(GL_FRAMEBUFFER,defaultFramebufferObject() ); // back to default
    depthTesting.updateShapeShader();
    m_PlaneMesh->Draw(depthTesting.shader_Shape);

    foreach(auto modelInfo, m_Models){
        model.setToIdentity();
        model.translate(modelInfo.worldPos);
        model.rotate(modelInfo.pitch,QVector3D(1.0,0.0,0.0));
        model.rotate(modelInfo.yaw,QVector3D(0.0,1.0,0.0));
        model.rotate(modelInfo.roll,QVector3D(0.0,0.0,1.0));
        loadModels.model = model;
        loadModels.updateShapeShader();
        // 所有的模型都只用这一套shader即可
        modelInfo.model->Draw(loadModels.shader_Shape);
    }

    model.setToIdentity();
    model.translate(0.0f, 2.5f, -25.0f);
    frameBuffer.model = model;
    frameBuffer.updateFrameBufferShader();
    if(frameBuffer.isFrameBuffer) {
        m_frameBufferMesh->textures = frameBuffer.FrameBufferTex;
    } else{
        m_frameBufferMesh->textures = blending.cubeTextures;
    }
    m_frameBufferMesh->Draw(frameBuffer.shader_Shape);
}

// 开始绘制
void Preview::drawModule() {
    switch (currentScene_) {
    case Scene::DepthTestingScene:
        DrawDepthTesting_01();
        break;
    case Scene::DepthTestingPreciseScene:
        DrawDepthTestingPrecise_02();
        break;
    case Scene::MousePickingScene:
        DrawMousePicking_03();
        break;
    case Scene::ModelsControlScene:
        DrawLoadModelsControl_04();
        break;
    case Scene::StencilOutLineScene:
        DrawStencilOutLineControl_05();
        break;
    case Scene::DisCardScene:
        DrawDiscard_06();
        break;
    case Scene::BlendingScene:
        DrawBlending_07();
        break;
    case Scene::FaceCullingScene:
        DrawCulling_08();
        break;
    case Scene::FrameBufferScene:
        DrawFrameBuffer_09();
        break;
    default:
        break;
    }

}

void Preview::setCurrentScene(Scene s)
{
    currentScene_ = s;
    depthTesting.close();
    depthTestingPrecise.close();
    mousePicking.close();
    blending.close();
    faceCulling.close();
    frameBuffer.close();
    switch (currentScene_) {
    case Scene::DepthTestingScene:
        depthTesting.showWindow();
        break;
    case Scene::DepthTestingPreciseScene:
        depthTestingPrecise.showWindow();
        break;
    case Scene::MousePickingScene:
        mousePicking.showWindow();
        break;
    case Scene::BlendingScene:
        blending.showWindow();
        break;
    case Scene::FaceCullingScene:
        faceCulling.showWindow();
        break;
    case Scene::FrameBufferScene:
        frameBuffer.showWindow();
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

void Preview::loadModel(string path)
{
    static int i = 0;
    makeCurrent();
    Model * _model = new Model(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>()
                               ,path.c_str());
    pCamera_->Position = cameraPosInit(_model->m_maxY ,_model->m_minY);
    m_Models["模型" + QString::number(i++)]=
            ModelInfo{_model,QVector3D(0,0 - _model->m_minY, 0),0.0,0.0,0.0,false,"模型"};
    doneCurrent();
}

QVector3D Preview::cameraPosInit(float maxY, float minY)
{
    QVector3D temp={0,0,0};
    float height=maxY-minY;
    temp.setZ(1.5*height);
    if(minY>=0) {
        temp.setY(height/2.0);
    }
    viewInitPos=temp;
    return temp;
}

Mesh *Preview::processMesh(std::vector<float> vertices,int size, vector<Texture> textures)
{
    vector<Vertex> _vertices;
    vector<unsigned int> _indices;
    //    std::memcpy(&_vertices[0], vertices.data(), vertices.size() * sizeof(float));  没有Normal数据，需要手动添加

    for(int i = 0; i < size;i++){
        Vertex vert;
        vert.Position[0]=vertices.at(i*5+0);
        vert.Position[1]=vertices.at(i*5+1);
        vert.Position[2]=vertices.at(i*5+2);
        vert.TexCoords[0]=vertices.at(i*5+3);
        vert.TexCoords[1]=vertices.at(i*5+4);
        _vertices.push_back(vert);
        _indices.push_back(i);
    }

    return new Mesh(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>()
                    ,_vertices,_indices,textures);
}

