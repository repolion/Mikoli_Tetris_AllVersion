#ifndef IPDIALOG_H
#define IPDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>

namespace mikoli {

/*!
 * \brief This class is use for creating a QDialog Box
 * for asking host's ip and port to be connected in
 * multiplayer game
 */
class IpDialog:public QDialog
{

public:
    /*!
     * \brief The IpDialog constructor
     * \param fenetre the QWidget associated therewith
     */
    IpDialog(QWidget & fenetre,QWidget *parent = 0);

    /*!
     * \brief To get the ip from  the Qdialog box
     */
    QString getIp();

    /*!
     * \brief To get the port from the QDialog box
     */
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
