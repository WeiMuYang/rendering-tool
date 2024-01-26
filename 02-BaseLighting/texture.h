#ifndef TEXTURE_H
#define TEXTURE_H

#include <QObject>
#include <QOpenGLTexture>

class Texture : public QObject
{
    Q_OBJECT
public:
    explicit Texture(QObject *parent = nullptr);

signals:

private:
    QString name_;
    // 没有默认构造函数，需要通过初始化列表赋初值
    QOpenGLTexture texture_;
};

#endif // TEXTURE_H
