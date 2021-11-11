#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    QNetworkProxyFactory::setUseSystemConfiguration(false);
    socket = new QTcpSocket(this);
}

bool Client::connecttoserver(){
    if (host==QHostAddress::Null){
        qDebug() << "Host is not set";
    }
    else if (port==0){
        qDebug() << "Port not set";
    }
    else{
        socket->connectToHost(host, port);
        qDebug() << "Connecting to host: "<<host.toString()<<" "<<port;
    }
    if(socket->waitForConnected(3000)){
        qDebug() << "Connected.";
        connect(socket,SIGNAL(readyRead()),this,SLOT(readData()));
        return 1;
    }
    else{
        qDebug()<<"Could Not Connect.";
        return 0;
    }

    conn_timeout = new QTimer(this);
    connect(conn_timeout,&QTimer::timeout,this,&Client::timeout);
    conn_timeout->start(3000);

}

Client::~Client(){
    if(socket){
        socket->close();
        delete socket;
    }
}


void Client::readData(){
    data = socket->readAll();
    qDebug() << data;
    emit newDataRead();
}

QHostAddress Client::getHostIP(){
    return host;
}

quint16 Client::getPortNum(){
    return port;
}

void Client::setHostIp(QHostAddress adr){
    host = adr;
}

void Client::setPortNum(quint16 portnum){
    port = portnum;
}

void Client::timeout(){
    socket->close();
}
