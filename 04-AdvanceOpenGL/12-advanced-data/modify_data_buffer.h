#ifndef MODIFY_DATA_BUFFER_H
#define MODIFY_DATA_BUFFER_H

#include <QDialog>
#include <QOpenGLFunctions_3_3_Core>


enum ModifyVBOType{
    VBONormal = 0, PtrHalf = 1, PtrAll = 2, SubHalf = 3, SubAll = 4
};

namespace Ui {
class ModifyDataBuffer;
}

class ModifyDataBuffer : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyDataBuffer(QWidget *parent = nullptr);
    ~ModifyDataBuffer();

    void showWindow();
    void updateDlg();
    void initSigSlot();

signals:
    void sigCurrentVBOType(ModifyVBOType type);
private:
    Ui::ModifyDataBuffer *ui;
};

#endif // MODIFY_DATA_BUFFER_H
