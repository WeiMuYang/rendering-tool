QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    modeling/rectangle.cpp \
    modeling/triangle.cpp \
    preview.cpp \
    shader.cpp \
    triangle.cpp \
    vertices.cpp

HEADERS += \
    data_type.h \
    mainwindow.h \
    modeling/rectangle.h \
    modeling/triangle.h \
    preview.h \
    shader.h \
    triangle.h \
    vertices.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
