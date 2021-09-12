#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->list_a->setDragEnabled(true);
    ui->list_a->setAcceptDrops(true);
    ui->list_a->setDropIndicatorShown(true);
    ui->list_a->setDefaultDropAction(Qt::MoveAction);
    ui->list_b->setDragEnabled(true);
    ui->list_b->setAcceptDrops(true);
    ui->list_b->setDropIndicatorShown(true);
    ui->list_b->setDefaultDropAction(Qt::MoveAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

