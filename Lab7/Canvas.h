#ifndef CANVAS
#define CANVAS
#include <QtWidgets>
#include "MainWindow.h"

class Canvas : public QWidget
{
 Q_OBJECT

public :
    class Pile{
    public:
        Pile(int a,int b) : x(a), y(b) {}
        ~Pile();
        int getX(){   return x;   }
        int getY(){   return y;}

    private:
        int x;
        int y;
    };

    Canvas(MainWindow *p);

    void draw();
    void drawRectangle();
    void drawProvisionalRectangle();
    void drawCircle();
    void drawProvisionalCircle();
    void drawTrait();
    void drawProvisionalTrait();

    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

public slots:
    void newCanvas();
    void saveCanvas();
    void openCanvas();
    void returnCanvas();

private :

    int xMove;
    int yMove;
    int xPress;
    int yPress;
    int xRelease;
    int yRelease;

    int curPix;
    int xMax;
    int yMax;

    QPainter *painter;
    QLabel *label;
    MainWindow *parent;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QImage *image;
    QVector<QPixmap*> pixmapList;
    QPainterPath *path; //for simple drawing
};

#endif
