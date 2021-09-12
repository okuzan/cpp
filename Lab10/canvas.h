#ifndef CANVAS
#define CANVAS
#include <QtWidgets>
#include <mainwindow.h>

class Canvas : public QWidget
{
 Q_OBJECT

public :
    Canvas(MainWindow *p);

    void draw();
    void drawPoly(bool clean = false);
    void drawCircle(bool clean = false);
    void drawRectangle(bool clean = false);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);

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
    int xMax = 800;
    int yMax = 800;

    QImage *image;
    QLabel *label;
    QPainter *painter;
    MainWindow *parent;
    QPainterPath *path; //for simple drawing
    QGraphicsView *view;
    QGraphicsScene *scene;
    QVector<QPixmap*> pixmapList;
};

#endif
