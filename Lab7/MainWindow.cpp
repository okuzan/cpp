#include "MainWindow.h"
#include "Canvas.h"
#include "WinSize.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow():
    QMainWindow(),
    ui(new Ui::MainWindow)
{
    resize(500,500);
    ui->setupUi(this);
    //Initialisation variables
    drawEnable = 1;
    rectangleEnable = 0;
    circleEnable = 0;
    traitEnable = 0;
    valueSlider = 1;


    Canvas *canvas = new Canvas(this);
    WinSize *winsize= new WinSize(canvas);
    setCentralWidget(canvas);

    //Menu Fichier
    QMenu *menuFichier = menuBar()->addMenu("File -FR");

    QAction *actionNouveau = new QAction("New",this);
    menuFichier->addAction(actionNouveau);
    QAction *actionSauvegarder = new QAction("Save",this);
    menuFichier->addAction(actionSauvegarder);
    QAction *actionOuvrir = new QAction("Open",this);
    menuFichier->addAction(actionOuvrir);

    connect(actionNouveau,SIGNAL(triggered(bool)),winsize,SLOT(createClick()));
    connect(actionSauvegarder,SIGNAL(triggered(bool)),canvas,SLOT(saveCanvas()));
    connect(actionOuvrir,SIGNAL(triggered(bool)),canvas,SLOT(openCanvas()));

    //Menu forme
    QMenu *menuForme = menuBar()->addMenu("&Forme");

    QAction *actionDraw = new QAction("Dessiner",this);
    menuForme->addAction(actionDraw);
    QAction *actionRectangle = new QAction("Rectangle",this);
    menuForme->addAction(actionRectangle);
    QAction *actionCercle = new QAction("Cercle",this);
    menuForme->addAction(actionCercle);
    QAction *actionTrait = new QAction("Trait",this);
    menuForme->addAction(actionTrait);


    connect(actionDraw,SIGNAL(triggered(bool)),this,SLOT(slotDraw()));
    connect(actionRectangle,SIGNAL(triggered(bool)),this,SLOT(slotRectangle()));
    connect(actionCercle,SIGNAL(triggered(bool)),this,SLOT(slotCircle()));
    connect(actionTrait,SIGNAL(triggered(bool)),this,SLOT(slotTrait()));

    //Menu
    QMenu *menuOutils = menuBar()->addMenu("Outils");

    QAction *actionRemplir = new QAction("Remplir",this);
    menuOutils->addAction(actionRemplir);
    QAction *actionRetour = new QAction("Retour en arrière",this);
    actionRetour->setShortcut(QKeySequence("Ctrl+Z"));
    menuOutils->addAction(actionRetour);

    connect(actionRemplir,SIGNAL(triggered(bool)),this,SLOT(slotFill()));
    connect(actionRetour,SIGNAL(triggered(bool)),canvas,SLOT(returnCanvas()));

    //bar
    QToolBar *toolBar = addToolBar("Couleur");

    QPushButton *boutonCouleur = new QPushButton;
    boutonCouleur->setText("Couleur");
    colorDialog = new QColorDialog;
    toolBar->addWidget(boutonCouleur);

    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(1,15);
    toolBar->addWidget(slider);

    connect(boutonCouleur,SIGNAL(clicked(bool)),this,SLOT(slotColor()));
    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(slotSlider(int)));
}

bool MainWindow::getDrawEnable(){   return drawEnable;  }
bool MainWindow::getRectangleEnable(){   return rectangleEnable;     }
bool MainWindow::getCircleEnable(){   return circleEnable;    }
bool MainWindow::getTraitEnable(){   return traitEnable; }
void MainWindow::slotColor(){   color = colorDialog->getColor();    }
void MainWindow::slotSlider(int x) {   valueSlider = x;    }
int MainWindow::getValueSlider(){   return valueSlider; }
QColor MainWindow::getColor(){   return color;  }

//choosing right regime
void MainWindow::slotDraw()
{
    drawEnable = 1;
    rectangleEnable = 0;
    circleEnable = 0;
    traitEnable = 0;
}
void MainWindow::slotRectangle()
{
    drawEnable = 0;
    rectangleEnable = 1;
    circleEnable = 0;
    traitEnable = 0;
}
void MainWindow::slotCircle()
{
    drawEnable = 0;
    rectangleEnable = 0;
    circleEnable = 1;
    traitEnable = 0;
}

void MainWindow::slotTrait()
{
    drawEnable = 0;
    rectangleEnable = 0;
    circleEnable = 0;
    traitEnable = 1;
}

void MainWindow::on_actionNew_triggered()
{

}
