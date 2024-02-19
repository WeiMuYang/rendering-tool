#include "preview.h"

QVector3D viewInitPos(0.0,0.0,5.0);

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

    currentScene_ = Scene::Box3D;

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
    box3D.initTexture();
    modelShaderTex.initTexture();
    // 3. shader
    axisXYZ.initShader();
    box3D.initShader();
    modelShaderTex.initShader();

    m_mesh = processMesh();
}

void Preview::resizeGL(int w, int h)
{
    qDebug() << "resizeGL" ;
    Q_UNUSED(w)
    Q_UNUSED(h)
}

void Preview::paintGL()
{

    // 设置窗口颜色，背景颜色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // 打开深度测试，否则立方体形状无法显示立体
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawAxis();
    drawModule();
}

void Preview::DrawBox3D_01()
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
    box3D.projection = projection;
    box3D.view = view;
    box3D.model = model;
    box3D.u_viewPos = pCamera_->Position;
    box3D.updateShapeShader();
    m_mesh->Draw(box3D.shader_Shape);

    //// Shader Light
    model.setToIdentity();
    model.translate(box3D.u_lightPos);
    model.rotate(1.0, 1.0f, 5.0f, 0.5f);
    model.scale(0.2f);
    box3D.model = model;
    box3D.updateLightShader();
    m_mesh->Draw(box3D.shader_Light);
}

void Preview::DrawModel_02() {
    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;
    if(isTimeUsed) {
        rotateByTime = m_elapsedTime.elapsed() / 50.0;
    }
    projection.perspective(pCamera_->fov,(float)width()/height(),pCamera_->nearPlane,pCamera_->farPlane);
    view = pCamera_->GetViewMatrix();
    model.rotate(rotateByTime, rotationAxis.x(), rotationAxis.y(), rotationAxis.z());
    modelShaderTex.projection = projection;
    modelShaderTex.view = view;
    modelShaderTex.model = model;
    modelShaderTex.u_viewPos = pCamera_->Position;
    modelShaderTex.updateShapeShader();
    m_model->Draw(modelShaderTex.shader_Shape);
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

Mesh *Preview::processMesh()
{
    vector<Vertex> _vertices(36);
    vector<unsigned int> _indices;
    vector<Texture> _textures;
    std::memcpy(&_vertices[0], box3D.vertices.data(), box3D.vertices.size() * sizeof(float));
    for(int i = 0; i < 36;i++){
        _indices.push_back(i);
    }

    Texture tex;
    tex.id= box3D.texConrainerDiffuse->textureId();
    tex.type = "texture_diffuse";
    _textures.push_back(tex);
    tex.id= box3D.texConrainerSpecular->textureId();
    tex.type = "texture_specular";
    _textures.push_back(tex);
    return new Mesh(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>()
                    ,_vertices,_indices,_textures);
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
    switch (currentScene_) {
    case Scene::Box3D:
        DrawBox3D_01();
        break;
    case Scene::LoadModel:
        if(m_model==NULL) {
            return;
        }
        DrawModel_02();
        break;
    default:
        break;
    }
}

void Preview::setCurrentScene(Scene s)
{
    currentScene_ = s;
    switch (currentScene_) {
    case Scene::Box3D:
        ;
        break;
    case Scene::LoadModel:
        ;
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
    if(m_model !=NULL)
        delete m_model;

    m_model=NULL;
    makeCurrent();
    m_model = new Model(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>()
                        ,path.c_str());
    pCamera_->Position = cameraPosInit(m_model->m_maxY,m_model->m_minY);
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

