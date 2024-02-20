QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    00-axis/axis.cpp \
    01-depth-testing/depth_testing.cpp \
    camera.cpp \
    main.cpp \
    mainwindow.cpp \
    mesh.cpp \
    model.cpp \
    preview.cpp

HEADERS += \
    00-axis/axis.h \
    01-depth-testing/depth_testing.h \
    camera.h \
    data_type.h \
    mainwindow.h \
    mesh.h \
    model.h \
    preview.h

FORMS += \
    01-depth-testing/depth_testing.ui \
    mainwindow.ui \

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
    01-depth-testing/img/container2.png \
    01-depth-testing/img/container2_specular.png \
    01-depth-testing/img/matrix.jpg \
    01-depth-testing/shader/light.frag \
    01-depth-testing/shader/light.vert \
    01-depth-testing/shader/shapes.frag \
    01-depth-testing/shader/shapes.vert




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Assimp/lib/ -lassimp-vc142-mt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Assimp/lib/ -lassimp-vc142-mtd

INCLUDEPATH += $$PWD/../Assimp/include
DEPENDPATH += $$PWD/../Assimp/include
