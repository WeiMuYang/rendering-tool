#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(QSize(1400, 800));
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

    connectSceneAction(ui->actionColorOfObj, Scene::ColorOfObject);
    connectSceneAction(ui->actionPhongLight, Scene::PhongLight);
    connectSceneAction(ui->actionGouraudLight, Scene::GouraudLight);
    connectSceneAction(ui->actionMaterial, Scene::Material);
    connectSceneAction(ui->actionCyanPlastic, Scene::CyanPlastic);
    connectSceneAction(ui->actionTexTureLight, Scene::TextureLight);
    connectSceneAction(ui->actionParallelLight, Scene::ParallelLight);
    connectSceneAction(ui->actionPointLight, Scene::PointLight);
    connectSceneAction(ui->actionSpotLight, Scene::SpotLight);
    connectSceneAction(ui->actionSpotLightSmooth, Scene::SpotLightSmooth);
    connectSceneAction(ui->actionMultLight, Scene::MultLight);
}


