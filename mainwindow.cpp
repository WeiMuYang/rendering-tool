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

    // REPEAT, MIRRORED_REPEAT, CLAMP_TO_BORDER, CLAMP_TO_EDGE
    QStringList wrapList;
    wrapList << "REPEAT" << "MIRRORED_REPEAT" << "CLAMP_TO_BORDER" << "CLAMP_TO_EDGE";
    ui->texWrapComBox->addItems(wrapList);
    ui->texWrapComBox->setCurrentText("REPEAT");
    connect(ui->texWrapComBox, &QComboBox::currentTextChanged, this, &MainWindow::setWrapComBoxSlot);

    //   NEAREST,  LINEAR,
    QStringList filterMagList;
    filterMagList << "NEAREST" << "LINEAR" << "NEAREST_MIPMAP_NEAREST" << "NEAREST_MIPMAP_NEAREST" << "NEAREST_MIPMAP_LINEAR"
                  << "LINEAR_MIPMAP_LINEAR";
    ui->texMagComBox->addItems(filterMagList);
    connect(ui->texMagComBox, &QComboBox::currentTextChanged, this, &MainWindow::setMinComBoxSlot);
    ui->texMagComBox->setCurrentText("LINEAR");
    //  NEAREST_MIPMAP_NEAREST, LINEAR_MIPMAP_NEAREST , NEAREST_MIPMAP_LINEAR , LINEAR_MIPMAP_LINEAR
    QStringList filterMinList;
    filterMinList << "NEAREST" << "LINEAR" << "NEAREST_MIPMAP_NEAREST" << "NEAREST_MIPMAP_NEAREST" << "NEAREST_MIPMAP_LINEAR"
                  << "LINEAR_MIPMAP_LINEAR";
    ui->texMinComBox->addItems(filterMinList);
    connect(ui->texMinComBox, &QComboBox::currentTextChanged, this, &MainWindow::setMagComBoxSlot);
    ui->texMinComBox->setCurrentText("LINEAR");

    setShowByModuleType(Module::isTriangle);


    u_translation.setX(ui->tran_x_SpinBox->value());
    u_translation.setY(ui->tran_y_SpinBox->value());
    u_translation.setZ(ui->tran_z_SpinBox->value());

    u_rotation.setX(ui->rota_x_SpinBox->value());
    u_rotation.setY(ui->rota_y_SpinBox->value());
    u_rotation.setZ(ui->rota_z_SpinBox->value());

    u_scale.setX(ui->scale_x_SpinBox->value());
    u_scale.setY(ui->scale_y_SpinBox->value());
    u_scale.setZ(ui->scale_z_SpinBox->value());
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
    if(module == Module::isRectPosColTex) {
        ui->TexTureMixBox->show();
    }else {
        ui->TexTureMixBox->hide();
    }

    if(module == Module::isRectTranRotaScale) {
        ui->matPropertyBox->show();
    }else {
        ui->matPropertyBox->hide();
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

    // actionTranRotaScale
    connect(ui->actionTranRotaScale, &QAction::triggered, [this]() {
        ui->PreviewWgt->setModuleType(Module::isRectTranRotaScale);
        setShowByModuleType(Module::isRectTranRotaScale);
    });
}

void MainWindow::on_xSpinBox_valueChanged(double arg1)
{
    u_Color.setX(arg1);
    char name[] = "u_Color";
    ui->PreviewWgt->set_shaderProRectUniform_Uniform(name, u_Color);
}


void MainWindow::on_ySpinBox_valueChanged(double arg1)
{
    u_Color.setY(arg1);
    char name[] = "u_Color";
    ui->PreviewWgt->set_shaderProRectUniform_Uniform(name, u_Color);
}


void MainWindow::on_zSpinBox_valueChanged(double arg1)
{
    u_Color.setZ(arg1);
    char name[] = "u_Color";
    ui->PreviewWgt->set_shaderProRectUniform_Uniform(name, u_Color);
}

void MainWindow::on_wSpinBox_valueChanged(double arg1)
{
    u_Color.setW(arg1);
    char name[] = "u_Color";
    ui->PreviewWgt->set_shaderProRectUniform_Uniform(name, u_Color);
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


void MainWindow::on_texMixSpinBox_valueChanged(double arg1)
{
    char name[] = "ratio";
    ui->PreviewWgt->set_shaderProRectTex_Uniform(name, arg1);
}


void MainWindow::on_tran_x_SpinBox_valueChanged(double arg1)
{
    QMatrix4x4 theMat;
    u_translation.setX(arg1);
    theMat.translate(u_translation);
    theMat.rotate(u_rotateDeg, u_rotation);
    theMat.scale(u_scale);
    ui->PreviewWgt->set_shaderProTransRotaScale_Uniform(theMat);
}


void MainWindow::on_tran_y_SpinBox_valueChanged(double arg1)
{
    QMatrix4x4 theMat;
    u_translation.setY(arg1);
    theMat.translate(u_translation);
    theMat.rotate(u_rotateDeg, u_rotation);
    theMat.scale(u_scale);
    ui->PreviewWgt->set_shaderProTransRotaScale_Uniform(theMat);
}


void MainWindow::on_tran_z_SpinBox_valueChanged(double arg1)
{
    QMatrix4x4 theMat;
    u_translation.setZ(arg1);
    theMat.translate(u_translation);
    theMat.rotate(u_rotateDeg, u_rotation);
    theMat.scale(u_scale);
    ui->PreviewWgt->set_shaderProTransRotaScale_Uniform(theMat);
}


void MainWindow::on_rota_x_SpinBox_valueChanged(double arg1)
{
    QMatrix4x4 theMat;
    u_rotation.setX(arg1);
    theMat.translate(u_translation);
    theMat.rotate(u_rotateDeg, u_rotation);
    theMat.scale(u_scale);
    ui->PreviewWgt->set_shaderProTransRotaScale_Uniform(theMat);
}


void MainWindow::on_rota_y_SpinBox_valueChanged(double arg1)
{
    QMatrix4x4 theMat;
    u_rotation.setY(arg1);
    theMat.translate(u_translation);
    theMat.rotate(u_rotateDeg, u_rotation);
    theMat.scale(u_scale);
    ui->PreviewWgt->set_shaderProTransRotaScale_Uniform(theMat);
}


void MainWindow::on_rota_z_SpinBox_valueChanged(double arg1)
{
    QMatrix4x4 theMat;
    u_rotation.setZ(arg1);
    theMat.translate(u_translation);
    theMat.rotate(u_rotateDeg, u_rotation);
    theMat.scale(u_scale);
    ui->PreviewWgt->set_shaderProTransRotaScale_Uniform(theMat);
}


void MainWindow::on_scale_x_SpinBox_valueChanged(double arg1)
{
    QMatrix4x4 theMat;
    u_scale.setX(arg1);
    theMat.translate(u_translation);
    theMat.rotate(u_rotateDeg, u_rotation);
    theMat.scale(u_scale);
    ui->PreviewWgt->set_shaderProTransRotaScale_Uniform(theMat);
}


void MainWindow::on_scale_y_SpinBox_valueChanged(double arg1)
{
    QMatrix4x4 theMat;
    u_scale.setY(arg1);
    theMat.translate(u_translation);
    theMat.rotate(u_rotateDeg, u_rotation);
    theMat.scale(u_scale);
    ui->PreviewWgt->set_shaderProTransRotaScale_Uniform(theMat);
}


void MainWindow::on_scale_z_SpinBox_valueChanged(double arg1)
{
    QMatrix4x4 theMat;
    u_scale.setZ(arg1);
    theMat.translate(u_translation);
    theMat.rotate(u_rotateDeg, u_rotation);
    theMat.scale(u_scale);
    ui->PreviewWgt->set_shaderProTransRotaScale_Uniform(theMat);
}


void MainWindow::on_rota_deg_SpinBox_valueChanged(double arg1)
{
    QMatrix4x4 theMat;
    u_rotateDeg = arg1;
    theMat.translate(u_translation);
    theMat.rotate(u_rotateDeg, u_rotation);
    theMat.scale(u_scale);
    ui->PreviewWgt->set_shaderProTransRotaScale_Uniform(theMat);
}

