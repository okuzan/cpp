#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "string.h"
#include <iostream>
#include <QString>
#include <QByteArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(300, 150));
    connect(ui->choose_btn, SIGNAL(clicked()), this, SLOT(choose_file()));
    connect(ui->create_btn, SIGNAL(clicked()), this, SLOT(create_file()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::choose_file(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open text file"), "D:/", tr("Text files (*.txt *.doc *.docx *.rtf)"));

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);
    QString text = "";
    while(!in.atEnd())
        text+= in.readLine().replace("\n", "").replace("\t", " ");
    read_text = text;
    file.close();

    if(fileName!=""){
        QStringList pieces = fileName.split( "/" );
        ui->status_lbl->setText(pieces.last());
    }
}
void MainWindow::create_file(){
    if(ui->status_lbl->text() == "Not Selected")
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "You haven't chosen anything yet!");
        messageBox.setFixedSize(500, 200);
        return;
    }
    QString filename = QFileDialog::getSaveFileName(this, tr("Save to"),  "D:/formatted_file.txt", tr("Text files (*.txt *.doc *.docx *.rtf)"));
    QFile f (filename);
    f.open (QIODevice::WriteOnly | QIODevice::ReadWrite);
    QTextStream stream(&f);
    stream << read_text.toUtf8();
    f.close();
}
