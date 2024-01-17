#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 不用给preview创建对象，因为是采用提升的方式创建的PreviewWgt
    // 只需要通过ui->PreviewWgt，就可以找到Preview的属性成员
    initAction();
    u_Color.setX(ui->xSpinBox->value());
    u_Color.setY(ui->ySpinBox->value());
    u_Color.setZ(ui->zSpinBox->value());
    u_Color.setW(ui->wSpinBox->value());
    ui->colorUniformBox->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initAction() {
    // 绘制模式： 点线面
    connect(ui->actionPoint, &QAction::triggered, [this]() {
        ui->PreviewWgt->setDrawMode(DrawMode::isPointMode);
    });
    connect(ui->actionLine, &QAction::triggered, [this]() {
        ui->PreviewWgt->setDrawMode(DrawMode::isLineMode);

    });
    connect(ui->actionFill, &QAction::triggered, [this]() {
        ui->PreviewWgt->setDrawMode(DrawMode::isFillMode);
    });

    // 使用的顶点信息
    connect(ui->actionTriangle, &QAction::triggered, [this]() {
        ui->PreviewWgt->setModuleType(Module::isTriangle);
    });

    connect(ui->actionRectangle, &QAction::triggered, [this]() {
        ui->PreviewWgt->setModuleType(Module::isRectanglePos);
    });

    connect(ui->actionRectaCol, &QAction::triggered, [this]() {
        ui->PreviewWgt->setModuleType(Module::isRectanglePosCol);
    });


    // 使用的着色器
    connect(ui->actionBase, &QAction::triggered, [this]() {
        ui->PreviewWgt->setShaderProgram(ShaderProgram::Base);
        ui->colorUniformBox->hide();
    });
    connect(ui->actionBaseUniform, &QAction::triggered, [this]() {
        ui->PreviewWgt->setShaderProgram(ShaderProgram::BaseWithUniform);
        ui->colorUniformBox->show();
    });
    connect(ui->actionBaseACol, &QAction::triggered, [this]() {
        ui->PreviewWgt->setShaderProgram(ShaderProgram::BaseWithAColor);
//        ui->PreviewWgt->setModuleType(Module::isRectanglePosCol);
        ui->colorUniformBox->hide();
    });
}

void MainWindow::on_xSpinBox_valueChanged(double arg1)
{
    u_Color.setX(arg1);
    char name[] = "u_Color";
    ui->PreviewWgt->setUniform(name, u_Color);
}


void MainWindow::on_ySpinBox_valueChanged(double arg1)
{
    u_Color.setY(arg1);
    char name[] = "u_Color";
    ui->PreviewWgt->setUniform(name, u_Color);
}


void MainWindow::on_zSpinBox_valueChanged(double arg1)
{
    u_Color.setZ(arg1);
    char name[] = "u_Color";
    ui->PreviewWgt->setUniform(name, u_Color);
}

void MainWindow::on_wSpinBox_valueChanged(double arg1)
{
    u_Color.setW(arg1);
    char name[] = "u_Color";
    ui->PreviewWgt->setUniform(name, u_Color);
}
