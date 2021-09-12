#include "mainwindow.h"
#include "canvas.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(): ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    //initialisation variables - small width, mode - pencil
    defaultValues();
    Canvas *canvas = new Canvas(this); //creating canvas pane to draw on
    setCentralWidget(canvas);

    //connecting ui elements to actions
    connect(ui->actionClear, SIGNAL(triggered(bool)), canvas, SLOT(newCanvas()));
    connect(ui->actionSave,SIGNAL(triggered(bool)), canvas, SLOT(saveCanvas()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), canvas, SLOT(openCanvas()));

    connect(ui->actionPencil, SIGNAL(triggered(bool)),this, SLOT(slotDraw()));
    connect(ui->actionRectangle,SIGNAL(triggered(bool)),this, SLOT(slotRectangle()));
    connect(ui->actionCircle, SIGNAL(triggered(bool)),this,SLOT(slotCircle()));
    connect(ui->actionPolygon, SIGNAL(triggered(bool)),this,SLOT(slotPoly()));

    connect(ui->actionReturn,SIGNAL(triggered(bool)),canvas,SLOT(returnCanvas()));
    connect(ui->actionChange_color, SIGNAL(triggered(bool)),this,SLOT(slotColor()));
    connect(ui->actionChange_width, SIGNAL(triggered(bool)),this,SLOT(slotPenWidth()));
}

bool MainWindow::getRectangleState(){   return rectangleEnabled;     }
bool MainWindow::getCircleState(){   return circleEnabled;    }
bool MainWindow::getDrawState(){   return drawEnabled;  }
bool MainWindow::getPolyState(){   return polyEnabled; }
int MainWindow::getPenWidth(){   return penWidth; }
QColor MainWindow::getColor(){   return penColor;  }

//choosing right regime
void MainWindow::slotPenWidth() { penWidth = QInputDialog::getInt(this, "Width of the pen", "Now:", penWidth, 1);    }
void MainWindow::slotColor(){   penColor = colorDialog->getColor();    }

void MainWindow::defaultValues(){
    slotDraw();
    penWidth = 1;
}
void MainWindow::slotDraw()
{
    drawEnabled = 1;
    rectangleEnabled = 0;
    circleEnabled = 0;
    polyEnabled = 0;
}
void MainWindow::slotRectangle()
{
    drawEnabled = 0;
    rectangleEnabled = 1;
    circleEnabled = 0;
    polyEnabled = 0;
}
void MainWindow::slotCircle()
{
    drawEnabled = 0;
    rectangleEnabled = 0;
    circleEnabled = 1;
    polyEnabled = 0;
}

void MainWindow::slotPoly()
{
    drawEnabled = 0;
    rectangleEnabled = 0;
    circleEnabled = 0;
    polyEnabled = 1;
}

