#include "preview.h"

float verticesTex[] = {
    // positions      | //  colors      | // texture coords
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
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
    currentModelType_ = Module::isTriangle;
    drawMode_ = DrawMode::isFillMode;
//    currrentShaderPro_ = ShaderProgram::Base;
    initVertices();
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

    shaderProRectACol.addShaderFromSourceFile(QOpenGLShader::Vertex,"../shader/rect_aCol.vert");
    shaderProRectACol.addShaderFromSourceFile(QOpenGLShader::Fragment,"../shader/rect_aCol.frag");
    success = shaderProRectACol.link();
    if(!success) {
        qDebug()<<"ERR:"<<shaderProRectACol.log();
    }

//    shaderProRectACol.addShaderFromSourceFile(QOpenGLShader::Vertex,"../shader/rect_tex.vert");
//    shaderProRectACol.addShaderFromSourceFile(QOpenGLShader::Fragment,"../shader/rect_tex.frag");
//    success = shaderProRectACol.link();
//    if(!success) {
//        qDebug()<<"ERR:"<<shaderProRectACol.log();
//    }
}

void Preview::initTexture() {
    textureWall=new QOpenGLTexture(QImage(":/images/images/wall.jpg").mirrored());
    textureSmile=new QOpenGLTexture(QImage(":/images/images/awesomeface.png").mirrored());
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
    // 2. shader
    initShaderProgram();
    // 3. texture
    initTexture();
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
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxis();
    drawModule();
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
    rectanglePosColTex_.setVerticesArr(verticesTex, 4 * ( 3 + 3 + 2) );
    rectanglePosCol_.setIndices(indicesRect, INDICES_RECT_SIZE);
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

void Preview::setUniform(char* uniformName, QVector4D color) {
    makeCurrent();
    shaderProRectUniform.setUniformValue(uniformName ,color.x(), color.y(), color.z(), color.w());
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

