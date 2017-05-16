#include "ipwindow.h"
#include "ui_widget.h"

using namespace std;

IpWindow::IpWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget){
    ui->setupUi(this);


}

IpWindow::~IpWindow(){
    delete ui;
}

void IpWindow::closeEvent(QCloseEvent *event){
    std::cout<<"do something when closing"<<std::endl;
    if(_thread->getIsConnected()){
        _thread->sendMessage(GameMessage(TypeMessage::QUIT));
    }
}





