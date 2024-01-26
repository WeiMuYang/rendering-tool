#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(QSize(1600, 800));
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

    u_proFov = ui->Fov_SpinBox->value();
    u_proNear = ui->near_SpinBox->value();
    u_proFar = ui->Far_SpinBox->value();
    u_proAspectRatio = ui->aspectRatio_SpinBox->value();


    // camera value
//    void sigPosition(QVector3D pos);
//    void sigYawPitch(float yaw, float pitch);
//    void sigFrontRightUp(QVector3D f,QVector3D r, QVector3D u,QVector3D wu);
    connect(ui->PreviewWgt, &Preview::sigPosition, [&](QVector3D cameraPos){
        ui->cameraPosXSpinBox->setValue(cameraPos.x());
        ui->cameraPosYSpinBox->setValue(cameraPos.y());
        ui->cameraPosZSpinBox->setValue(cameraPos.z());
    });

    connect(ui->PreviewWgt, &Preview::sigYawPitch, [&](float yaw, float pitch){
        ui->cameraYaw_SpinBox->setValue(yaw);
        ui->cameraPitch_SpinBox->setValue(pitch);
    });

    connect(ui->PreviewWgt, &Preview::sigFrontRightUp, [&](QVector3D f,QVector3D r, QVector3D u,QVector3D wu){
        ui->cameraFrontXSpinBox->setValue(f.x());
        ui->cameraFrontYSpinBox->setValue(f.y());
        ui->cameraFrontZSpinBox->setValue(f.z());

        ui->cameraRightXSpinBox->setValue(r.x());
        ui->cameraRightYSpinBox->setValue(r.y());
        ui->cameraRightZSpinBox->setValue(r.z());

        ui->cameraUpXSpinBox->setValue(u.x());
        ui->cameraUpYSpinBox->setValue(u.y());
        ui->cameraUpZSpinBox->setValue(u.z());

        ui->cameraWorldUpXSpinBox->setValue(wu.x());
        ui->cameraWorldUpYSpinBox->setValue(wu.y());
        ui->cameraWorldUpZSpinBox->setValue(wu.z());
    });
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

    // mvpBox
    if(module == Module::isBox3dMVP) {
        ui->mvpBox->show();
    }else {
        ui->mvpBox->hide();
    }

    // cameraWSADMouseBox
    if(module == Module::isCameraWSADMouse) {
        ui->cameraWSADMouseBox->show();
    }else {
        ui->cameraWSADMouseBox->hide();
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

    connect(ui->actionTranRotaScale, &QAction::triggered, [this]() {
        ui->PreviewWgt->setModuleType(Module::isRectTranRotaScale);
        setShowByModuleType(Module::isRectTranRotaScale);
    });

    connect(ui->action3DBox, &QAction::triggered, [this]() {
        ui->PreviewWgt->setModuleType(Module::isBox3dMVP);
        setShowByModuleType(Module::isBox3dMVP);
    });

    // actionManyBox
    connect(ui->actionManyBox, &QAction::triggered, [this]() {
        ui->PreviewWgt->setModuleType(Module::isManyBox3d);
        setShowByModuleType(Module::isManyBox3d);
    });


    connect(ui->actionCameraWSADMouse, &QAction::triggered, [this]() {
        ui->PreviewWgt->setModuleType(Module::isCameraWSADMouse);
        setShowByModuleType(Module::isCameraWSADMouse);
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
    // 代码中的逻辑是：先位移，再旋转，再缩放 translate.rotate.scale * Vec3(Pos.x,Pos.y,Pos.z)
    // 但是如果乘上Pos,根据线性代数乘法次序，是先 scale 再 rotate 再 translate
    // 记住，位移要放在最后。否则出现旋转中心偏移。
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

void MainWindow::on_Fov_SpinBox_valueChanged(double arg1)
{
    u_proFov = arg1;
    QMatrix4x4 projection;
    projection.perspective(u_proFov,u_proAspectRatio,u_proNear,u_proFar);
    char name[] = "projection";
    ui->PreviewWgt->set_shaderProBox3dMVP_Uniform(name, projection);
}


void MainWindow::on_near_SpinBox_valueChanged(double arg1)
{
    u_proNear = arg1;
    QMatrix4x4 projection;
    projection.perspective(u_proFov,u_proAspectRatio,u_proNear,u_proFar);
    char name[] = "projection";
    ui->PreviewWgt->set_shaderProBox3dMVP_Uniform(name, projection);
}


void MainWindow::on_Far_SpinBox_valueChanged(double arg1)
{
    u_proFar = arg1;
    QMatrix4x4 projection;
    projection.perspective(u_proFov,u_proAspectRatio,u_proNear,u_proFar);
    char name[] = "projection";
    ui->PreviewWgt->set_shaderProBox3dMVP_Uniform(name, projection);
}


void MainWindow::on_aspectRatio_SpinBox_valueChanged(double arg1)
{
    u_proAspectRatio = arg1;
    QMatrix4x4 projection;
    projection.perspective(u_proFov,u_proAspectRatio,u_proNear,u_proFar);
    char name[] = "projection";
    ui->PreviewWgt->set_shaderProBox3dMVP_Uniform(name, projection);
}


void MainWindow::on_model_tran_x_SpinBox_valueChanged(double arg1)
{
    QMatrix4x4 theMat;
    model_tran.setX(arg1);
    theMat.translate(model_tran);
    char name[] = "model";
    ui->PreviewWgt->set_shaderProBox3dMVP_Uniform(name, theMat);
}


void MainWindow::on_model_tran_y_SpinBox_valueChanged(double arg1)
{
    QMatrix4x4 theMat;
    model_tran.setY(arg1);
    theMat.translate(model_tran);
    char name[] = "model";
    ui->PreviewWgt->set_shaderProBox3dMVP_Uniform(name, theMat);
}


void MainWindow::on_model_tran_z_SpinBox_valueChanged(double arg1)
{
    QMatrix4x4 theMat;
    model_tran.setZ(arg1);
    theMat.translate(model_tran);
    char name[] = "model";
    ui->PreviewWgt->set_shaderProBox3dMVP_Uniform(name, theMat);
}


void MainWindow::on_view_tran_x_SpinBox_valueChanged(double arg1)
{
    QMatrix4x4 theMat;
    view_tran.setX(arg1);
    theMat.translate(view_tran);
    char name[] = "view";
    ui->PreviewWgt->set_shaderProBox3dMVP_Uniform(name, theMat);
}


void MainWindow::on_view_tran_y_SpinBox_valueChanged(double arg1)
{
    QMatrix4x4 theMat;
    view_tran.setY(arg1);
    theMat.translate(view_tran);
    char name[] = "view";
    ui->PreviewWgt->set_shaderProBox3dMVP_Uniform(name, theMat);
}


void MainWindow::on_view_tran_z_SpinBox_valueChanged(double arg1)
{
    QMatrix4x4 theMat;
    view_tran.setZ(arg1);
    theMat.translate(view_tran);
    char name[] = "view";
    ui->PreviewWgt->set_shaderProBox3dMVP_Uniform(name, theMat);
}

