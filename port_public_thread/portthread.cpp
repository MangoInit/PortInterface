#include "portthread.h"

PortThread::PortThread()
{
    qDebug() << "port thread id\t" << this->thread();
}

void PortThread::sl_info_refresh()
{
    QSet<QString>::iterator i_set;

    //add new serial port
    const auto infos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info:infos)
    {
        if(info.portName().at(3) == QString("U"))
        {
            i_set = m_set.find(info.portName());
            if(i_set == m_set.end())
            {
                if(!info.isBusy())
                {
                     m_set.insert(info.portName());
                    qDebug() << "find new port" << info.portName();
                    Q_EMIT sg_add_det_port(m_set, Info_Way::ADD);
                    return ;
                }
            }
        }
    }

    //delete lost serial port
    foreach(const QString &set, m_set)
    {
        QSerialPort port;
        port.setPortName(set);
        if(!port.open(QIODevice::ReadWrite))
        {
            qDebug() << "lose one port: " << port.portName();
            m_set.remove(set);
            Q_EMIT sg_add_det_port(m_set, Info_Way::DET);
        }
        else
        {
//            qDebug() << port.isReadable();
//            port.clear();
//            port.close();
        }
    }

    qDebug() << "info thread id:" << this->thread() << m_set;
}

void PortThread::sl_port_fix(QString port_name)
{
    qDebug() << port_name;
    m_serialPort = new QSerialPort;
    m_serialPort->setPortName(port_name);

    if(m_serialPort->open(QIODevice::ReadWrite))
    {
        m_serialPort->setBaudRate(QSerialPort::Baud115200);
        m_serialPort->setParity(QSerialPort::NoParity);
        m_serialPort->setDataBits(QSerialPort::Data8);
        m_serialPort->setStopBits(QSerialPort::OneStop);
        m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
        connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(m_serialPort_receive()));     //receive data
        port_select = true;
//        m_set.remove(port_name);
    }
    else
    {
        qDebug() << "open port fail";
        return ;
    }
    Q_EMIT sg_stop_refresh_timer();
    Q_EMIT sg_start_check_timer();

    Q_EMIT sg_out_serialport(m_serialPort);
}

void PortThread::sl_port_relieve(QString port_name)
{
    port_select = false;
    delete m_serialPort;
    Q_EMIT sg_start_refresh_timer();
    Q_EMIT sg_stop_check_timer();
}

void PortThread::sl_port_check()
{
    if(m_serialPort->isRequestToSend())
    {
        qDebug() << m_serialPort->portName() << " is connect";
    }
    else
    {
        port_select = false;
        qDebug() << m_serialPort->portName() << "is disconncted";
        Q_EMIT sg_port_disconnect();
    }
}

void PortThread::m_serialPort_receive()
{
    qDebug() << "receive:" << m_serialPort->readAll();
}

void PortThread::run()
{
    m_timer = new QTimer;
    m_timer->setInterval(1000);
    connect(this, SIGNAL(sg_stop_refresh_timer()), m_timer, SLOT(stop()));
    connect(this, SIGNAL(sg_start_refresh_timer()), m_timer, SLOT(start()));
    connect(m_timer, &QTimer::timeout, this, &PortThread::sl_info_refresh);
    m_timer->start();
    qDebug() << "run() thread id\t" << this->thread();
    qDebug() << "timer thread id\t" << m_timer->thread();

    check_timer = new QTimer;
    check_timer->setInterval(1000);
    connect(this, SIGNAL(sg_start_check_timer()), check_timer, SLOT(start()));
    connect(this, SIGNAL(sg_stop_check_timer()), check_timer, SLOT(stop()));
    connect(check_timer, &QTimer::timeout, this, &PortThread::sl_port_check);
    this->exec();
}
