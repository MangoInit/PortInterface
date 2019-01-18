#ifndef PORTDIALOG_H
#define PORTDIALOG_H

#include <QDialog>
#include <portthread.h>
#include <QMessageBox>

namespace Ui {
class PortDialog;
}
//typedef QList <analysis_results> analysis_results_list;


class PortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PortDialog(QWidget *parent = nullptr);
    ~PortDialog();
    PortThread *m_portthread;

    bool port_public_write(QByteArray data);

signals:
    void sg_check_port(QString port_name);

    void sg_uncheck_port(QString port_name);

public slots:
    void sl_comboBox_dis(QSet<QString> set, Info_Way way);

    void sl_disconnect_warn();

private slots:
    void on_pushButton_connect_clicked(bool checked);

private:
    Ui::PortDialog *ui;

};

#endif // PORTDIALOG_H
