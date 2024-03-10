#include "modify_data_buffer.h"
#include "ui_modify_data_buffer.h"

ModifyDataBuffer::ModifyDataBuffer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyDataBuffer)
{
    ui->setupUi(this);
    initSigSlot();
}

ModifyDataBuffer::~ModifyDataBuffer()
{
    delete ui;
}

void ModifyDataBuffer::showWindow()
{
    show();
    updateDlg();
}


void ModifyDataBuffer::updateDlg()
{
    ui->comboBox->setCurrentIndex(0);
}

void ModifyDataBuffer::initSigSlot()
{
    QObject::connect(ui->comboBox, &QComboBox::currentTextChanged, this, [&](QString name) {
        if(name == "正常(Normal)") {
            emit sigCurrentVBOType(ModifyVBOType::VBONormal);
        }else if(name == "glMapBuffer给一半数据(PtrHalf)") {
            emit sigCurrentVBOType(ModifyVBOType::PtrHalf);
        }else if(name == "glMapBuffer给另一半数据(PtrAll)") {
            emit sigCurrentVBOType(ModifyVBOType::PtrAll);
        }else if(name == "glBufferSubData给一半数据(SubHalf)") {
            emit sigCurrentVBOType(ModifyVBOType::SubHalf);
        }else if(name == "glBufferSubData给另一半数据(SubAll)") {
            emit sigCurrentVBOType(ModifyVBOType::SubAll);
        }else{
            emit sigCurrentVBOType(ModifyVBOType::VBONormal);
        }
    });
}
