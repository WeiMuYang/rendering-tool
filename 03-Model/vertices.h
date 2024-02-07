#ifndef VERTICES_H
#define VERTICES_H

#include <QObject>

class Vertices : public QObject
{
    Q_OBJECT
public:
    explicit Vertices(QObject *parent = nullptr);

    float* getVertices();
    int verticeLength();
    unsigned int* getIndices() ;
    int indicesLength();
    void setVerticesArr(float* arr, int len);
    void setIndices(unsigned int* arr, int len);
signals:

private:

    float* verticesArr_;
    int verticesLength_;

    unsigned int* indices_; // 索引信息
    int indicesLength_;

};

#endif // VERTICES_H
