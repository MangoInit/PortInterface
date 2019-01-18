#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    port_public_dialog = new Port_Public_Dialog(this);
    ui->verticalLayout->addWidget(port_public_dialog);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete port_public_dialog;
}
