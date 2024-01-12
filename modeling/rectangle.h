#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QObject>

namespace Modeling {

class Rectangle : public QObject
{
    Q_OBJECT
public:
    explicit Rectangle(QObject *parent = nullptr);
    ~Rectangle();

    float* getVertices() {
        return verticesArr_;
    }

    int verticeLength() {
        return verticesLength_;
    }

    int* getIndices() {
        return indices_;
    }

    int indicesLength() {
        return indicesLength_;
    }

signals:

private:

    float* verticesArr_;
    int verticesLength_;

    int* indices_; // 索引信息
    int indicesLength_;
};

}

#endif // RECTANGLE_H
