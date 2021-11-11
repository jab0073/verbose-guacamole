#ifndef GAMESCENES_H
#define GAMESCENES_H

#include <QGraphicsScene>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QString>
#include <QDebug>
#include "definitions.h"

class GameScenes : public QObject
{
public:
    GameScenes(QObject* par);
    ~GameScenes();
    QGraphicsScene* gettitlescreen();
    QGraphicsScene* getjg_screen();
    QGraphicsScene* getchar_select_screen(QString,QString);
    QGraphicsScene* getstage_select_screen();
    QGraphicsScene* getoptions_screen();
    bool getiptext(QString&);
    bool getporttext(QString&);
    void editPlayerId(QString);
    bool getRightHand();
private:
    QGraphicsScene* title_screen = nullptr;
    QGraphicsScene* jg_screen = nullptr;
    QGraphicsScene* char_select_screen = nullptr;
    QGraphicsScene* stage_select_screen = nullptr;
    QGraphicsScene* options_screen = nullptr;
    QObject* parent;
    bool isRightHanded = false;
    void maketitlescreen();
    QLabel* title;
    QPushButton* cgbtn;
    QPushButton* jgbtn;
    QPushButton* options_btn;
    QPushButton* quit_btn;
    void makeoptions_screen();
    QRadioButton* rhand;
    QRadioButton* lhand;
    QButtonGroup* ctrlgroup;
    QLabel* lhandmsg;
    QLabel* rhandmsg;
    QLabel* optionslabel;
    QPushButton* options_back_btn;
    QPushButton* options_save_btn;
    void makejg_screen();
    QLabel* ip_msg;
    QLineEdit* ip_prompt;
    QLabel* port_msg;
    QLineEdit* port_prompt;
    QPushButton* connectbtn;
    QPushButton* jg_back;
    void makechar_select_screen(QString,QString);
    QLabel* server_label;
    QLabel* playerID_label = nullptr;
    QPushButton* char_sel_back;
    void makestage_select_screen();

public slots:
    void options_save();
};

#endif // GAMESCENES_H
