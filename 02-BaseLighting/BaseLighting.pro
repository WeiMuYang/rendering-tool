QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core openglwidgets

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
    10-spot-light-smooth/spot_light_smooth.cpp \
    11-mult-light/mult_light.cpp \
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
    10-spot-light-smooth/spot_light_smooth.h \
    11-mult-light/mult_light.h \
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
    10-spot-light-smooth/spotlightsmooth.ui \
    11-mult-light/mult_light.ui \
    mainwindow.ui \
    04-material/material.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    00-axis/axis.qrc \
    01-color-of-object/color-of-object.qrc \
    02-phong-light/phong-light.qrc \
    03-gourand-light/gouraud_light.qrc \
    04-material/material.qrc \
    05-cyan-plastic/cyan_plastic.qrc \
    06-texture-light/texture_light.qrc \
    07-parallel-light/parallel_light.qrc \
    08-point-light/point_light.qrc \
    09-spot-light/spot_light.qrc \
    10-spot-light-smooth/spot_light_smooth.qrc \
    11-mult-light/mult_light.qrc


