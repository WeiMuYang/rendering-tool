#include "texture.h"

Texture::Texture(QObject *parent)
    : QObject{parent}, texture_(QOpenGLTexture::Target2D)
{

}
