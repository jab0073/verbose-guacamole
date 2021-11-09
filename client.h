#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkProxyFactory>
#include <QDebug>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    bool connecttoserver(QHostAddress host, quint16 port);

    QHostAddress getHostIP();
    quint16 getPortNum();

    QByteArray data;

signals:
    void newDataRead();
public slots:
    void readData();
private:
    QTcpSocket* socket;
};

#endif // CLIENT_H
