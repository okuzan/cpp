#ifndef HEADER_MAINWINDOW
#define HEADER_MAINWINDOW

#include "WinSize.h"
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
    MainWindow();
    bool getDrawEnable();
    bool getRectangleEnable();
    bool getCircleEnable();
    bool getTraitEnable();
    QColor getColor();
    int getValueSlider();

public slots :

    void slotDraw();
    void slotRectangle();
    void slotCircle();
    void slotTrait();
    void slotColor();
    void slotSlider(int x);

private slots:
    void on_actionNew_triggered();

private:
    bool drawEnable;
    bool rectangleEnable;
    bool circleEnable;
    bool traitEnable;
    int valueSlider;
    QColorDialog *colorDialog;
    QColor color;
    Ui::MainWindow *ui;
};

#endif
