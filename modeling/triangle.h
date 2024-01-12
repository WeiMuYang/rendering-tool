#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include <QVector>

namespace Modeling {

class Triangle : public QObject
{
    Q_OBJECT
public:
    explicit Triangle(QObject *parent = nullptr);
    ~Triangle();

    float* getVertices() {
        return verticesArr_;
    }

    int verticeLength() {
        return verticesLength_;
    }

signals:

private:
    float* verticesArr_;
    int verticesLength_;
};

}

#endif // TRIANGLE_H
