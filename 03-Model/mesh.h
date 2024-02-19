#ifndef MESH_H
#define MESH_H

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>
#include <string>
#include <vector>
using namespace std;
struct Vertex {
    QVector3D Position;
    QVector3D Normal;
    QVector2D TexCoords;
};
struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    // mesh data
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    void Draw(QOpenGLShaderProgram &shader);
    Mesh(QOpenGLFunctions_3_3_Core *glFuns,
         vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
private:
    // render data
    unsigned int VAO, VBO, EBO;
    void setupMesh();
private:
    // 获取初始后的OpenGL函数指针
    QOpenGLFunctions_3_3_Core *m_glFuns;
};

#endif // DATA_TYPE_H
