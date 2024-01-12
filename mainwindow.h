#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "data_type.h"
#include "vertices.h"
#include "shader.h"

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
    void initVertices();
    void initShaders();

private:
    Ui::MainWindow *ui;
    QMap<Module, Vertices> verticesMap_;
    QMap<QString, Shader> shaderMap_;
};
#endif // MAINWINDOW_H
