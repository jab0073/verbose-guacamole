#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QString>
#include "server.h"
#include "client.h"
#include "gamescenes.h"

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
    void char_sel_back();
    void jg_back();
    void options_menu();
    void options_back();
    void connectclient();
    void parseData();
private:
    Ui::MainWindow *ui;
    Server* server = nullptr;
    Client* client = nullptr;
    GameScenes* sceneselect;
    QVBoxLayout* layout;
    QGraphicsView* view = nullptr;
    bool userIsHost = false;
    int playerID;
};

#endif // MAINWINDOW_H
