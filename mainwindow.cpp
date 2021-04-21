#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

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
    if(path != "")
    {
        Print("^XA"
              "^FO 360,40"  //смещение текста от левого верхнего края
              "^FB400,2,10,C,0" //ширина, количество строк, пробелы между строками, выравнивание текста, отступ для второй или последующей строки
              "^ASN,10,10" //шрифт S и размер букв 10 на 10 точек
              "^BXN,5,200,,,,_"
              "^FD_1" + QString(array[(int)ui->numberDataMatrix->value()]) + "^FS"//сам текст
              "^XZ");
    }
    else
    {
        QMessageBox box;
        box.setWindowTitle("Ошибка");
        box.setText("Не загружен файл с DataMatrix");
        box.exec();
    }

}

void MainWindow::on_Download_clicked()
{
    int i = 0;
    path = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"), QDir::currentPath(),"File (*.csv)");
    QFile file(path);
    if(file.open(QFile::ReadOnly))
    {
       QTextStream in(&file);
       while(!in.atEnd())
       {
           fromFileInfo = in.readLine();
           array[i] = fromFileInfo;
           i++;
       }
    }
    qDebug()<<array[1];


}
