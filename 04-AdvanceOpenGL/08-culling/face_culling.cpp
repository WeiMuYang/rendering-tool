#include "face_culling.h"
#include "ui_face_culling.h"

FaceCulling::FaceCulling(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FaceCulling)
{
    ui->setupUi(this);
    cullingType = FaceCullingType::FaceCullingBACK;
    cullingOri = FaceCullingOri::antiClockwise;
    initSigSlot();
}

FaceCulling::~FaceCulling()
{
    delete ui;
}

void FaceCulling::showWindow()
{
    show();
    updateDlg();
}

void FaceCulling::updateDlg()
{
    ui->CullingType_comboBox->setCurrentIndex(0);
    ui->FrontFace_comboBox->setCurrentIndex(0);
}

void FaceCulling::initSigSlot()
{
    QObject::connect(ui->CullingType_comboBox, &QComboBox::currentTextChanged, this, [&](QString name) {
        // FRONT = 0x0404, BACK = 0x0405, LEFT = 0x0406, RIGHT = 0x0407, FRONT_AND_BACK = 0x0408
        if(name == "FRONT") {
            cullingType = FaceCullingType::FaceCullingFRONT;
        }else if(name == "BACK"){
            cullingType = FaceCullingType::FaceCullingBACK;
        }else if(name == "LEFT"){
            cullingType = FaceCullingType::FaceCullingLEFT;
        }else if(name == "RIGHT"){
            cullingType = FaceCullingType::FaceCullingRIGHT;
        }else {
            cullingType = FaceCullingType::FRONT_AND_BACK;
        }
    });

    QObject::connect(ui->FrontFace_comboBox, &QComboBox::currentTextChanged, this, [&](QString name) {
        if(name == "ClockWise") {
            cullingOri = FaceCullingOri::ClockWise;
        }else {
            cullingOri = FaceCullingOri::antiClockwise;
        }
    });
}
