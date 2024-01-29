#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector3D>
#include "data_type.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct ObjectOfColor_01
{
    QVector3D objectColor;
    QVector3D lightColor;
};

struct PhongLight_02
{
    QVector3D objectColor;
    QVector3D lightColor;
    float ambient;
    float specular;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initAction();
    void switchScene(Scene scene);

    void setShowBox(Scene scene);
    void initSceneData();
private slots:


    void on_Light_R_SpinBox_valueChanged(double arg1);

    void on_Light_G_SpinBox_valueChanged(double arg1);

    void on_Light_B_SpinBox_valueChanged(double arg1);

    void on_Obj_R_SpinBox_valueChanged(double arg1);

    void on_Obj_G_SpinBox_valueChanged(double arg1);

    void on_Obj_B_SpinBox_valueChanged(double arg1);

    void on_PhongLight_R_SpinBox_valueChanged(double arg1);

    void on_PhongLight_G_SpinBox_valueChanged(double arg1);

    void on_PhongLight_B_SpinBox_valueChanged(double arg1);

    void on_PhongObj_R_SpinBox_valueChanged(double arg1);

    void on_PhongObj_G_SpinBox_valueChanged(double arg1);

    void on_PhongObj_B_SpinBox_valueChanged(double arg1);

    void on_PhongAmbient_SpinBox_valueChanged(double arg1);

    void on_PhongSpecular_SpinBox_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    ObjectOfColor_01  objectOfColor_01;
    PhongLight_02 phongLight_02;

};
#endif // MAINWINDOW_H
