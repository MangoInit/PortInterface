#ifndef PORT_PUBLIC_DIALOG_H
#define PORT_PUBLIC_DIALOG_H

#include <QDialog>
#include <QObject>
#include <QTimer>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtSerialPort>
#include <QSet>
#include <QRunnable>

namespace Ui {
class Port_Public_Dialog;
}

class Port_Public_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Port_Public_Dialog(QWidget *parent = nullptr);
    ~Port_Public_Dialog();
    enum Info_Way
    {
        ADD = 0, DET
    };

signals:
    void sg_port_changed(QString portName, Info_Way way);

private slots:
    void sl_info_refresh();

    void sl_comboBox_dis(QString portName, Info_Way way);

private:
    Ui::Port_Public_Dialog *ui;

    QByteArray m_response;
    QTimer m_timer;
//    QSerialPort m_serialPort;
    QSet<QString> m_set;
};

#endif // PORT_PUBLIC_DIALOG_H
