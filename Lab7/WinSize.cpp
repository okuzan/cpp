#include "WinSize.h"

int WinSize::length = 500;
int WinSize::height = 500;

WinSize::WinSize(Canvas *canvas) : QWidget()
{

    QVBoxLayout *layout = new QVBoxLayout(this);
    QFormLayout *given = new QFormLayout;
    lengthLine = new QLineEdit;
    heightLine = new QLineEdit;

    given->addRow("Enter length", lengthLine);
    given->addRow("Enter height", heightLine);


    create = new QPushButton("Create");

    layout->addLayout(given);
    layout->addWidget(create);

    connect(create,SIGNAL(clicked(bool)),canvas,SLOT(nouveauCanevas()));
    connect(lengthLine,SIGNAL(textChanged(QString)),this,SLOT(getLengthLine(QString)));
    connect(heightLine,SIGNAL(textChanged(QString)),this,SLOT(getHeightLine(QString)));
    connect(create,SIGNAL(clicked(bool)),this,SLOT(close()));
}

void WinSize::createClick() {   this->show();   }
void WinSize::getLengthLine(QString length) {   length = length.toInt();     }
void WinSize::getHeightLine(QString height){   height = height.toInt(); }
int WinSize::getLength(){   return length;  }
int WinSize::getHeight(){   return height;  }
