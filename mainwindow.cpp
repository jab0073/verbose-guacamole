#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sceneselect = new GameScenes(this);

    view = new QGraphicsView(this);

    layout = new QVBoxLayout;
    setLayout(layout);

    layout->addWidget(view);
    resize(definitions::width,definitions::height);
    view->resize(definitions::width,definitions::height);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setScene(sceneselect->gettitlescreen());

}


void MainWindow::create_game(){
    server = new Server(this);

    client = new Client(this);
    client->setHostIp(server->gethostaddress());
    client->setPortNum(server->getport());
    client->connecttoserver();

    view->setScene(sceneselect->getchar_select_screen(server->gethostaddress().toString(),QString::number(server->getport())));

    userIsHost = true;
    connect(client,SIGNAL(newDataRead()),this,SLOT(parseData()));
}

void MainWindow::join_game(){
    client = new Client(this);

    view->setScene(sceneselect->getjg_screen());
}

void MainWindow::connectclient(){
    QString host;
    QString port;
    if (sceneselect->getiptext(host) && sceneselect->getporttext(port)){
        client->setHostIp(QHostAddress(host));
        client->setPortNum(quint16(port.toUInt()));
        if(client->connecttoserver()){

            view->setScene(sceneselect->getchar_select_screen(host,port));

            connect(client,SIGNAL(newDataRead()),this,SLOT(parseData()));
        }
    }
}

void MainWindow::char_sel_back(){
    if (userIsHost){
        delete client;
        client = nullptr;
        delete server;
        server = nullptr;
        view->setScene(sceneselect->gettitlescreen());
        userIsHost = false;
    }
    else{
        delete client;
        client = nullptr;
        view->setScene(sceneselect->getjg_screen());
    }
}

void MainWindow::jg_back(){
    delete client;
    client = nullptr;
    view->setScene(sceneselect->gettitlescreen());
}

void MainWindow::options_menu(){
    view->setScene(sceneselect->getoptions_screen());
}

void MainWindow::options_back(){
    view->setScene(sceneselect->gettitlescreen());
}

void MainWindow::parseData(){
    if(client->data[0]=='P'){
        playerID = client->data[1]-0x30;
        sceneselect->editPlayerId(" Player "+QString::number(playerID));
    }
}

MainWindow::~MainWindow()
{
    delete sceneselect;
    delete view;
    delete layout;
    if (server)
        delete server;
    if (client)
        delete client;
    delete ui;
}
