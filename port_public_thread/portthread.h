#ifndef PORTTHREAD_H
#define PORTTHREAD_H

#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QSet>
#include <QMetaType>

enum Info_Way{
    ADD = 0, DET
};

class PortThread : public QThread
{
    Q_OBJECT


public:
    PortThread();
    QTimer *m_timer;
    QTimer *check_timer;
    QSerialPort *m_serialPort;
    bool port_select = false;

signals:
//    void sg_add_det_port(QString portName, Info_Way way);

    void sg_add_det_port(QSet<QString> set, Info_Way way);

    void sg_stop_refresh_timer();

    void sg_start_check_timer();

    void sg_start_refresh_timer();

    void sg_stop_check_timer();

    void sg_port_disconnect();

    void sg_out_serialport(QSerialPort*);    //接口：串口句柄

public slots:
    void sl_info_refresh();

    void sl_port_fix(QString port_name);

    void sl_port_relieve(QString port_name);

    void sl_port_check();

    void m_serialPort_receive();

private:
    QSet<QString> m_set;

protected:
    void run();
};

#endif // PORTTHREAD_H
