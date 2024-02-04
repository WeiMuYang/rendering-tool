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
    int shiny;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initAction();

    void initSceneData();
    template<typename T>
    void connectSceneAction(T action, Scene scene);
private slots:

private:
    Ui::MainWindow *ui;
    ObjectOfColor_01  objectOfColor_01;
    PhongLight_02 phongLight_02;

};
#endif // MAINWINDOW_H
