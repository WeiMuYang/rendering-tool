#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(QSize(1400, 800));

    ui->PreviewWgt->setCurrentScene(Scene::DepthTestingScene);
    // 不用给preview创建对象，因为是采用提升的方式创建的PreviewWgt
    // 只需要通过ui->PreviewWgt，就可以找到Preview的属性成员
    initAction();

    ui->statusbar->setStyleSheet("font: 14pt ");
    ui->statusbar->showMessage(" 世界坐标:    X:"
                               +QString::number(0,'f', 2)
                               +" Y:"+QString::number(0,'f', 2)
                               +" Z:"+QString::number(0,'f', 2)
                               );
}

MainWindow::~MainWindow()
{
    delete ui;
}

template<typename T>
void MainWindow::connectSceneAction(T action, Scene scene) {
    connect(action, &QAction::triggered, this, [this, scene]() {
        ui->PreviewWgt->setCurrentScene(scene);
    });
}

void MainWindow::initAction() {
    ui->actionTimer->setShortcut(QKeySequence("Space"));
    connect(ui->actionTimer, &QAction::triggered,this , [this]() {
        ui->PreviewWgt->timeStartStop();
    });
    connectSceneAction(ui->actionDepthTesting, Scene::DepthTestingScene);
    connectSceneAction(ui->actiondepthTestingPrecise, Scene::DepthTestingPreciseScene);
    connectSceneAction(ui->actionMousePicking, Scene::MousePickingScene);
    connectSceneAction(ui->actionModels, Scene::ModelsControlScene);
    connectSceneAction(ui->actionStencilOutLine, Scene::StencilOutLineScene);
    connectSceneAction(ui->actionDiscard, Scene::DisCardScene);
    connectSceneAction(ui->actionBlending, Scene::BlendingScene);
    connectSceneAction(ui->actionCulling, Scene::FaceCullingScene);
    connectSceneAction(ui->actionFrameBuffer, Scene::FrameBufferScene);
    connectSceneAction(ui->actionPostProcessing, Scene::PostProcessingScene);
    connectSceneAction(ui->actionSkyBox, Scene::SkyBoxScene);
    connectSceneAction(ui->actionAdvancedData, Scene::AdvancedDataScene);
    connectSceneAction(ui->actionGLSLVariable, Scene::GLSLVariableScene);
    connectSceneAction(ui->actionInterfaceBlock, Scene::InterfaceBlockScene);


    connect(ui->actionLoadModel, &QAction::triggered, this, [this]() {
        QString path = QFileDialog::getOpenFileName(this,"选择模型文件","",
                                                  "OBJ (*.obj);;FBX(*.fbx);;ALL FILES( *.* ) ");
        ui->PreviewWgt->loadModel(path.toStdString());
    });


    connect(ui->PreviewWgt, &Preview::mousePickingPos,this,[this](QVector3D pos) {
        ui->statusbar->setStyleSheet("font: 14pt ");
        ui->statusbar->showMessage(" 世界坐标:    X:"
                                   +QString::number(pos.x(),'f', 2)
                                   +" Y:"+QString::number(pos.y(),'f', 2)
                                   +" Z:"+QString::number(pos.z(),'f', 2)
                                   );
    });
}
