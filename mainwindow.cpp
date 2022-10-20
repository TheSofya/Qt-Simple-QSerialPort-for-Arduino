#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    arduino = std::make_unique<QSerialPort>(this);

    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &MainWindow::on_comboBox_currentIndexChanged);
    fillComboBoxWithAvaliablePorts();
};

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillComboBoxWithAvaliablePorts() {
    ui->comboBox->clear();
    const auto ports_information = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : ports_information) {
        QStringList list_of_avaliable_ports;
        list_of_avaliable_ports << info.portName();
        ui->comboBox->addItem(list_of_avaliable_ports.first(), list_of_avaliable_ports);
    }
}

void MainWindow::on_pushButtonTrue_clicked() {
    if (arduino->isWritable()) {
        arduino->write("1");
    } else {
        qDebug() << "Could't write 1 to serial";
    }
}

/*QByteArray b("a0 01 01 a2");
QByteArray t = b.replace(" ", "");
QByteArray bytes = QByteArray::fromHex(t);
arduino->write(bytes);*/

void MainWindow::on_pushButtonFalse_clicked() {
    if (arduino->isWritable()) {
        arduino->write("0");
    } else {
        qDebug() << "Could't write 0 to serial";
    }
}

/*QByteArray b("a0 01 00 a1");
QByteArray t = b.replace(" ", "");
QByteArray bytes = QByteArray::fromHex(t);
arduino->write(bytes);*/

void MainWindow::on_comboBox_currentIndexChanged(const QString &port) {
    qDebug() << "Try to connect" << port;
    arduino->setPortName(port);
    arduino->setBaudRate(QSerialPort::Baud9600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);
    arduino->open(QIODevice::ReadWrite);
}

