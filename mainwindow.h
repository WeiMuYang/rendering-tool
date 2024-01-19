#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector4D>
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

private:
    Ui::MainWindow *ui;
    QVector4D u_Color;
};
#endif // MAINWINDOW_H
