#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkProxyFactory>
#include <QDebug>
#include <QTimer>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();
    bool connecttoserver();
    void setHostIp(QHostAddress);
    void setPortNum(quint16);
    QHostAddress getHostIP();
    quint16 getPortNum();

    QByteArray data;

signals:
    void newDataRead();
public slots:
    void readData();
private:
    QTcpSocket* socket = nullptr;
    QHostAddress host = QHostAddress::Null;
    quint16 port = 0;
    QTimer* conn_timeout = nullptr;
private slots:
    void timeout();
};

#endif // CLIENT_H
