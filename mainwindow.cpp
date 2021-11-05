#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setMinimumSize(800,600); //this isn't final. We can fullscreen the game if we want.
    this->setWindowTitle("Beetle Sumo");

    main_menu = new QGraphicsScene(-400,-300,800,600); //initialize the coordinates to be like math but with weird y-axis
    main_menu->setBackgroundBrush(Qt::black); //temp. We'll put a graphic here later.
    view = new QGraphicsView;
    view->setScene(main_menu); //view holds scene
    view->setMinimumSize(810,610);
    this->layout()->addWidget(view); //layout holds view

    QGraphicsTextItem* title = new QGraphicsTextItem; //We'll make an official logo later, and this will be an image item
    title->setPlainText("Beetle Sumo");
    title->setDefaultTextColor(Qt::white);
    title->setPos(-(title->boundingRect().width())/2,-(title->boundingRect().height())/2); //wacky centering method
    main_menu->addItem(title);

    //button for create game; this will also look cool *later*
    QPushButton* createbtn = new QPushButton;
    //createbtn->setStyleSheet("color: white; background-color: transparent");
    createbtn->setGeometry(-150,100,100,50);
    createbtn->setText("Create Game");
    main_menu->addWidget(createbtn);

    //button for join game
    QPushButton* joinbtn = new QPushButton;
    joinbtn->setGeometry(50,100,100,50);
    joinbtn->setText("Join Game");
    main_menu->addWidget(joinbtn);

    //if buttons are clicked, do the stuff
    connect(createbtn,SIGNAL(clicked()),this,SLOT(create_game()));
    connect(joinbtn,SIGNAL(clicked()),this,SLOT(join_game()));
}

void MainWindow::create_game(){
    //uh oh. It's netcode time.
}

void MainWindow::join_game(){
    //good luck, Phillip lol

    //actually, these slots are just setup, so it shouldn't be too terrible.
    //the hard part will be the realtime connection maintenance.
}

//once we're able to establish a connection between players and send/receive input data,
//we can work on gameplay mechanics. We'll work on the gameplay and the mid-match netcode
//simultaneously since they're mutually dependent on each other. That part is gonna be an
//all hands on deck type thing. Fun times.

//I can make some UI elements over the weekend and start working on character animations then too.

MainWindow::~MainWindow()
{
    delete ui;
}
