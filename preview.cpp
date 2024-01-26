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

float verticesTranRotaScale[] = {
    // positions      // colors        // texture coords
    0.3f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
    0.3f, -0.3f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.3f, -0.3f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.3f, 0.3f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
};

float verticesTexFilter[] = {
    // positions      // colors        // texture coords
    0.9f, 0.9f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
    0.9f, -0.9f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.9f, -0.9f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.9f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
};

float verticesTex[] = {
    // positions      // colors        // texture coords
    0.9f, 0.9f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 2.0f, // top right
    0.9f, -0.9f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, -1.0f, // bottom right
    -0.9f, -0.9f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f, -1.0f, // bottom left
    -0.9f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 2.0f // top left
};

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

// 顶点的数据：没有解析的数据是没有意义的
// 内存中的数据，关键是如何将内存中的数据给显卡
float verticesRectPos[VERTICES_RECT_SIZE] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};

float verticesRectPosCol[] = {
    // positions        // colors
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	// top right
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,	// bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 	// bottom left
    -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f,	// top left
};

unsigned int indicesRect[INDICES_RECT_SIZE] = {
    // 注意索引从0开始!
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};

// 顶点的数据：没有解析的数据是没有意义的
// 内存中的数据，关键是如何将内存中的数据给显卡
float verDataTri[9] = {
    // 所有的值是在[-1, 1]之间的
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};

Preview::Preview(QWidget *parent)
    : QOpenGLWidget{parent}
{
    // 获取键盘事件
    setFocusPolicy(Qt::StrongFocus);
    // 获取鼠标事件
    setMouseTracking(true);
    currentModelType_ = Module::isTriangle;
    drawMode_ = DrawMode::isFillMode;
    //    currrentShaderPro_ = ShaderProgram::Base;
    initVertices();

    pCamera_ = new Camera(QVector3D(0,0,3.0));

    connect(pCamera_, &Camera::sigCameraPositionInfo, [&](QVector3D pos){
        emit sigPosition(pos);
    });
    connect(pCamera_, &Camera::sigCameraYawPitchInfo, [&](float yaw, float pitch){
        emit sigYawPitch(yaw, pitch);
    });
    connect(pCamera_, &Camera::sigCameraFrontRightUpInfo, [&](QVector3D f, QVector3D r, QVector3D u,QVector3D wu){
        emit sigFrontRightUp(f, r, u, wu);
    });
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

void Preview::initShaderProgram() {
    bool success;

    shaderProAxis.addShaderFromSourceFile(QOpenGLShader::Vertex,"../shader/axis.vert");
    shaderProAxis.addShaderFromSourceFile(QOpenGLShader::Fragment,"../shader/axis.frag");
    success = shaderProAxis.link();
    if(!success) {
        qDebug()<<"ERR:"<<shaderProAxis.log();
    }

    shaderProTri.addShaderFromSourceFile(QOpenGLShader::Vertex,"../shader/triangle.vert");
    shaderProTri.addShaderFromSourceFile(QOpenGLShader::Fragment,"../shader/triangle.frag");
    success = shaderProTri.link();
    if(!success) {
        qDebug()<<"ERR:"<<shaderProTri.log();
    }

    shaderProRectUniform.addShaderFromSourceFile(QOpenGLShader::Vertex,"../shader/rect_uniform.vert");
    shaderProRectUniform.addShaderFromSourceFile(QOpenGLShader::Fragment,"../shader/rect_uniform.frag");
    success = shaderProRectUniform.link();
    if(!success) {
        qDebug()<<"ERR:"<<shaderProRectUniform.log();
    }
    shaderProRectUniform.bind();
    shaderProRectUniform.setUniformValue("u_Color" ,0, 0, 0, 1);

    shaderProRectACol.addShaderFromSourceFile(QOpenGLShader::Vertex,"../shader/rect_aCol.vert");
    shaderProRectACol.addShaderFromSourceFile(QOpenGLShader::Fragment,"../shader/rect_aCol.frag");
    success = shaderProRectACol.link();
    if(!success) {
        qDebug()<<"ERR:"<<shaderProRectACol.log();
    }

    shaderProRectTex.addShaderFromSourceFile(QOpenGLShader::Vertex,"../shader/rect_tex.vert");
    shaderProRectTex.addShaderFromSourceFile(QOpenGLShader::Fragment,"../shader/rect_tex.frag");

    success = shaderProRectTex.link();
    if(!success) {
        qDebug()<<"ERR:"<<shaderProRectTex.log();
    }
    shaderProRectTex.bind();
    shaderProRectTex.setUniformValue("ratio", 0.5f);
    // 不设置的话编号的，只有0有纹理，最后加载的起作用
    // 设置shader中的uniform对应的编号，将纹理可以在shader中区分开
    shaderProRectTex.setUniformValue("textureWall",0);
    shaderProRectTex.setUniformValue("textureSmile",1);

    shaderProRectTexFilter.addShaderFromSourceFile(QOpenGLShader::Vertex,"../shader/rect_tex_filter.vert");
    shaderProRectTexFilter.addShaderFromSourceFile(QOpenGLShader::Fragment,"../shader/rect_tex_filter.frag");
    success = shaderProRectTexFilter.link();
    if(!success) {
        qDebug()<<"ERR:"<<shaderProRectTexFilter.log();
    }


    shaderProTransRotaScale.addShaderFromSourceFile(QOpenGLShader::Vertex,"../shader/tran_rota_scale.vert");
    shaderProTransRotaScale.addShaderFromSourceFile(QOpenGLShader::Fragment,"../shader/tran_rota_scale.frag");
    success = shaderProTransRotaScale.link();
    if(!success) {
        qDebug()<<"ERR:"<<shaderProTransRotaScale.log();
    }
    shaderProTransRotaScale.bind();
    QMatrix4x4 matrix; // 默认是单位矩阵
    shaderProTransRotaScale.setUniformValue("theMatrix" , matrix);


    shaderProBox3dMVP.addShaderFromSourceFile(QOpenGLShader::Vertex,"../shader/box_3d_mvp.vert");
    shaderProBox3dMVP.addShaderFromSourceFile(QOpenGLShader::Fragment,"../shader/box_3d_mvp.frag");
    success = shaderProBox3dMVP.link();
    if(!success) {
        qDebug()<<"ERR:"<<shaderProBox3dMVP.log();
    }
    shaderProBox3dMVP.bind();
    shaderProBox3dMVP.setUniformValue("textureWall",0);
    shaderProBox3dMVP.setUniformValue("textureSmile",1);
    shaderProBox3dMVP.setUniformValue("textureSmall",2);

    QMatrix4x4 projection;
    projection.perspective(45,(float)width()/height(),0.1f,100);
    shaderProBox3dMVP.setUniformValue("projection", projection);

    QMatrix4x4 view; // 默认是单位矩阵
    view.translate(0.0,0.0,0);
    shaderProBox3dMVP.setUniformValue("view", view);

    QMatrix4x4 model;
    model.setToIdentity();
    model.translate(0.0f, 0.0f, 0.0f);
    model.rotate(30, 1.0f, 0.0f, 0.0f);
    shaderProBox3dMVP.setUniformValue("model", model);
}

void Preview::initTexture() {

    // 打开blend, 让透明起作用
    glEnable(GL_BLEND);
    // alpha通道， 1 - alpha通道
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // CPU端准备好3个纹理，分别对应编号：0 1 2。纹理至少可以支持16个
    textureWall = new QOpenGLTexture(QImage(":/img/wall.jpg").mirrored());
    textureSmile = new QOpenGLTexture(QImage(":/img/awesomeface.png").mirrored());
    textureSmall = new QOpenGLTexture(QImage(":/img/small.png").mirrored());
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
//    glClear(GL_COLOR_BUFFER_BIT);
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
    deltaPos=currentPos-lastPos;
    lastPos=currentPos;

    pCamera_->ProcessMouseMovement(deltaPos.x(),-deltaPos.y());
    update();
}

void Preview::wheelEvent(QWheelEvent *event)
{
    pCamera_->ProcessMouseScroll(event->angleDelta().y()/120);

    update();
}

void Preview::vertexData2VBO() {
    // 初始化调用的，不用添加 makeCurrent
    switch (currentModelType_) {
    case Module::isTriangle:
    {
        // 1.把数据放进 VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * triangle_.verticeLength() , triangle_.getVertices(), GL_STATIC_DRAW);
        // 2.解析数据  a_Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        // 3.开启location = 0的属性解析
        glEnableVertexAttribArray(0);
    }
        break;
    case Module::isRectPos:
    {
        // 1.把数据放进VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * rectanglePos_.verticeLength() , rectanglePos_.getVertices(), GL_STATIC_DRAW);
        // 2.配置EBO相关
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);
        unsigned int* indices = rectanglePos_.getIndices();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * rectanglePos_.indicesLength(), indices, GL_STATIC_DRAW);
        // 3.解析数据  a_Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        // 4.开启location = 0的属性解析
        glEnableVertexAttribArray(0);
    }
        break;
    case Module::isRectPosCol:
    {
        // 1.把数据放进VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * rectanglePosCol_.verticeLength() , rectanglePosCol_.getVertices(), GL_STATIC_DRAW);

        // 6.配置EBO相关
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);
        unsigned int* indices = rectanglePosCol_.getIndices();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * rectanglePosCol_.indicesLength(), indices, GL_STATIC_DRAW);

        // 2.解析数据 a_Postion
        //  GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        // 3.开启VAO管理的第一个属性值 Position 开启location = 0的属性解析
        glEnableVertexAttribArray(0);
        // 4.解析数据 a_Color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        // 5.开启VAO管理的第二个属性值 Color 解析   开启location = 1的属性解析
        glEnableVertexAttribArray(1);

    }
        break;
    case Module::isRectPosColTex:
    {
        // 1.把数据放进VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * rectanglePosColTex_.verticeLength() , rectanglePosColTex_.getVertices(), GL_STATIC_DRAW);

        // 6.配置EBO相关
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);
        unsigned int* indices = rectanglePosColTex_.getIndices();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * rectanglePosColTex_.indicesLength(), indices, GL_STATIC_DRAW);

        // 2.解析数据 a_Postion
        //  GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        // 3.开启VAO管理的第一个属性值 Position 开启location = 0的属性解析
        glEnableVertexAttribArray(0);
        // 4.解析数据 a_Color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // 5.解析数据 a_Texture
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
        break;
    case Module::isRectPosColTexWrap: // 和isRectPosColTex的顶点数据一致
    {
        // 1.把数据放进VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * rectanglePosColTex_.verticeLength() , rectanglePosColTex_.getVertices(), GL_STATIC_DRAW);

        // 6.配置EBO相关
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);
        unsigned int* indices = rectanglePosColTex_.getIndices();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * rectanglePosColTex_.indicesLength(), indices, GL_STATIC_DRAW);

        // 2.解析数据 a_Postion
        //  GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        // 3.开启VAO管理的第一个属性值 Position 开启location = 0的属性解析
        glEnableVertexAttribArray(0);
        // 4.解析数据 a_Color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // 5.解析数据 a_Texture
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
        break;
    case Module::isRectPosColTexFilter:
    {
        // 1.把数据放进VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * rectanglePosColTexFilter_.verticeLength() , rectanglePosColTexFilter_.getVertices(), GL_STATIC_DRAW);

        // 6.配置EBO相关
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);
        unsigned int* indices = rectanglePosColTexFilter_.getIndices();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * rectanglePosColTexFilter_.indicesLength(), indices, GL_STATIC_DRAW);

        // 2.解析数据 a_Postion
        //  GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        // 3.开启VAO管理的第一个属性值 Position 开启location = 0的属性解析
        glEnableVertexAttribArray(0);
        // 4.解析数据 a_Color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // 5.解析数据 a_Texture
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
        break;
    case Module::isRectTranRotaScale:
    {
        // 1.把数据放进VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * rectTranRotatScale_.verticeLength() , rectTranRotatScale_.getVertices(), GL_STATIC_DRAW);

        // 6.配置EBO相关
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);
        unsigned int* indices = rectTranRotatScale_.getIndices();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * rectTranRotatScale_.indicesLength(), indices, GL_STATIC_DRAW);

        // 2.解析数据 a_Postion
        //  GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        // 3.开启VAO管理的第一个属性值 Position 开启location = 0的属性解析
        glEnableVertexAttribArray(0);
        // 4.解析数据 a_Color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // 5.解析数据 a_Texture
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
        break;
    case Module::isBox3dMVP:
    {
        // 1.把数据放进VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * box3dMVPMat_.verticeLength() , box3dMVPMat_.getVertices(), GL_STATIC_DRAW);

        // 6.配置EBO相关
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);
        unsigned int* indices = box3dMVPMat_.getIndices();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * box3dMVPMat_.indicesLength(), indices, GL_STATIC_DRAW);

        // 2.解析数据 a_Postion
        //  GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        // 3.开启VAO管理的第一个属性值 Position 开启location = 0的属性解析
        glEnableVertexAttribArray(0);
        // 5.解析数据 a_Texture
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
        break;
    case Module::isManyBox3d: // 和isBox3dMVP的顶点数据一致
    {
        // 1.把数据放进VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * box3dMVPMat_.verticeLength() , box3dMVPMat_.getVertices(), GL_STATIC_DRAW);

        // 6.配置EBO相关
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);
        unsigned int* indices = box3dMVPMat_.getIndices();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * box3dMVPMat_.indicesLength(), indices, GL_STATIC_DRAW);

        // 2.解析数据 a_Postion
        //  GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        // 3.开启VAO管理的第一个属性值 Position 开启location = 0的属性解析
        glEnableVertexAttribArray(0);
        // 5.解析数据 a_Texture
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }// isManyBox3d
        break;


    case Module::isCameraWSADMouse: // 和isManyBox3d的顶点数据一致
    {
        // 1.把数据放进VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * box3dMVPMat_.verticeLength() , box3dMVPMat_.getVertices(), GL_STATIC_DRAW);

        // 6.配置EBO相关
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);
        unsigned int* indices = box3dMVPMat_.getIndices();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * box3dMVPMat_.indicesLength(), indices, GL_STATIC_DRAW);

        // 2.解析数据 a_Postion
        //  GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        // 3.开启VAO管理的第一个属性值 Position 开启location = 0的属性解析
        glEnableVertexAttribArray(0);
        // 5.解析数据 a_Texture
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }// isManyBox3d
        break;
    default:
        break;
    }
}

void Preview::drawAxis() {
    shaderProAxis.bind();
    glBindVertexArray(VAO_id[0]);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(VAO_id[1]);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(VAO_id[2]);
    glDrawArrays(GL_LINES, 0, 2);
}

void Preview::setWrap(TexWrap texWrap) {
    texWrap_ = texWrap;
    update();
}

void Preview::setMinFilter(TexFilter TexF) {
    texMinFilter_ = TexF;
    update();
}

void Preview::setMagFilter(TexFilter TexF) {
    texMagFilter_ = TexF;
    update();
}

void Preview::texTureWrap() {
    float borderColor[] = {0.5f, 0.0f, 0.4f, 1.0f};
    // REPEAT,        MIRRORED_REPEAT, CLAMP_TO_BORDER, CLAMP_TO_EDGE
    // GL_REPEAT  GL_MIRRORED_REPEAT  GL_CLAMP_TO_BORDER  GL_CLAMP_TO_EDGE
    switch (texWrap_) {
    case REPEAT:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        break;
    case MIRRORED_REPEAT:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        break;
    case CLAMP_TO_BORDER:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        // 边界填充
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        break;
    case CLAMP_TO_EDGE:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        break;
    default:
        break;
    }
}

void Preview::texTureMinFilter() {
    switch (texMinFilter_) {
    case TexFilter::LINEAR:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        break;
    case TexFilter::NEAREST:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        break;
    case TexFilter::NEAREST_MIPMAP_NEAREST:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        break;
    case TexFilter::LINEAR_MIPMAP_NEAREST:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        break;
    case TexFilter:: NEAREST_MIPMAP_LINEAR:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        break;
    case TexFilter:: LINEAR_MIPMAP_LINEAR:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        break;
    default:
        break;
    }
}

void Preview::texTureMagFilter()
{
    // NEAREST,  LINEAR
    switch (texMagFilter_) {
    case TexFilter::LINEAR:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
    case TexFilter::NEAREST:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        break;
    case TexFilter::NEAREST_MIPMAP_NEAREST:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        break;
    case TexFilter::LINEAR_MIPMAP_NEAREST:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        break;
    case TexFilter:: NEAREST_MIPMAP_LINEAR:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        break;
    case TexFilter:: LINEAR_MIPMAP_LINEAR:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        break;
    default:
        break;
    }
}

void Preview::setTexture(Module module) {
    switch (module) {
    case Module::isRectPosColTex:
        shaderProRectTex.bind();

        // 绑定纹理 0 1，shader中可以使用到0 和 1纹理了
        textureWall->bind(0);
        textureSmile->bind(1);
        break;

    case Module::isRectPosColTexWrap:
    {
        shaderProRectTexFilter.bind();
        // GPU端：将shader中的纹理进行区分，同时可以分别对应创建的3个纹理
        shaderProRectTexFilter.setUniformValue("textureWall",0);
        shaderProRectTexFilter.setUniformValue("textureSmile",1);
        shaderProRectTexFilter.setUniformValue("textureSmall",2);
        // 设置textureSmall的纹理
        textureSmall->generateMipMaps();
        textureSmall->bind(2);
        // 设置 Wrap
        texTureWrap();
        // GPU中只有textureSmall起作用
        textureWall->bind(0);
        textureSmile->bind(1);
        textureSmall->bind(2);
        break;
    }
    case Module::isRectPosColTexFilter:
    {
        shaderProRectTexFilter.bind();
        // GPU端：将shader中的纹理进行区分，同时可以分别对应创建的3个纹理
        shaderProRectTexFilter.setUniformValue("textureWall",0);
        shaderProRectTexFilter.setUniformValue("textureSmile",1);
        shaderProRectTexFilter.setUniformValue("textureSmall",2);
        // 设置textureSmall的纹理
        textureSmall->generateMipMaps();
        textureSmall->bind(2);
        // 设置 Wrap
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        // 设置 Filter
        texTureMinFilter();
        texTureMagFilter();
        // GPU中只有textureSmall起作用
        textureWall->bind(0);
        textureSmile->bind(1);
        textureSmall->bind(2);
        break;
    }
    default:
        break;
    }
}


// 开始绘制
void Preview::drawModule() {
    // 使用时还需要再绑定一次
    glBindVertexArray(VAO_id[3]);
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
        shaderProTri.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        break;
    case Module::isRectPos:
        shaderProRectUniform.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        break;
    case Module::isRectPosCol:
        shaderProRectACol.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        break;
    case Module::isRectPosColTex:
        setTexture(Module::isRectPosColTex);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        break;
    case Module::isRectPosColTexWrap:
        setTexture(Module::isRectPosColTexWrap);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        break;
    case Module::isRectPosColTexFilter:
        setTexture(Module::isRectPosColTexFilter);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        break;
    case Module::isRectTranRotaScale:
        shaderProTransRotaScale.bind();
        // 绑定纹理 0 1，shader中可以使用到0 和 1纹理了
        textureWall->bind(0);
        textureSmile->bind(1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        break;
    case Module::isBox3dMVP:
    {
        shaderProBox3dMVP.bind();
        // 绑定纹理 0 1，shader中可以使用到0 和 1纹理了
        textureWall->bind(0);
        //glActiveTexture(GL_TEXTURE1);
        textureSmile->bind(1);
        textureSmall->bind(2);
        shaderProBox3dMVP.setUniformValue("ratio",0.1f);

        glDrawArrays(GL_TRIANGLES,0,36);
    }
        break;
    case Module::isManyBox3d:  //
    {
        shaderProBox3dMVP.bind();
        // 绑定纹理 0 1，shader中可以使用到0 和 1纹理了
        textureWall->bind(0);
        //glActiveTexture(GL_TEXTURE1);
        textureSmile->bind(1);
        textureSmall->bind(2);
        shaderProBox3dMVP.setUniformValue("ratio",0.1f);

        QMatrix4x4 projection;
        projection.perspective(45,(float)width()/height(),0.1f,100);
        shaderProBox3dMVP.setUniformValue("projection", projection);

        QMatrix4x4 view; // 默认是单位矩阵
        view.translate(0.0,0.0,-9.0);
        shaderProBox3dMVP.setUniformValue("view", view);

        QMatrix4x4 model;
        int deg = 0;
        foreach (auto item, BoxPositions) {
            model.setToIdentity();
            model.translate(item);
            model.rotate(deg, 1.0f, 5.0f, 0.5f);
            deg += 30;
            shaderProBox3dMVP.setUniformValue("model", model);
            glDrawArrays(GL_TRIANGLES,0,36);
        }

    }
        break;
    case Module::isCameraWSADMouse:  //
    {
        shaderProBox3dMVP.bind();
        // 绑定纹理 0 1，shader中可以使用到0 和 1纹理了
        textureWall->bind(0);
        //glActiveTexture(GL_TEXTURE1);
        textureSmile->bind(1);
        textureSmall->bind(2);
        shaderProBox3dMVP.setUniformValue("ratio",0.1f);

        QMatrix4x4 projection;
        projection.perspective(pCamera_->Zoom,(float)width()/height(),0.1f,100);
        shaderProBox3dMVP.setUniformValue("projection", projection);

        QMatrix4x4 view; // 默认是单位矩阵
        view.lookAt(pCamera_->Position, pCamera_->Position + pCamera_->Front, pCamera_->Up);
        shaderProBox3dMVP.setUniformValue("view", view);

        QMatrix4x4 model;
        int deg = 0;
        foreach (auto item, BoxPositions) {
            model.setToIdentity();
            model.translate(item);
            model.rotate(deg, 1.0f, 5.0f, 0.5f);
            deg += 30;
            shaderProBox3dMVP.setUniformValue("model", model);
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
    // 三角形
    triangle_.setVerticesArr(verDataTri, 9);
    // 矩形 Pos
    rectanglePos_.setVerticesArr(verticesRectPos, VERTICES_RECT_SIZE);
    rectanglePos_.setIndices(indicesRect, INDICES_RECT_SIZE);
    // 矩形 Pos Col
    rectanglePosCol_.setVerticesArr(verticesRectPosCol, 24);
    rectanglePosCol_.setIndices(indicesRect, INDICES_RECT_SIZE);
    // 矩形 Pos Col Tex
    rectanglePosColTex_.setVerticesArr(verticesTex, 32);
    rectanglePosColTex_.setIndices(indicesRect, INDICES_RECT_SIZE);

    // 矩形 Pos Col Tex
    rectanglePosColTexFilter_.setVerticesArr(verticesTexFilter, 32);
    rectanglePosColTexFilter_.setIndices(indicesRect, INDICES_RECT_SIZE);

    // rectTranRotatScale_
    rectTranRotatScale_.setVerticesArr(verticesTranRotaScale, 32);
    rectTranRotatScale_.setIndices(indicesRect, INDICES_RECT_SIZE);

    // box3dMVPMat_
    box3dMVPMat_.setVerticesArr(vertices3DBox, 180);
    box3dMVPMat_.setIndices(indicesRect, INDICES_RECT_SIZE);
}

void Preview::setModuleType(Module type) {
    currentModelType_ = type;
    makeCurrent();
    setModelVAO();
    update();
    doneCurrent();
}

void Preview::setDrawMode(DrawMode mode) {
    drawMode_ = mode;
    update();
}

void Preview::set_shaderProRectUniform_Uniform(char* uniformName, QVector4D color) {
    makeCurrent();
    shaderProRectUniform.setUniformValue(uniformName ,color.x(), color.y(), color.z(), color.w());
    update();
    doneCurrent();
}


void Preview::set_shaderProTransRotaScale_Uniform(QMatrix4x4 value) {
    makeCurrent();
    shaderProTransRotaScale.setUniformValue("theMatrix" , value);
    update();
    doneCurrent();
}

void Preview::set_shaderProRectTex_Uniform(char* uniformName, float value) {
    makeCurrent();
    shaderProRectTex.setUniformValue(uniformName , value);
    update();
    doneCurrent();
}

void Preview::set_shaderProBox3dMVP_Uniform(char* uniformName, QMatrix4x4 value) {
    makeCurrent();
    if(strcmp(uniformName,"model") == 0){
        value.rotate(30, 1.0f, 0.0f, 0.0f);
    }
    shaderProBox3dMVP.setUniformValue(uniformName , value);
    update();
    doneCurrent();
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

