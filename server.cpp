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

    conn_monitor = new QTimer(this);
    connect(conn_monitor,&QTimer::timeout,this,&Server::refresh_connections);
    conn_monitor->start(2000);
}

Server::~Server(){
    if (tcpServer){
        tcpServer->close();
        delete tcpServer;
    }
    delete conn_monitor;
}

void Server::newConnection()
{
    serverclients.append(tcpServer->nextPendingConnection());
    QByteArray player_info = "PX";
    player_info[1] = serverclients.size()+0x30;
    sendData(player_info,serverclients.at(serverclients.size()-1));
    if (serverclients.count()==definitions::max_players){
        tcpServer->pauseAccepting();
    }
}

void Server::sendData(QByteArray data, QTcpSocket* serverclient)
{
    if (serverclient->state() == QAbstractSocket::ConnectedState)
    {
        serverclient->write(data);
        serverclient->flush();
    }
    //This is probably not the best place to reset timer but it works for now
    conn_monitor->start(2000);
}

QHostAddress Server::gethostaddress(){
    return host;
}

quint16 Server::getport(){
    return port;
}

void Server::refresh_connections(){
    QByteArray refresh_message = "R";
    for (QTcpSocket* socket : serverclients){
        sendData(refresh_message,socket);
    }
    checkconnections();
}

void Server::checkconnections(){
    int count = 0;
    for (QTcpSocket* socket : serverclients){
        if(!(socket->state() == QAbstractSocket::ConnectedState)){
            qDebug() << "Player " << (count+1) << " lost connection.";
            socket->abort();
            serverclients.removeAt(count);
            while (tcpServer->hasPendingConnections()){
                delete tcpServer->nextPendingConnection();
            }
            tcpServer->resumeAccepting();
        }
        count++;
    }
}
