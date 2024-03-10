QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    01-depth-testing/shader/shapes.vert \
    02-depth-testing-precise/shader/shapes-linear.frag \
    02-depth-testing-precise/shader/shapes-linear.vert \
    02-depth-testing-precise/shader/shapes-not-linear.frag \
    02-depth-testing-precise/shader/shapes-not-linear.vert \
    03-mouse-picking/img/container2.png \
    03-mouse-picking/img/matrix.jpg \
    03-mouse-picking/shader/shapes.frag \
    03-mouse-picking/shader/shapes.vert \
    04-load-models/img/wall.jpg \
    04-load-models/shader/shapes.frag \
    04-load-models/shader/shapes.vert \
    05-stencil-outline/shader/shapes.frag \
    05-stencil-outline/shader/shapes.vert \
    05-stencil-outline/shader/singleColor.frag \
    06-discard/img/container2.png \
    06-discard/img/container2_specular.png \
    06-discard/img/grass.png \
    06-discard/shader/shapes.frag \
    06-discard/shader/shapes.vert \
    07-blending/img/blending_transparent_window.png \
    07-blending/shader/shapes.frag \
    07-blending/shader/shapes.vert \
    10-post-processing/shader/blur.frag \
    10-post-processing/shader/shapes.vert \
    10-post-processing/shader/grayscale.frag \
    10-post-processing/shader/inversion.frag \
    10-post-processing/shader/sharpen.frag \
    10-post-processing/shader/weighted.frag \
    11-sky-box/img/skybox/back.jpg \
    11-sky-box/img/skybox/bottom.jpg \
    11-sky-box/img/skybox/front.jpg \
    11-sky-box/img/skybox/left.jpg \
    11-sky-box/img/skybox/right.jpg \
    11-sky-box/img/skybox/top.jpg \
    11-sky-box/shader/reflect-tex.frag \
    11-sky-box/shader/reflect-tex.vert \
    11-sky-box/shader/reflection.frag \
    11-sky-box/shader/reflection.vert \
    11-sky-box/shader/refraction.frag \
    11-sky-box/shader/refraction.vert \
    11-sky-box/shader/shapes.frag \
    11-sky-box/shader/shapes.vert \
    11-sky-box/shader/skybox.frag \
    11-sky-box/shader/skybox.vert


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Assimp/lib/ -lassimp-vc142-mt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Assimp/lib/ -lassimp-vc142-mtd

INCLUDEPATH += $$PWD/../Assimp/include
DEPENDPATH += $$PWD/../Assimp/include
