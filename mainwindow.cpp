#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Print(QString str)
{
    QByteArray array = str.toUtf8();
    QAbstractSocket *socket;
    socket = new QAbstractSocket(QAbstractSocket::TcpSocket, this);
    socket->setProxy(QNetworkProxy::NoProxy);
    socket->setSocketOption(QAbstractSocket::SendBufferSizeSocketOption, 1024);
    socket->connectToHost("192.168.0.35", 9100, QAbstractSocket::ReadWrite);
    if (socket->waitForConnected(1000))
    {
    if (socket->write(array) != -1)
    {
    while (socket->bytesToWrite() > 0)
    {
    socket->flush();
    }
    }
    else
    {
    QMessageBox::StandardButton ErrorOpenFile;
    ErrorOpenFile = QMessageBox::critical(this,
    QString::fromUtf8("Ошибка"),
    QString::fromUtf8("<font size='16'>Ошибка печати!</font>"));
    }
    }
    else
    {
    QMessageBox::StandardButton ErrorOpenFile;
    ErrorOpenFile = QMessageBox::critical(this,
    QString::fromUtf8("Ошибка"),
    QString::fromUtf8("<font size='16'>Ошибка доступа к принтеру! Проверьте питания принтера!</font>"));
    }
    socket->disconnectFromHost();
}


void MainWindow::on_pushButton_clicked()
{
    Print(QString("^XA")
          + QString("^FO 200,100")
          + QString("^FB400,2,10,C,0")
          + QString("^ASN,10,10")
          + QString("^FD")
          + QString(ui->lineEdit->text())
          + QString("^FS")
          + QString("^XZ"));
}
