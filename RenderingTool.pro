QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    preview.cpp \
    shader.cpp \
    vertices.cpp

HEADERS += \
    data_type.h \
    mainwindow.h \
    preview.h \
    shader.h \
    vertices.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    shader/axis.frag \
    shader/axis.vert \
    shader/base.frag \
    shader/base.vert \
    shader/base_aCol.frag \
    shader/base_aCol.vert \
    shader/base_uniform.frag \
    shader/base_uniform.vert \
    shader/rect_aCol.frag \
    shader/rect_aCol.vert \
    shader/rect_tex.frag \
    shader/rect_tex.vert \
    shader/rect_tex_filter.frag \
    shader/rect_tex_filter.vert \
    shader/rect_uniform.frag \
    shader/rect_uniform.vert \
    shader/triangle.frag \
    shader/triangle.vert

RESOURCES += \
    img.qrc
