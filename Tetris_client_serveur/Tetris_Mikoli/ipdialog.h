#ifndef IPDIALOG_H
#define IPDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>

namespace mikoli {

class IpDialog:public QDialog
{

public:
    IpDialog(QWidget & fenetre,QWidget *parent = 0);
    QString getIp();
    QString getPort();

private:
    QLabel *_label;
    QLineEdit *_lineEditIp;
    QLineEdit *_lineEditPort;
    QPushButton *_confirm;
    QString _port;
    QString ip;


};

}

#endif // IPDIALOG_H
