        #include "ipdialog.h"
    #include <QGroupBox>
    #include <QGridLayout>

    namespace mikoli {

    IpDialog::IpDialog(QWidget & fenetre,QWidget *parent)
        :QDialog(parent)
    {

        QGroupBox *connexionGroup = new QGroupBox(tr("Connexion"));

        _confirm = new QPushButton("confirm");

        _lineEditIp = new QLineEdit;
        _lineEditIp->setPlaceholderText("Host IP");
        _lineEditIp->setFocus();

        _lineEditPort = new QLineEdit;
        _lineEditPort->setPlaceholderText("Host Port");
        _lineEditPort->setFocus();

        QGridLayout *connexionLayout = new QGridLayout;
        connexionLayout->addWidget(_lineEditIp, 0, 0);
        connexionLayout->addWidget(_lineEditPort, 0, 1);
        connexionLayout->addWidget(_confirm, 0, 2);

        connexionGroup->setLayout(connexionLayout);

        QGridLayout *layout = new QGridLayout;
        layout->addWidget(connexionGroup, 0, 0);

        setLayout(layout);

        setWindowTitle(tr("Connexion to Host"));

        QObject::connect(_confirm,SIGNAL(clicked()),&fenetre,SLOT(confirm()));

    }

    QString IpDialog::getIp(){
        return _lineEditIp->text();
    }

    QString IpDialog::getPort(){
        return _lineEditPort->text();
    }

    }

