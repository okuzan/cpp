#ifndef HEADER_MAINWINDOW
#define HEADER_MAINWINDOW

#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
    MainWindow();
    bool getRectangleState();
    bool getCircleState();
    bool getDrawState();
    bool getPolyState();
    int getPenWidth();
    QColor getColor();

public slots :
    void slotRectangle();
    void slotPenWidth();
    void slotCircle();
    void slotColor();
    void slotDraw();
    void slotPoly();

private:
    void defaultValues();
    bool rectangleEnabled;
    bool circleEnabled;
    bool polyEnabled;
    bool drawEnabled;
    int penWidth;
    QColorDialog *colorDialog;
    Ui::MainWindow *ui;
    QColor penColor;

};

#endif
