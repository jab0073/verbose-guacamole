#include "gamescenes.h"
#include <QLabel>
#include <QPushButton>

GameScenes::GameScenes(QObject* par){
    parent = par;
};

GameScenes::~GameScenes(){
    if (title_screen){
        delete title;
        delete cgbtn;
        delete jgbtn;
        delete title_screen;
    }
    if (jg_screen){
        delete ip_msg;
        delete ip_prompt;
        delete port_msg;
        delete port_prompt;
        delete jg_screen;
    }
    if (char_select_screen){
        delete server_label;
        delete playerID_label;
        delete char_select_screen;
    }
    if (stage_select_screen){
        delete stage_select_screen;
    }
    if (options_screen){
        delete lhandmsg;
        delete lhand;
        delete rhandmsg;
        delete rhand;
        delete optionslabel;
        delete options_back_btn;
        delete options_save_btn;
        delete ctrlgroup;
        delete options_screen;
    }
}

QGraphicsScene* GameScenes::gettitlescreen(){
    if (!title_screen)
        maketitlescreen();
    return title_screen;
}

void GameScenes::maketitlescreen(){
    title_screen = new QGraphicsScene;
    title_screen->setBackgroundBrush(Qt::cyan);
    title_screen->setSceneRect(-definitions::width/2,-definitions::height/2,definitions::width,definitions::height);

    title = new QLabel;

    QPixmap logo = QPixmap(":/Images/Logo.png");
    logo = logo.scaledToWidth((definitions::width/8)*5);
    title->setPixmap(logo);

    title->setGeometry(
                -logo.width()/2,
                -logo.height()/2-(definitions::height/6),
                logo.width(),
                logo.height());


    title->setAttribute(Qt::WA_TranslucentBackground);

    title_screen->addWidget(title);

    cgbtn = new QPushButton;
    QPixmap cgbtn_pix = QPixmap(":/Images/CG_Button.png").scaledToWidth((definitions::width/16)*5);

    cgbtn->setIconSize(cgbtn_pix.size());

    cgbtn->setIcon(QIcon(cgbtn_pix));
    QRect cgbtn_geo;
    cgbtn_geo.setX(-cgbtn_pix.width()/2-((definitions::width/16)*3));
    cgbtn_geo.setY(-cgbtn_pix.height()/2+((definitions::height/24)*3));
    cgbtn_geo.setWidth(cgbtn_pix.width());
    cgbtn_geo.setHeight(cgbtn_pix.height());
    cgbtn->setGeometry(cgbtn_geo);

    cgbtn->setAttribute(Qt::WA_TranslucentBackground);
    cgbtn->setAttribute(Qt::WA_TransparentForMouseEvents);
    cgbtn->setFlat(true);
    cgbtn->setStyleSheet("QPushButton{background-color: rgba(0,0,0,0);border:none;color:rgb(255, 255, 255);}"
                                       "QPushButton:hover{background-color: rgba(0,0,0,0);border:none;color:rgb(255, 255, 255);}"
                                       "QPushButton:checked{background-color: rgba(0,0,0,0);border:none;color:rgb(255, 255, 255);}");

    title_screen->addWidget(cgbtn);

    jgbtn = new QPushButton;
    QPixmap jgbtn_pix = QPixmap(":/Images/JG_Button.png").scaledToWidth((definitions::width/16)*5);

    jgbtn->setIconSize(jgbtn_pix.size());

    jgbtn->setIcon(QIcon(jgbtn_pix));
    QRect jgbtn_geo;
    jgbtn_geo.setX(-jgbtn_pix.width()/2+((definitions::width/16)*3));
    jgbtn_geo.setY(-jgbtn_pix.height()/2+((definitions::height/24)*3));
    jgbtn_geo.setWidth(jgbtn_pix.width());
    jgbtn_geo.setHeight(jgbtn_pix.height());
    jgbtn->setGeometry(jgbtn_geo);

    jgbtn->setAttribute(Qt::WA_TranslucentBackground);
    jgbtn->setAttribute(Qt::WA_TransparentForMouseEvents);
    jgbtn->setFlat(true);
    jgbtn->setStyleSheet("QPushButton{background-color: rgba(0,0,0,0);border:none;color:rgb(255, 255, 255);}"
                                       "QPushButton:hover{background-color: rgba(0,0,0,0);border:none;color:rgb(255, 255, 255);}"
                                       "QPushButton:checked{background-color: rgba(0,0,0,0);border:none;color:rgb(255, 255, 255);}");

    title_screen->addWidget(jgbtn);

    options_btn = new QPushButton;
    options_btn->setText("Options");
    options_btn->setGeometry(((definitions::width/2)-5)-options_btn->sizeHint().width(),-((definitions::height/2)-5),options_btn->sizeHint().width(),options_btn->sizeHint().height());
    title_screen->addWidget(options_btn);

    /*
    quit_btn = new QPushButton;
    quit_btn->setText("Quit");
    quit_btn->setGeometry(((definitions::width/2)-5)-quit_btn->sizeHint().width(),((definitions::height/2)-5)-quit_btn->sizeHint().height(),
                                  quit_btn->sizeHint().width(),quit_btn->sizeHint().height());
    title_screen->addWidget(quit_btn);
    */


    connect(cgbtn,SIGNAL(clicked()),parent,SLOT(create_game()));
    connect(jgbtn,SIGNAL(clicked()),parent,SLOT(join_game()));
    connect(options_btn,SIGNAL(clicked()),parent,SLOT(options_menu()));
    //connect(quit_btn,&QPushButton::clicked,parent,SLOT(quit_game()));
}

QGraphicsScene* GameScenes::getoptions_screen(){
    if(!options_screen)
        makeoptions_screen();
    else {
        if(isRightHanded){
            rhand->setChecked(true);
        }
        else{
            lhand->setChecked(true);
        }
    }
    qDebug() << isRightHanded;
    return options_screen;
}

void GameScenes::makeoptions_screen(){
    options_screen = new QGraphicsScene;
    options_screen->setBackgroundBrush(Qt::cyan);
    options_screen->setSceneRect(-definitions::width/2,-definitions::height/2,definitions::width,definitions::height);

    optionslabel = new QLabel;
    optionslabel->setText("Options");
    optionslabel->setGeometry(-optionslabel->sizeHint().width()/2,-(definitions::height/2)+(definitions::height/12),optionslabel->sizeHint().width(),optionslabel->sizeHint().height());
    optionslabel->setAttribute(Qt::WA_TranslucentBackground);

    options_screen->addWidget(optionslabel);

    rhand = new QRadioButton;
    lhand = new QRadioButton;
    rhandmsg = new QLabel;
    lhandmsg = new QLabel;
    rhandmsg->setText("Right Hand Controls: I,J,K,L for Movement");
    lhandmsg->setText("Left Hand Controls: W,A,S,D for Movement");

    ctrlgroup = new QButtonGroup;
    ctrlgroup->addButton(rhand);
    ctrlgroup->addButton(lhand);
    lhand->setChecked(true);

    rhand->setGeometry(-rhand->sizeHint().width()-(rhandmsg->sizeHint().width()/2),-definitions::height/12,
                       rhand->sizeHint().width(),rhand->sizeHint().height());
    lhand->setGeometry(-lhand->sizeHint().width()-(lhandmsg->sizeHint().width()/2),definitions::height/12,
                       rhand->sizeHint().width(),rhand->sizeHint().height());
    rhandmsg->setGeometry(-(rhandmsg->sizeHint().width()/2)+(rhand->sizeHint().width()/2),-definitions::height/12,
                          rhandmsg->sizeHint().width(),rhandmsg->sizeHint().height());
    lhandmsg->setGeometry(-(lhandmsg->sizeHint().width()/2)+(lhand->sizeHint().width()/2),definitions::height/12,
                          lhandmsg->sizeHint().width(),lhandmsg->sizeHint().height());

    rhandmsg->setAttribute(Qt::WA_TranslucentBackground);
    lhandmsg->setAttribute(Qt::WA_TranslucentBackground);

    options_screen->addWidget(rhand);
    options_screen->addWidget(lhand);
    options_screen->addWidget(rhandmsg);
    options_screen->addWidget(lhandmsg);

    options_back_btn = new QPushButton;
    options_back_btn->setText("Back");
    options_back_btn->setGeometry(-((definitions::width/2)-5),((definitions::height/2)-5)-options_back_btn->sizeHint().height(),
                                  options_back_btn->sizeHint().width(),options_back_btn->sizeHint().height());
    options_screen->addWidget(options_back_btn);

    options_save_btn = new QPushButton;
    options_save_btn->setText("Save");
    options_save_btn->setGeometry(((definitions::width/2)-5)-options_save_btn->sizeHint().width(),((definitions::height/2)-5)-options_save_btn->sizeHint().height(),
                                  options_save_btn->sizeHint().width(),options_save_btn->sizeHint().height());
    options_screen->addWidget(options_save_btn);

    connect(options_back_btn,SIGNAL(clicked()),parent,SLOT(options_back()));
    connect(options_save_btn,&QPushButton::clicked,this,&GameScenes::options_save);
}

void GameScenes::options_save(){
    if (options_screen){
        if (rhand->isChecked())
            isRightHanded = true;
        else
            isRightHanded = false;
    }
    qDebug() << isRightHanded;
}

bool GameScenes::getRightHand(){
    if (options_screen){
        if (isRightHanded)
            return true;
    }
    return false;
}

QGraphicsScene* GameScenes::getjg_screen(){
    if (!jg_screen)
        makejg_screen();
    return jg_screen;
}

void GameScenes::makejg_screen(){
    jg_screen = new QGraphicsScene;
    jg_screen->setBackgroundBrush(Qt::cyan);

    jg_screen->setSceneRect(-definitions::width/2,-definitions::height/2,definitions::width,definitions::height);

    ip_msg = new QLabel;
    ip_msg->setText("Server IP: ");
    port_msg = new QLabel;
    port_msg->setText("Port #: ");
    ip_prompt = new QLineEdit;
    port_prompt = new QLineEdit;

    ip_msg->setGeometry(-((ip_msg->sizeHint().width()/2)+(ip_prompt->sizeHint().width()/2)),
                        -((ip_msg->sizeHint().height())+(definitions::height/30)),
                        ip_msg->sizeHint().width(),ip_msg->sizeHint().height());
    ip_msg->setAttribute(Qt::WA_TranslucentBackground);

    ip_prompt->setGeometry(ip_msg->sizeHint().width()-(ip_prompt->sizeHint().width()/2),
                           -((ip_prompt->sizeHint().height())+(definitions::height/30)),
                           ip_prompt->sizeHint().width(),ip_prompt->sizeHint().height());

    port_msg->setGeometry(-((port_msg->sizeHint().width()/2)+(port_prompt->sizeHint().width()/2)),
                          (definitions::height/30),
                          port_msg->sizeHint().width(),port_msg->sizeHint().height());
    port_msg->setAttribute(Qt::WA_TranslucentBackground);

    port_prompt->setGeometry(port_msg->sizeHint().width()-(port_prompt->sizeHint().width()/2),
                             (definitions::height/30),
                             port_prompt->sizeHint().width(),port_prompt->sizeHint().height());

    jg_screen->addWidget(ip_msg);
    jg_screen->addWidget(ip_prompt);

    jg_screen->addWidget(port_msg);
    jg_screen->addWidget(port_prompt);

    connectbtn = new QPushButton;
    connectbtn->setText("Connect");

    connectbtn->setGeometry((definitions::width/8)-connectbtn->sizeHint().width()/2,(definitions::height/6)-connectbtn->sizeHint().height()/2,connectbtn->sizeHint().width(),connectbtn->sizeHint().height());

    jg_screen->addWidget(connectbtn);

    jg_back = new QPushButton;
    jg_back->setText("Back");
    jg_back->setGeometry(-((definitions::width/2)-5),((definitions::height/2)-5)-jg_back->sizeHint().height(),jg_back->sizeHint().width(),jg_back->sizeHint().height());
    jg_screen->addWidget(jg_back);

    connect(jg_back,SIGNAL(clicked()),parent,SLOT(jg_back()));

    connect(connectbtn,SIGNAL(clicked()),parent,SLOT(connectclient()));
}

bool GameScenes::getiptext(QString& adr){
    if (jg_screen){
        adr = ip_prompt->displayText();
        return true;
    }
    else
        return false;
}

bool GameScenes::getporttext(QString& port){
    if (jg_screen){
        port = port_prompt->displayText();
        return true;
    }
    else
        return false;
}

QGraphicsScene* GameScenes::getchar_select_screen(QString ip, QString port){
    if (!char_select_screen)
        makechar_select_screen(ip,port);
    return char_select_screen;
}

void GameScenes::makechar_select_screen(QString ip, QString port){
    char_select_screen = new QGraphicsScene;

    char_select_screen->setSceneRect(-definitions::width/2,-definitions::height/2,definitions::width,definitions::height);

    char_select_screen->setBackgroundBrush(Qt::cyan);

    server_label = new QLabel;
    server_label->setText("Server IP: "+ip+"\n\rPort #: "+port);
    server_label->setGeometry(-server_label->sizeHint().width()/2,-((definitions::height/2)-5),server_label->sizeHint().width(),server_label->sizeHint().height());
    server_label->setAttribute(Qt::WA_TranslucentBackground);

    char_select_screen->addWidget(server_label);

    playerID_label = new QLabel;
    playerID_label->setText("Player 0");
    playerID_label->setGeometry(-((definitions::width/2)-5),-((definitions::height/2)-5),playerID_label->sizeHint().width(),playerID_label->sizeHint().height());
    playerID_label->setAttribute(Qt::WA_TranslucentBackground);

    char_select_screen->addWidget(playerID_label);

    char_sel_back = new QPushButton;
    char_sel_back->setText("Back");
    char_sel_back->setGeometry(-((definitions::width/2)-5),((definitions::height/2)-5)-char_sel_back->sizeHint().height(),char_sel_back->sizeHint().width(),char_sel_back->sizeHint().height());
    char_select_screen->addWidget(char_sel_back);

    connect(char_sel_back,SIGNAL(clicked()),parent,SLOT(char_sel_back()));
}

QGraphicsScene* GameScenes::getstage_select_screen(){
    if (!stage_select_screen)
        makestage_select_screen();
    return stage_select_screen;
}

void GameScenes::makestage_select_screen(){
    return;
}

void GameScenes::editPlayerId(QString newtext){
    playerID_label->setText(newtext);
}
