#include "canvas.h"


Canvas::Canvas(MainWindow *p) : QWidget()
{
    parent = p;
    label = new QLabel(this);
    pixmapList.push_back(new QPixmap(xMax,yMax));
    curPix = pixmapList.size()-1;
    pixmapList[curPix]->fill();
    painter = new QPainter(pixmapList[curPix]);
    label->setPixmap(*pixmapList[curPix]);
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    //deciding what to draw depending on current mode
    if(parent->getDrawState())
    {
        xMove = event->pos().x();
        yMove = event->pos().y();
        draw();

    }
    if(parent->getRectangleState())
    {
        xMove = event->pos().x();
        yMove = event->pos().y();
        drawRectangle(true);
    }
    if(parent->getCircleState())
    {
        xMove = event->pos().x();
        yMove = event->pos().y();
        drawCircle(true);
    }
    if(parent->getPolyState())
    {
        xMove = event->pos().x();
        yMove = event->pos().y();
        drawPoly(true);
    }

}
void Canvas::mousePressEvent(QMouseEvent* event)
{
    if(parent->getRectangleState()||parent->getCircleState()||parent->getPolyState())
    {
        xPress = event->pos().x();
        yPress = event->pos().y();

    }
    if(parent->getDrawState())
    {
        pixmapList.push_back(new QPixmap(xMax,yMax));
        curPix = curPix+1;
        pixmapList[curPix]->operator =(*pixmapList[curPix-1]);
        painter->end();
        delete painter;
        painter = new QPainter(pixmapList[curPix]);
        xPress = event->pos().x(); //getDrawEnable xy todo
        yPress = event->pos().y();
        path = new QPainterPath(QPointF(xPress,yPress));
        path->moveTo(xPress,yPress);
    }

}
void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if(parent->getRectangleState())
    {
        xRelease = event->pos().x();
        yRelease = event->pos().y();
        drawRectangle();

    }
    if(parent->getCircleState())
    {
        xRelease = event->pos().x();
        yRelease = event->pos().y();
        drawCircle();

    }
    if(parent->getPolyState())
    {
        xRelease = event->pos().x();
        yRelease = event->pos().y();
        drawPoly();

    }
    if(parent->getDrawState()){   delete path;    }

}

void Canvas::draw()
{
    QPen pen;
    path->lineTo(xMove,yMove);
    pen.setColor(parent->getColor());
    pen.setWidth(parent->getPenWidth());
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(*path);

    label->setPixmap(*pixmapList[curPix]);
}

void Canvas::drawRectangle(bool clean)
{
    QPen pen;
    pen.setColor(parent->getColor());
    pen.setWidth(parent->getPenWidth());

    pixmapList.push_back(new QPixmap(xMax,yMax));
    curPix = curPix+1;
    pixmapList[curPix]->operator =(*pixmapList[curPix-1]);
    painter->end();
    delete painter;
    painter = new QPainter(pixmapList[curPix]);
    painter->setPen(pen);
    if(clean){
        painter->drawRect(xPress,yPress,xMove-xPress,yMove-yPress);
        label->setPixmap(*pixmapList[curPix]);
        pixmapList.remove(curPix);
        curPix = pixmapList.size()-1;
    }else{
        painter->drawRect(xPress,yPress,xRelease-xPress,yRelease-yPress);
        label->setPixmap(*pixmapList[curPix]);
    }
}


void Canvas::drawCircle(bool clean)
{
    QPen pen;
    pen.setColor(parent->getColor());
    pen.setWidth(parent->getPenWidth());

    pixmapList.push_back(new QPixmap(xMax,yMax));
    curPix = curPix+1;
    pixmapList[curPix]->operator =(*pixmapList[curPix-1]);
    painter->end();
    delete painter;
    painter = new QPainter(pixmapList[curPix]);
    painter->setPen(pen);

    if(clean){
        painter->drawEllipse(xPress,yPress,xMove-xPress,yMove-yPress);
        label->setPixmap(*pixmapList[curPix]);
        pixmapList.remove(curPix);
        curPix = pixmapList.size() - 1;

    } else{
        painter->drawEllipse(xPress,yPress,xRelease-xPress,yRelease-yPress);
        label->setPixmap(*pixmapList[curPix]);
    }
}

void Canvas::drawPoly(bool clean)
{
    QPen pen;
    pen.setColor(parent->getColor());
    pen.setWidth(parent->getPenWidth());

    pixmapList.push_back(new QPixmap(xMax,yMax));
    curPix = curPix+1;
    pixmapList[curPix]->operator =(*pixmapList[curPix-1]);
    painter->end();
    delete painter;
    painter = new QPainter(pixmapList[curPix]);
    painter->setPen(pen);
    if(clean){
        painter->drawLine(xPress,yPress,xMove,yMove);
        label->setPixmap(*pixmapList[curPix]);
        pixmapList.remove(curPix);
        curPix = pixmapList.size()-1;
    }else{
        painter->drawLine(xPress,yPress,xRelease,yRelease);
        label->setPixmap(*pixmapList[curPix]);
    }
}

void Canvas::saveCanvas()
{
    QString filename = QFileDialog::getSaveFileName(0, "Save image", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    pixmapList[curPix]->save(filename);
}

void Canvas::openCanvas()
{
    QString filename = QFileDialog::getOpenFileName(0, "Open image", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    painter->end();
    delete painter;
    pixmapList.remove(curPix);
    pixmapList.push_back(new QPixmap(filename));
    painter = new QPainter(pixmapList[curPix]);
    label->setPixmap(*pixmapList[curPix]);

}

void Canvas::newCanvas()
{
    painter->end();
    delete painter;
    pixmapList.erase(pixmapList.begin(),pixmapList.end());
    delete label;
    pixmapList.push_back(new QPixmap(xMax,yMax));
    curPix = pixmapList.size()-1;
    pixmapList[curPix]->fill();

    label = new QLabel(this);
    label->setPixmap(*pixmapList[curPix]);
    label->show();
    painter = new QPainter(pixmapList[curPix]);
}

void Canvas::returnCanvas()
{
    if(curPix == 0) return;
    pixmapList.remove(curPix);
    curPix = pixmapList.size() - 1;
    painter->end();
    delete painter;
    painter = new QPainter(pixmapList[curPix]);
    label->setPixmap(*pixmapList[curPix]);
}

void Canvas::paintEvent(QPaintEvent *event){  }
