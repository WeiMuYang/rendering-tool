#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector4D>
#include <QVector3D>
#include <QMatrix4x4>
#include "data_type.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initAction();
    void setShowByModuleType(Module module);

private slots:
    void on_xSpinBox_valueChanged(double arg1);

    void on_ySpinBox_valueChanged(double arg1);

    void on_zSpinBox_valueChanged(double arg1);

    void on_wSpinBox_valueChanged(double arg1);

    void setWrapComBoxSlot(QString name);

    void setMinComBoxSlot(QString name);

    void setMagComBoxSlot(QString name);
    void on_texMixSpinBox_valueChanged(double arg1);

    void on_tran_x_SpinBox_valueChanged(double arg1);

    void on_tran_y_SpinBox_valueChanged(double arg1);

    void on_tran_z_SpinBox_valueChanged(double arg1);

    void on_rota_x_SpinBox_valueChanged(double arg1);

    void on_rota_y_SpinBox_valueChanged(double arg1);

    void on_rota_z_SpinBox_valueChanged(double arg1);

    void on_scale_x_SpinBox_valueChanged(double arg1);

    void on_scale_y_SpinBox_valueChanged(double arg1);

    void on_scale_z_SpinBox_valueChanged(double arg1);

    void on_rota_deg_SpinBox_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    QVector4D u_Color;

    QVector3D u_translation;
    QVector3D u_rotation;
    float u_rotateDeg{0};
    QVector3D u_scale;
    QMatrix4x4 u_theMat;
};
#endif // MAINWINDOW_H
