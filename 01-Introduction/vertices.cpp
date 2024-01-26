#include "vertices.h"

Vertices::Vertices(QObject *parent)
    : QObject{parent}
{
    verticesLength_ = 0;
    indicesLength_ = 0;
}

float* Vertices::getVertices() {
    return verticesArr_;
}

int Vertices::verticeLength() {
    return verticesLength_;
}

unsigned int* Vertices::getIndices() {
    return indices_;
}

int Vertices::indicesLength() {
    return indicesLength_;
}

void Vertices::setVerticesArr(float* arr, int len) {
    verticesLength_ = len;
    verticesArr_ = new float[len];
    std::memcpy(verticesArr_, arr, sizeof(float) * len);
}

void Vertices::setIndices(unsigned int* arr, int len){
    indicesLength_ = len;
    indices_ = new unsigned int[len];
    std::memcpy(indices_, arr, sizeof(unsigned int) * len);
}
