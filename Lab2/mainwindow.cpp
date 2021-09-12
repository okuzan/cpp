#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event){
    ui->textBrowser->setText("Width: " + QString::number(MainWindow::width()) +
                             " Height: " + QString::number(MainWindow::height()));

    ui->textBrowser->setGeometry(MainWindow::width()/2 - ui->textBrowser->width()/2, MainWindow::height()/2 - ui->textBrowser->width()/2,
                                 ui->textBrowser->width(), ui->textBrowser->height());
}
