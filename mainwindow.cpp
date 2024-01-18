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

    ui->TexTureBox->hide();
    // REPEAT, MIRRORED_REPEAT, CLAMP_TO_BORDER, CLAMP_TO_EDGE
    QStringList wrapList;
    wrapList << "REPEAT" << "MIRRORED_REPEAT" << "CLAMP_TO_BORDER" << "CLAMP_TO_EDGE";
    ui->texWrapComBox->addItems(wrapList);
    ui->texWrapComBox->setCurrentText("REPEAT");
    connect(ui->texWrapComBox, &QComboBox::currentTextChanged, this, &MainWindow::setWrapComBoxSlot);

    ui->texFilterBox->hide();
    //   NEAREST,  LINEAR,
    QStringList filterMagList;
    filterMagList << "NEAREST" << "LINEAR" << "NEAREST_MIPMAP_NEAREST" << "NEAREST_MIPMAP_NEAREST" << "NEAREST_MIPMAP_LINEAR"
                  << "LINEAR_MIPMAP_LINEAR";
    ui->texMagComBox->addItems(filterMagList);
    connect(ui->texMagComBox, &QComboBox::currentTextChanged, this, &MainWindow::setMinComBoxSlot);
    ui->texMagComBox->setCurrentText("NEAREST");
    //  NEAREST_MIPMAP_NEAREST, LINEAR_MIPMAP_NEAREST , NEAREST_MIPMAP_LINEAR , LINEAR_MIPMAP_LINEAR
    QStringList filterMinList;
    filterMinList << "NEAREST" << "LINEAR" << "NEAREST_MIPMAP_NEAREST" << "NEAREST_MIPMAP_NEAREST" << "NEAREST_MIPMAP_LINEAR"
                  << "LINEAR_MIPMAP_LINEAR";
    ui->texMinComBox->addItems(filterMinList);
    connect(ui->texMinComBox, &QComboBox::currentTextChanged, this, &MainWindow::setMagComBoxSlot);
    ui->texMinComBox->setCurrentText("NEAREST");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setShowByModuleType(Module module) {
    if(module == Module::isRectPos) {
        ui->colorUniformBox->show();
    }else {
        ui->colorUniformBox->hide();
    }

    if(module == Module::isRectPosColTexWrap) {
        ui->TexTureBox->show();
    }else {
        ui->TexTureBox->hide();
    }

    if(module == Module::isRectPosColTexFilter) {
        ui->texFilterBox->show();
    }else {
        ui->texFilterBox->hide();
    }
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
        setShowByModuleType(Module::isTriangle);
    });

    connect(ui->actionRectangle, &QAction::triggered, [this]() {
        ui->PreviewWgt->setModuleType(Module::isRectPos);
        setShowByModuleType(Module::isRectPos);

    });

    connect(ui->actionRectaCol, &QAction::triggered, [this]() {
        ui->PreviewWgt->setModuleType(Module::isRectPosCol);
        setShowByModuleType(Module::isRectPosCol);
    });

    connect(ui->actionTextureShader, &QAction::triggered, [this]() {
        ui->PreviewWgt->setModuleType(Module::isRectPosColTex);
        setShowByModuleType(Module::isRectPosColTex);
    });

    connect(ui->actionTextureWrap, &QAction::triggered, [this]() {
        ui->PreviewWgt->setModuleType(Module::isRectPosColTexWrap);
        setShowByModuleType(Module::isRectPosColTexWrap);
    });
    connect(ui->actionTextureFilter, &QAction::triggered, [this]() {
        ui->PreviewWgt->setModuleType(Module::isRectPosColTexFilter);
        setShowByModuleType(Module::isRectPosColTexFilter);
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

void MainWindow::setWrapComBoxSlot(QString name)
{
    // "REPEAT" << "MIRRORED_REPEAT" << "CLAMP_TO_BORDER" << "CLAMP_TO_EDGE";
    if(name == "REPEAT") {
        ui->PreviewWgt->setWrap(TexWrap::REPEAT);
    }else if(name == "MIRRORED_REPEAT") {
        ui->PreviewWgt->setWrap(TexWrap::MIRRORED_REPEAT);
    }else if(name == "CLAMP_TO_BORDER") {
        ui->PreviewWgt->setWrap(TexWrap::CLAMP_TO_BORDER);
    }else {
        ui->PreviewWgt->setWrap(TexWrap::CLAMP_TO_EDGE);
    }
}

void MainWindow::setMinComBoxSlot(QString name) {
    // NEAREST_MIPMAP_NEAREST, LINEAR_MIPMAP_NEAREST , NEAREST_MIPMAP_LINEAR , LINEAR_MIPMAP_LINEAR
    if(name == "NEAREST") {
        ui->PreviewWgt->setMinFilter(TexFilter::NEAREST);
    }else if(name == "LINEAR"){
        ui->PreviewWgt->setMinFilter(TexFilter::LINEAR);
    }else if(name == "NEAREST_MIPMAP_NEAREST") {
        ui->PreviewWgt->setMinFilter(TexFilter::NEAREST_MIPMAP_NEAREST);
    }else if(name == "LINEAR_MIPMAP_NEAREST") {
        ui->PreviewWgt->setMinFilter(TexFilter::LINEAR_MIPMAP_NEAREST);
    }else if(name == "NEAREST_MIPMAP_LINEAR") {
        ui->PreviewWgt->setMinFilter(TexFilter::NEAREST_MIPMAP_LINEAR);
    }else {
        ui->PreviewWgt->setMinFilter(TexFilter::LINEAR_MIPMAP_LINEAR);
    }
}

void MainWindow::setMagComBoxSlot(QString name) {
    if(name == "NEAREST") {
        ui->PreviewWgt->setMagFilter(TexFilter::NEAREST);
    }else if(name == "LINEAR"){
        ui->PreviewWgt->setMagFilter(TexFilter::LINEAR);
    }else if(name == "NEAREST_MIPMAP_NEAREST") {
        ui->PreviewWgt->setMagFilter(TexFilter::NEAREST_MIPMAP_NEAREST);
    }else if(name == "LINEAR_MIPMAP_NEAREST") {
        ui->PreviewWgt->setMagFilter(TexFilter::LINEAR_MIPMAP_NEAREST);
    }else if(name == "NEAREST_MIPMAP_LINEAR") {
        ui->PreviewWgt->setMagFilter(TexFilter::NEAREST_MIPMAP_LINEAR);
    }else {
        ui->PreviewWgt->setMagFilter(TexFilter::LINEAR_MIPMAP_LINEAR);
    }
}

