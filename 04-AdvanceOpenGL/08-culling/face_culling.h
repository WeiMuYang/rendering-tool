#ifndef FACE_CULLING_H
#define FACE_CULLING_H

#include <QDialog>
#include "../data_type.h"

namespace Ui {
class FaceCulling;
}

class FaceCulling : public QDialog
{
    Q_OBJECT

public:
    explicit FaceCulling(QWidget *parent = nullptr);
    ~FaceCulling();

    FaceCullingType cullingType;
    FaceCullingOri cullingOri;


    void showWindow();
    void updateDlg();
public slots:
    void initSigSlot();

private:
    Ui::FaceCulling *ui;
};

#endif // FACE_CULLING_H
