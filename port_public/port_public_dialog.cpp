#include "port_public_dialog.h"
#include "ui_port_public_dialog.h"


Port_Public_Dialog::Port_Public_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Port_Public_Dialog)
{
    ui->setupUi(this);
    connect(&m_timer, &QTimer::timeout, this, &Port_Public_Dialog::sl_info_refresh);
    connect(this, &Port_Public_Dialog::sg_port_changed, this, &Port_Public_Dialog::sl_comboBox_dis);
    m_timer.start(1000);
}

Port_Public_Dialog::~Port_Public_Dialog()
{
    delete ui;
}

void Port_Public_Dialog::sl_info_refresh()
{
    QSet<QString>::iterator i_set;

    const auto infos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info:infos)
    {
        if(info.portName().at(3) == QString("U"))
        {
            //add new serial port
            i_set = m_set.find(info.portName());
            if(i_set == m_set.end())
            {
                if(!ui->pushButton->isChecked())
                {
                    Q_EMIT sg_port_changed(info.portName(), Info_Way::ADD);
                    m_set.insert(info.portName());
                    qDebug() << "find new port" << info.portName();
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
            if(!ui->pushButton->isChecked())
            {
                QSerialPortInfo info;
                i_set = m_set.find(set);
                qDebug() << "lose one port: " << port.portName();
                i_set = m_set.erase(i_set);
                Q_EMIT sg_port_changed(port.portName(), Info_Way::DET);
           }
       }
    }
    qDebug() << "did:" << m_set;
}


//add or delete item from m_set
void Port_Public_Dialog::sl_comboBox_dis(QString portName, Info_Way way)
{
    if(way == Info_Way::ADD)
    {
        ui->comboBox->insertItem(portName.at(6).toLatin1(), portName);
    }
    else
    {
        int i = portName.at(6).toLatin1() - '0';
        ui->comboBox->removeItem(i);
    }
}
