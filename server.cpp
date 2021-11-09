#include "server.h"

Server::Server(QWidget* parent):
    QObject (parent)
{
    QNetworkProxyFactory::setUseSystemConfiguration(false);

    tcpServer = new QTcpServer(this);

    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newConnection()));

    /*
    if(!tcpServer->listen(QHostAddress::Any,1234))
    {
        qDebug() << "Server could not start!";
    }
    else
    {
        qDebug() << "Server started";
    }
    */

    QList<QHostAddress> possibleAddresses = QNetworkInterface::allAddresses();


    for(QHostAddress address : possibleAddresses){
        if(address.toIPv4Address() && address != QHostAddress::LocalHost){
            host = address;
            break;
        }
    }

    if(!tcpServer->listen(host)){
        tcpServer->close();
        qDebug() << "Could not connect...";
    }
    else {
        qDebug() << "Server successfully created!";

        qDebug() << "Host IP: "  << host.toString();
        port = tcpServer->serverPort();
        qDebug() << "Port: " << port;

    }

}

void Server::newConnection()
{
    serverclients.append(tcpServer->nextPendingConnection());
    QByteArray player_info = "PX";
    player_info[1] = serverclients.size()+0x30;
    sendData(player_info,serverclients.at(serverclients.size()-1));

}
void Server::sendData(QByteArray data, QTcpSocket* serverclient)
{
    if (serverclient->state() == QAbstractSocket::ConnectedState)
    {
        serverclient->write(data);
        serverclient->flush();
    }
}
