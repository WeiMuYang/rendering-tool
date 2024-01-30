QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    00-axis/axis.cpp \
    01-color-of-object/color_of_object.cpp \
    02-phong-light/phong_light.cpp \
    03-gourand-light/gouraud_light.cpp \
    04-material/material.cpp \
    camera.cpp \
    main.cpp \
    mainwindow.cpp \
    preview.cpp \
    texture.cpp \
    vertices.cpp

HEADERS += \
    00-axis/axis.h \
    01-color-of-object/color_of_object.h \
    02-phong-light/phong_light.h \
    03-gourand-light/gouraud_light.h \
    04-material/material.h \
    camera.h \
    data_type.h \
    mainwindow.h \
    preview.h \
    texture.h \
    vertices.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    00-axis/shader/axis_X.frag \
    00-axis/shader/axis_X.vert \
    00-axis/shader/axis_Y.frag \
    00-axis/shader/axis_Y.vert \
    00-axis/shader/axis_Z.frag \
    00-axis/shader/axis_Z.vert \
    01-color-of-object/shader/ColorOfObject_light.frag \
    01-color-of-object/shader/ColorOfObject_light.vert \
    01-color-of-object/shader/ColorOfObject_shapes.frag \
    01-color-of-object/shader/ColorOfObject_shapes.vert \
    02-phong-light/shader/light.frag \
    02-phong-light/shader/light.vert \
    02-phong-light/shader/shapes.frag \
    02-phong-light/shader/shapes.vert \
    03-gourand-light/shader/light.frag \
    03-gourand-light/shader/light.vert \
    03-gourand-light/shader/shapes.frag \
    03-gourand-light/shader/shapes.vert \
    04-material/shader/light.frag \
    04-material/shader/light.vert \
    04-material/shader/shapes.frag \
    04-material/shader/shapes.vert

