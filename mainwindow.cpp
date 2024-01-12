#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 不用给preview创建对象，因为是采用提升的方式创建的PreviewWgt
    // 只需要通过ui->PreviewWgt，就可以找到Preview的属性成员
    setCentralWidget(ui->PreviewWgt);
    initVertices();
    initShaders();
    initAction();
}

void MainWindow::initVertices() {
    Vertices triangle; // 创建一个Vertices对象
    triangle.setVerticesArr(verDataTri, 9);
    verticesMap_.insert(Module::isTriangle, triangle);

    Vertices rectangle; // 创建一个Vertices对象
    rectangle.setVerticesArr(verticesRect, VERTICES_RECT_SIZE);
    rectangle.setIndices(indicesRect, INDICES_RECT_SIZE);
    verticesMap_.insert(Module::isRectangle, rectangle);
}

void MainWindow::initShaders() {
    Shader shader1;
    shader1.setVertex(vertexShaderSource);
    shader1.setFrament(fragmentShaderSource);
    shaderMap_.insert("shader", shader1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initAction() {
    connect(ui->actionTriangle, &QAction::triggered, [this]() {
        ui->PreviewWgt->setModuleType(Module::isTriangle);
    });

    connect(ui->actionRectangle, &QAction::triggered, [this]() {
        ui->PreviewWgt->setModuleType(Module::isRectangle);
    });

    connect(ui->actionPoint, &QAction::triggered, [this]() {
        ui->PreviewWgt->setDrawMode(DrawMode::isPointMode);
    });

    connect(ui->actionLine, &QAction::triggered, [this]() {
        ui->PreviewWgt->setDrawMode(DrawMode::isLineMode);

    });

    connect(ui->actionFill, &QAction::triggered, [this]() {
        ui->PreviewWgt->setDrawMode(DrawMode::isFillMode);
    });
}

