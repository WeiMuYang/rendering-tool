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
    initSceneData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setShowBox(Scene scene) {
    if(scene == Scene::ColorOfObject) {
        ui->ColorOfObjBox->show();
    }else {
        ui->ColorOfObjBox->hide();
    }

    if(scene == Scene::PhongLight) {
        ui->PhongLightBox->show();
    }else {
        ui->PhongLightBox->hide();
    }
}

void MainWindow::switchScene(Scene scene) {
    ui->PreviewWgt->setCurrentScene(scene);
    setShowBox(scene);
}

void MainWindow::initSceneData() {
    switchScene(Scene::ColorOfObject);
    // 01
    objectOfColor_01.lightColor = {1.0f, 1.0f, 1.0f};
    objectOfColor_01.objectColor = {1.0f, 0.5f, 0.3f};

    // 02
    phongLight_02.lightColor = {1.0f, 1.0f, 1.0f};
    phongLight_02.objectColor = {1.0f, 0.5f, 0.3f};
    phongLight_02.ambient = 0.1;
    phongLight_02.specular = 0.5;
    phongLight_02.shiny = 32;
}

void MainWindow::initAction() {
    ui->actionTimer->setShortcut(QKeySequence("Space"));
    connect(ui->actionTimer, &QAction::triggered, [this]() {
        ui->PreviewWgt->timeStartStop();
    });

    connect(ui->actionColorOfObj, &QAction::triggered, [this]() {
        switchScene(Scene::ColorOfObject);
    });

    connect(ui->actionPhongLight, &QAction::triggered, [this]() {
        switchScene(Scene::PhongLight);
    });

    connect(ui->actionGouraudLight, &QAction::triggered, [this]() {
        switchScene(Scene::GouraudLight);
    });

    connect(ui->actionMaterial, &QAction::triggered, [this]() {
        switchScene(Scene::Material);
    });

    connect(ui->actionCyanPlastic, &QAction::triggered, [this]() {
        switchScene(Scene::CyanPlastic);
    });

    // TexTureLight
    connect(ui->actionTexTureLight, &QAction::triggered, [this]() {
        switchScene(Scene::TexTureLight);
    });

}

void MainWindow::on_Light_R_SpinBox_valueChanged(double arg1)
{
    objectOfColor_01.lightColor.setX(arg1);
    ui->PreviewWgt->setShaderColorObj_01("lightColor", objectOfColor_01.lightColor);
}

void MainWindow::on_Light_G_SpinBox_valueChanged(double arg1)
{
    objectOfColor_01.lightColor.setY(arg1);
    ui->PreviewWgt->setShaderColorObj_01("lightColor", objectOfColor_01.lightColor);
}

void MainWindow::on_Light_B_SpinBox_valueChanged(double arg1)
{
    objectOfColor_01.lightColor.setZ(arg1);
    ui->PreviewWgt->setShaderColorObj_01("lightColor", objectOfColor_01.lightColor);
}

void MainWindow::on_Obj_R_SpinBox_valueChanged(double arg1)
{
    objectOfColor_01.objectColor.setX(arg1);
    ui->PreviewWgt->setShaderColorObj_01("objectColor", objectOfColor_01.objectColor);
}

void MainWindow::on_Obj_G_SpinBox_valueChanged(double arg1)
{
    objectOfColor_01.objectColor.setY(arg1);
    ui->PreviewWgt->setShaderColorObj_01("objectColor", objectOfColor_01.objectColor);
}

void MainWindow::on_Obj_B_SpinBox_valueChanged(double arg1)
{
    objectOfColor_01.objectColor.setZ(arg1);
    ui->PreviewWgt->setShaderColorObj_01("objectColor", objectOfColor_01.objectColor);
}


void MainWindow::on_PhongLight_R_SpinBox_valueChanged(double arg1)
{
    phongLight_02.lightColor.setX(arg1);
    ui->PreviewWgt->setShaderPhongLight_02("lightColor", phongLight_02.lightColor);
}


void MainWindow::on_PhongLight_G_SpinBox_valueChanged(double arg1)
{
    phongLight_02.lightColor.setY(arg1);
    ui->PreviewWgt->setShaderPhongLight_02("lightColor", phongLight_02.lightColor);
}

void MainWindow::on_PhongLight_B_SpinBox_valueChanged(double arg1)
{
    phongLight_02.lightColor.setZ(arg1);
    ui->PreviewWgt->setShaderPhongLight_02("lightColor", phongLight_02.lightColor);
}

void MainWindow::on_PhongObj_R_SpinBox_valueChanged(double arg1)
{
    phongLight_02.objectColor.setX(arg1);
    ui->PreviewWgt->setShaderPhongLight_02("objectColor", phongLight_02.objectColor);
}

void MainWindow::on_PhongObj_G_SpinBox_valueChanged(double arg1)
{
    phongLight_02.objectColor.setY(arg1);
    ui->PreviewWgt->setShaderPhongLight_02("objectColor", phongLight_02.objectColor);
}

void MainWindow::on_PhongObj_B_SpinBox_valueChanged(double arg1)
{
    phongLight_02.objectColor.setZ(arg1);
    ui->PreviewWgt->setShaderPhongLight_02("objectColor", phongLight_02.objectColor);
}

void MainWindow::on_PhongAmbient_SpinBox_valueChanged(double arg1)
{
    phongLight_02.ambient = arg1;
    ui->PreviewWgt->setShaderPhongLight_02("ambientStrength", QVector3D(phongLight_02.ambient, 0, 0));
}

void MainWindow::on_PhongSpecular_SpinBox_valueChanged(double arg1)
{
    phongLight_02.specular = arg1;
    ui->PreviewWgt->setShaderPhongLight_02("specularStrength", QVector3D(phongLight_02.specular, 0, 0));
}


void MainWindow::on_shiny_spinBox_valueChanged(int arg1)
{
    phongLight_02.shiny = arg1;
    ui->PreviewWgt->setShaderPhongLight_02("shiny", QVector3D(phongLight_02.shiny, 0, 0));
}

