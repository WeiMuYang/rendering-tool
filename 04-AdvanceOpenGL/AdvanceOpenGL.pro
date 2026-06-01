QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += core gui widgets openglwidgets opengl

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    00-axis/axis.cpp \
    01-depth-testing/depth_testing.cpp \
    02-depth-testing-precise/depth_testing_precise.cpp \
    03-mouse-picking/mouse_picking.cpp \
    04-load-models/load_models.cpp \
    05-stencil-outline/stencil_outline.cpp \
    06-discard/discard.cpp \
    07-blending/blending.cpp \
    08-culling/face_culling.cpp \
    09-frame-buffer/frame_buffer.cpp \
    10-post-processing/post_processing.cpp \
    11-sky-box/sky_box.cpp \
    12-advanced-data/modify_data_buffer.cpp \
    13-glsl-variable/glsl_variable.cpp \
    14-interface-block/interface_block.cpp \
    camera.cpp \
    main.cpp \
    mainwindow.cpp \
    mesh.cpp \
    model.cpp \
    preview.cpp

HEADERS += \
    00-axis/axis.h \
    01-depth-testing/depth_testing.h \
    02-depth-testing-precise/depth_testing_precise.h \
    03-mouse-picking/mouse_picking.h \
    04-load-models/load_models.h \
    05-stencil-outline/stencil_outline.h \
    06-discard/discard.h \
    07-blending/blending.h \
    08-culling/face_culling.h \
    09-frame-buffer/frame_buffer.h \
    10-post-processing/post_processing.h \
    11-sky-box/sky_box.h \
    12-advanced-data/modify_data_buffer.h \
    13-glsl-variable/glsl_variable.h \
    14-interface-block/interface_block.h \
    camera.h \
    data_type.h \
    mainwindow.h \
    mesh.h \
    model.h \
    preview.h

FORMS += \
    01-depth-testing/depth_testing.ui \
    02-depth-testing-precise/depth_testing_precise.ui \
    03-mouse-picking/mouse_picking.ui \
    07-blending/blending.ui \
    08-culling/face_culling.ui \
    09-frame-buffer/frame_buffer.ui \
    10-post-processing/post_processing.ui \
    11-sky-box/sky_box.ui \
    12-advanced-data/modify_data_buffer.ui \
    mainwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Assimp/lib/ -lassimp-vc142-mt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Assimp/lib/ -lassimp-vc142-mtd

INCLUDEPATH += $$PWD/../Assimp/include
DEPENDPATH += $$PWD/../Assimp/include

RESOURCES += \
    src.qrc
