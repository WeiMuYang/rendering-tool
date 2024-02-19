#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector3D>
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

    template<typename T>
    void connectSceneAction(T action, Scene scene);
private slots:

private:
    Ui::MainWindow *ui;
//    ObjectOfColor_01  objectOfColor_01;
//    PhongLight_02 phongLight_02;

};
#endif // MAINWINDOW_H
