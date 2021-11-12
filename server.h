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
#include "client.h"

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

private:
    QHostAddress host = QHostAddress::Null;
    quint16 port = 0;
    QTcpServer *tcpServer = nullptr;
    QList<QTcpSocket*> serverclients;
};

#endif // SERVER_H
