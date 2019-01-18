#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <port_public_dialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    Port_Public_Dialog *port_public_dialog;
};

#endif // MAINWINDOW_H
