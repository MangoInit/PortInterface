#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <portdialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    PortDialog *m_portdialog_1;
    PortDialog *m_portdialog_2;
    PortDialog *m_portdialog_3;
};

#endif // MAINWINDOW_H
