#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    QNetworkProxyFactory::setUseSystemConfiguration(false);
    socket = new QTcpSocket(this);
}

bool Client::connecttoserver(QHostAddress host, quint16 port){

    socket->connectToHost(host, port);
    qDebug() << "Connecting to host: "<<host.toString()<<" "<<port;
    if(socket->waitForConnected(3000)){
        qDebug() << "Connected.";
        connect(socket,SIGNAL(readyRead()),this,SLOT(readData()));
        return 1;
    }
    else{
        qDebug()<<"Could Not Connect.";
        return 0;
    }


}


void Client::readData(){
    data = socket->readAll();
    qDebug() << data;
    emit newDataRead();
}

QHostAddress Client::getHostIP(){
    return socket->peerAddress();
}

quint16 Client::getPortNum(){
    return socket->peerPort();
}
