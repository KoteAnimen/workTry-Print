#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>
#include <QNetworkProxy>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString fromFileInfo = "";

    QString array[5000];
    QString path = "";

    void Print(QString);

private slots:
    void on_pushButton_clicked();

    void on_Download_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
