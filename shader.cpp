#include "shader.h"


Shader::Shader(QObject *parent)
    : QObject{parent}
{

}

Shader::Shader(const QString &vertexShaderPath, const QString &fragmentShaderPath)
{
    setShader(vertexShaderPath, fragmentShaderPath);
}

Shader::~Shader()
{

}

char* Shader::QString2Chars(QString Source) {
    char* fragmentShader = new char[Source.length() + 1];
    std::strcpy(fragmentShader, Source.toUtf8().constData());
    return fragmentShader;
}

QString Shader::loadShaderSource(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open shader file:" << filePath;
        return "";
    }
    QTextStream in(&file);
    return in.readAll();
}

void Shader::setShader(const QString& vertexShaderPath, const QString& fragmentShaderPath)
{
    initializeOpenGLFunctions();
    // 加载顶点着色器和片元着色器源代码
    QString vertexShaderStr = loadShaderSource(vertexShaderPath);
    QString fragmentShaderStr = loadShaderSource(fragmentShaderPath);

    // 创建顶点着色器
    unsigned int vertexShader_id = glCreateShader(GL_VERTEX_SHADER);
    char* vertexShaderSource = QString2Chars(vertexShaderStr);
    glShaderSource(vertexShader_id, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader_id);

    // 创建片段着色器
    unsigned int fragmentShader_id = glCreateShader(GL_FRAGMENT_SHADER);
    char* fragmentShaderSource =QString2Chars(fragmentShaderStr);
    glShaderSource(fragmentShader_id, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader_id);
    // -----------------------------end---------------------------

    // -----------------------三、着色器程序相关----------------------
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader_id);
    glAttachShader(ID, fragmentShader_id);
    glLinkProgram(ID);
    // -----------------------------end---------------------------

    // 删除顶点着色器和片段着色器(不能将着色器程序也给delete掉)
    glDeleteShader(vertexShader_id);
    glDeleteShader(fragmentShader_id);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setFloat(const QString& name, float value)
{
    glUniform1f(glGetUniformLocation(ID,name.toUtf8().constData()), value);
}

void Shader::setVec3(const QString& name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(ID,name.toUtf8().constData()), x, y, z);
}

unsigned int Shader::id()
{
    return ID;
}
