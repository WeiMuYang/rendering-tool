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

    // 3. shader
    axisXYZ.initShader();
    depthTesting.initShader();

    m_CubeMesh = processMesh(depthTesting.cubeVertices, depthTesting.cubeVerCount, depthTesting.cubeTextures);
    m_PlaneMesh = processMesh(depthTesting.planeVertices, depthTesting.planeVerCount, depthTesting.planeTextures);
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

void Preview::setDepthTestingSlot(DepthTestType type) {
    currentDepthTesting_ = type;
    update();
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


// 开始绘制
void Preview::drawModule() {
    switch (currentScene_) {
    case Scene::DepthTestingScene:
        DrawDepthTesting_01();
        break;
        //    case Scene::LoadModel:
        //        if(m_model==NULL) {
        //            return;
        //        }
        //        DrawModel_02();
        //        break;
    default:
        break;
    }
}

void Preview::setCurrentScene(Scene s)
{
    currentScene_ = s;
        switch (currentScene_) {
        case Scene::DepthTestingScene:
            depthTesting.showWindow();
            break;
        case Scene::MousePickingScene:
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

