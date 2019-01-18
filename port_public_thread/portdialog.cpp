#include "portdialog.h"
#include "ui_portdialog.h"

PortDialog::PortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PortDialog)
{
    qRegisterMetaType< QSet<QString> >("string_set");
    qRegisterMetaType< Info_Way >("Info_Way");

    ui->setupUi(this);

    m_portthread = new PortThread;
    connect(m_portthread, SIGNAL(sg_add_det_port(string_set, Info_Way)), this, SLOT(sl_comboBox_dis(string_set, Info_Way)), Qt::QueuedConnection);//Cross-thread
    connect(this, &PortDialog::sg_check_port, m_portthread, &PortThread::sl_port_fix);
    connect(this, &PortDialog::sg_uncheck_port, m_portthread, &PortThread::sl_port_relieve);
    connect(m_portthread, &PortThread::sg_port_disconnect, this, &PortDialog::sl_disconnect_warn);
    m_portthread->start();

    /*moveToThread Way*/
//    QThread *m_thread = new QThread;
//    m_portthread = new PortThread;
//    connect(m_portthread, &PortThread::sg_add_det_port, this, &PortDialog::sl_comboBox_dis, Qt::QueuedConnection);//Cross-thread
//    connect(m_portthread->m_timer, &QTimer::timeout, m_portthread, &PortThread::sl_info_refresh);
//    connect(this, &PortDialog::sg_check_port, m_portthread, &PortThread::sl_port_check);
//    m_portthread->moveToThread(m_thread);
//    m_thread->start();
//    m_portthread->start();
}

PortDialog::~PortDialog()
{
    delete ui;
}

bool PortDialog::port_public_write(QByteArray data)
{
//    add a flag
    if(m_portthread->port_select == true)
    {
        qint64 i = m_portthread->m_serialPort->write(data);
        qDebug() << "write:" << i;
    }
}

void PortDialog::sl_comboBox_dis(QSet<QString> set, Info_Way way)
{
    ui->comboBox->clear();
    int i;
    foreach(const QString &_set, set)
    {
        i = _set.at(6).toLatin1() - '0';
        ui->comboBox->insertItem(i, _set);
    }
}

void PortDialog::sl_disconnect_warn()
{
    ui->comboBox->setEnabled(true);
    ui->pushButton_connect->setChecked(false);
    Q_EMIT sg_uncheck_port(ui->comboBox->currentText());
    QMessageBox message(QMessageBox::Warning,"警告","串口连接已断开\n请重新选择",QMessageBox::Yes|QMessageBox::No,NULL);
    if (message.exec()==QMessageBox::Yes)
    {
        qDebug()<<"clicked yes\n";
    }
    else
    {
        qDebug()<<"clicked no\n";
    }
}

void PortDialog::on_pushButton_connect_clicked(bool checked)
{
    if(checked)
    {
        ui->comboBox->setEnabled(false);
//        disconnect(m_portthread->m_timer, &QTimer::timeout, m_portthread, &PortThread::sl_info_refresh);
        Q_EMIT sg_check_port(ui->comboBox->currentText());
    }
    else
    {
        ui->comboBox->setEnabled(true);
//        connect(m_portthread->m_timer, &QTimer::timeout, m_portthread, &PortThread::sl_info_refresh);
        Q_EMIT sg_uncheck_port(ui->comboBox->currentText());
    }
}
