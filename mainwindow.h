#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QVBoxLayout>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QGraphicsView* view;            //show the stuff

    QGraphicsScene* main_menu;      //holds the main menu
    QGraphicsScene* network_menu;   //holds multiplayer menu
    QGraphicsScene* css;            //holds the character select screen
    QGraphicsScene* sss;            //holds the stage select screen
    QGraphicsScene* gameplay;       //holds the match visuals;
    //each of these scenes stores the visuals for a certain menu/mode
    //in the game. The current menu/mode's graphics scene is pointed to
    //by view. We can use signals and slots to move between menus. When
    //we want to go from one menu to another, we just change the current
    //scene on view using view->setScene();


private slots:
    void create_game();
    void join_game();
};

#endif // MAINWINDOW_H
