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
    connectSceneAction(ui->actionMousePicking, Scene::MousePickingScene);

    connect(ui->actionLoadModel, &QAction::triggered, this, [this]() {
        QString path = QFileDialog::getOpenFileName(this,"选择模型文件","",
                                                  "OBJ (*.obj);;FBX(*.fbx);;ALL FILES( *.* ) ");
        ui->PreviewWgt->loadModel(path.toStdString());
    });
}
