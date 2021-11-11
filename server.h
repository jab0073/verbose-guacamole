#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include <QLabel>
#include <QMessageBox>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QNetworkProxyFactory>
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>
#include <QString>
#include "client.h"
#include "definitions.h"

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();
    QHostAddress gethostaddress();
    quint16 getport();
signals:
    void serverReady(QHostAddress,quint16);

private slots:
    void newConnection();
    void sendData(QByteArray data, QTcpSocket* serverclient);
    //Called on refresh timer timeout
    void refresh_connections();

private:
    QHostAddress host = QHostAddress::Null;
    quint16 port = 0;
    QTcpServer *tcpServer = nullptr;
    QList<QTcpSocket*> serverclients;
    QTimer* conn_monitor = nullptr;
    //Specific function to check connections only on timer timeout
    void checkconnections();
};

#endif // SERVER_H
