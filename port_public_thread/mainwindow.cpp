#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_portdialog_1 = new PortDialog(this);
    m_portdialog_2 = new PortDialog(this);
//    m_portdialog_3 = new PortDialog(this);
    ui->verticalLayout->addWidget(m_portdialog_1);
    ui->verticalLayout->addWidget(m_portdialog_2);
//    ui->verticalLayout->addWidget(m_portdialog_3);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //write and read
    qDebug() << "flag:" << m_portdialog_1->m_portthread->port_select;
    QByteArray by = "hello";
    m_portdialog_1->port_public_write(by);
}
