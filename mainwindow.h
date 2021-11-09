#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include "server.h"
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void join_ready(QHostAddress host, quint16 port);
public slots:
    void create_game();
    void join_game();

    void connectclient();

    void parseData();
private:
    Ui::MainWindow *ui;
    Server* server;
    Client* client;

    QGraphicsView* view;

    QGraphicsScene* title_screen;
    QGraphicsScene* jg_screen;
    QGraphicsScene* char_select_screen;
    QGraphicsScene* stage_select_screen;

    QLineEdit* ip_prompt;
    QLineEdit* port_prompt;

    QLabel* playerID_label;

    int playerID;
};

#endif // MAINWINDOW_H
