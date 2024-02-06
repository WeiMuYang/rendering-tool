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
    05-cyan-plastic/cyan_plastic.cpp \
    06-texture-light/texture_light.cpp \
    07-parallel-light/parallel_light.cpp \
    08-point-light/point_light.cpp \
    09-spot-light/spot_light.cpp \
    camera.cpp \
    main.cpp \
    mainwindow.cpp \
    preview.cpp \
    vertices.cpp

HEADERS += \
    00-axis/axis.h \
    01-color-of-object/color_of_object.h \
    02-phong-light/phong_light.h \
    03-gourand-light/gouraud_light.h \
    04-material/material.h \
    05-cyan-plastic/cyan_plastic.h \
    06-texture-light/texture_light.h \
    07-parallel-light/parallel_light.h \
    08-point-light/point_light.h \
    09-spot-light/spot_light.h \
    camera.h \
    data_type.h \
    mainwindow.h \
    preview.h \
    vertices.h

FORMS += \
    01-color-of-object/color_of_object.ui \
    02-phong-light/phong_light.ui \
    03-gourand-light/gouraud_light.ui \
    05-cyan-plastic/cyan_plastic.ui \
    06-texture-light/texture_light.ui \
    07-parallel-light/parallel_light.ui \
    08-point-light/point_light.ui \
    09-spot-light/spot_light.ui \
    mainwindow.ui \
    04-material/material.ui

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
    04-material/shader/shapes.vert \
    05-cyan-plastic/shader/light.frag \
    05-cyan-plastic/shader/light.vert \
    05-cyan-plastic/shader/shapes.frag \
    05-cyan-plastic/shader/shapes.vert \
    06-texture-light/img/awesomeface.png \
    06-texture-light/img/container2.png \
    06-texture-light/img/container2_specular.png \
    06-texture-light/img/lighting_maps_specular_color.png \
    06-texture-light/img/matrix.jpg \
    06-texture-light/img/wall.jpg \
    06-texture-light/shader/light.frag \
    06-texture-light/shader/light.vert \
    06-texture-light/shader/shapes.frag \
    06-texture-light/shader/shapes.vert \
    07-parallel-light/img/awesomeface.png \
    07-parallel-light/img/container2.png \
    07-parallel-light/img/container2_specular.png \
    07-parallel-light/img/lighting_maps_specular_color.png \
    07-parallel-light/img/matrix.jpg \
    07-parallel-light/img/wall.jpg \
    07-parallel-light/shader/light.frag \
    07-parallel-light/shader/light.vert \
    07-parallel-light/shader/shapes.frag \
    07-parallel-light/shader/shapes.vert \
    08-point-light/img/awesomeface.png \
    08-point-light/img/container2.png \
    08-point-light/img/container2_specular.png \
    08-point-light/img/lighting_maps_specular_color.png \
    08-point-light/img/matrix.jpg \
    08-point-light/img/wall.jpg \
    08-point-light/shader/light.frag \
    08-point-light/shader/light.vert \
    08-point-light/shader/shapes.frag \
    08-point-light/shader/shapes.vert \
    09-spot-light/img/container2.png \
    09-spot-light/img/container2_specular.png \
    09-spot-light/img/lighting_maps_specular_color.png \
    09-spot-light/shader/light.frag \
    09-spot-light/shader/light.vert \
    09-spot-light/shader/shapes.frag \
    09-spot-light/shader/shapes.vert


