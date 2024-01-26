QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera.cpp \
    main.cpp \
    mainwindow.cpp \
    preview.cpp \
    shader.cpp \
    texture.cpp \
    vertices.cpp

HEADERS += \
    camera.h \
    data_type.h \
    mainwindow.h \
    preview.h \
    shader.h \
    texture.h \
    vertices.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    shader/ColorOfObject_light - 副本.frag \
    shader/ColorOfObject_light - 副本.vert \
    shader/ColorOfObject_light.frag \
    shader/ColorOfObject_light.vert \
    shader/ColorOfObject_shapes - 副本.frag \
    shader/ColorOfObject_shapes - 副本.vert \
    shader/ColorOfObject_shapes.frag \
    shader/ColorOfObject_shapes.vert \
    shader/axis_X.frag \
    shader/axis_X.vert \
    shader/axis_Y.frag \
    shader/axis_Y.vert \
    shader/axis_Z.frag \
    shader/axis_Z.vert
