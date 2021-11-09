#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    view = new QGraphicsView(this);

    QVBoxLayout* layout = new QVBoxLayout;
    setLayout(layout);

    layout->addWidget(view);
    resize(800,600);
    view->resize(800,600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    title_screen = new QGraphicsScene;
    title_screen->setBackgroundBrush(Qt::cyan);
    title_screen->setSceneRect(-400,-300,800,600);

    QLabel* title = new QLabel;

    QPixmap logo = QPixmap(":/Images/Logo.png");
    logo = logo.scaledToWidth(500);
    title->setPixmap(logo);

    title->setGeometry(
                -logo.width()/2,
                -logo.height()/2-100,
                logo.width(),
                logo.height());


    title->setAttribute(Qt::WA_TranslucentBackground);

    title_screen->addWidget(title);

    view->setScene(title_screen);

    QPushButton* cgbtn = new QPushButton;
    QPixmap cgbtn_pix = QPixmap(":/Images/CG_Button.png").scaledToWidth(250);

    cgbtn->setIconSize(cgbtn_pix.size());

    cgbtn->setIcon(QIcon(cgbtn_pix));
    QRect cgbtn_geo;
    cgbtn_geo.setX(-cgbtn_pix.width()/2-150);
    cgbtn_geo.setY(-cgbtn_pix.height()/2+75);
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

    QPushButton* jgbtn = new QPushButton;
    QPixmap jgbtn_pix = QPixmap(":/Images/JG_Button.png").scaledToWidth(250);

    jgbtn->setIconSize(jgbtn_pix.size());

    jgbtn->setIcon(QIcon(jgbtn_pix));
    QRect jgbtn_geo;
    jgbtn_geo.setX(-jgbtn_pix.width()/2+150);
    jgbtn_geo.setY(-jgbtn_pix.height()/2+75);
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


    connect(cgbtn,SIGNAL(clicked()),this,SLOT(create_game()));
    connect(jgbtn,SIGNAL(clicked()),this,SLOT(join_game()));
}

void MainWindow::create_game(){
    server = new Server(this);

    client = new Client(this);
    client->connecttoserver(server->host,server->port);

    char_select_screen = new QGraphicsScene;

    char_select_screen->setSceneRect(-400,-300,800,600);

    char_select_screen->setBackgroundBrush(Qt::cyan);

    view->setScene(char_select_screen);

    QLabel* server_label = new QLabel;
    server_label->setText("Server IP: "+server->host.toString()+"\n\rPort #: "+QString::number(server->port));
    server_label->setGeometry(-server_label->sizeHint().width()/2,-server_label->sizeHint().height()/2,server_label->sizeHint().width(),server_label->sizeHint().height());
    server_label->setAttribute(Qt::WA_TranslucentBackground);

    char_select_screen->addWidget(server_label);

    playerID_label = new QLabel;
    playerID_label->setText("Player 0");
    playerID_label->setGeometry(-400,-300,playerID_label->sizeHint().width(),playerID_label->sizeHint().height());
    playerID_label->setAttribute(Qt::WA_TranslucentBackground);

    char_select_screen->addWidget(playerID_label);

    connect(client,SIGNAL(newDataRead()),this,SLOT(parseData()));
}

void MainWindow::join_game(){
    client = new Client(this);

    jg_screen = new QGraphicsScene;
    jg_screen->setBackgroundBrush(Qt::cyan);

    view->setScene(jg_screen);
    jg_screen->setSceneRect(-400,-300,800,600);

    QLabel* ip_msg = new QLabel;
    ip_msg->setText("Server IP: ");
    ip_msg->setGeometry(-50-ip_msg->sizeHint().width()/2,-ip_msg->sizeHint().height()/2-20,ip_msg->sizeHint().width(),ip_msg->sizeHint().height());
    ip_msg->setAttribute(Qt::WA_TranslucentBackground);

    ip_prompt = new QLineEdit;
    ip_prompt->setGeometry(50-ip_prompt->sizeHint().width()/2,-ip_prompt->sizeHint().height()/2-20,ip_prompt->sizeHint().width(),ip_prompt->sizeHint().height());

    QLabel* port_msg = new QLabel;
    port_msg->setText("Port #: ");
    port_msg->setGeometry(-50-port_msg->sizeHint().width()/2,-port_msg->sizeHint().height()/2+20,port_msg->sizeHint().width(),port_msg->sizeHint().height());
    port_msg->setAttribute(Qt::WA_TranslucentBackground);

    port_prompt = new QLineEdit;
    port_prompt->setGeometry(50-port_prompt->sizeHint().width()/2,-port_prompt->sizeHint().height()/2+20,port_prompt->sizeHint().width(),port_prompt->sizeHint().height());

    jg_screen->addWidget(ip_msg);
    jg_screen->addWidget(ip_prompt);

    jg_screen->addWidget(port_msg);
    jg_screen->addWidget(port_prompt);

    QPushButton* connectbtn = new QPushButton;
    connectbtn->setText("Connect");

    connectbtn->setGeometry(100-connectbtn->sizeHint().width()/2,-connectbtn->sizeHint().height()/2+100,connectbtn->sizeHint().width(),connectbtn->sizeHint().height());

    jg_screen->addWidget(connectbtn);

    connect(connectbtn,SIGNAL(clicked()),this,SLOT(connectclient()));
}
void MainWindow::connectclient(){
    if(client->connecttoserver(QHostAddress(ip_prompt->displayText()),quint16(port_prompt->displayText().toUInt()))){

        char_select_screen = new QGraphicsScene;

        char_select_screen->setSceneRect(-400,-300,800,600);

        char_select_screen->setBackgroundBrush(Qt::cyan);

        view->setScene(char_select_screen);

        QLabel* server_label = new QLabel;
        server_label->setText("Server IP: "+client->getHostIP().toString()+"\n\rPort #: "+QString::number(client->getPortNum()));
        server_label->setGeometry(-server_label->sizeHint().width()/2,-server_label->sizeHint().height()/2,server_label->sizeHint().width(),server_label->sizeHint().height());
        server_label->setAttribute(Qt::WA_TranslucentBackground);

        char_select_screen->addWidget(server_label);

        playerID_label = new QLabel;
        playerID_label->setText(" Player 0");
        playerID_label->setGeometry(-400,-300,playerID_label->sizeHint().width(),playerID_label->sizeHint().height());
        playerID_label->setAttribute(Qt::WA_TranslucentBackground);

        char_select_screen->addWidget(playerID_label);

        connect(client,SIGNAL(newDataRead()),this,SLOT(parseData()));
    }
}

void MainWindow::parseData(){
    if(client->data[0]=='P'){
        playerID = client->data[1]-0x30;
        playerID_label->setText(" Player "+QString::number(playerID));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
