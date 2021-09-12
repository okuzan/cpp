#include "Canvas.h"
#include "WinSize.h"


Canvas::Canvas(MainWindow *p)
{
    parent = p;
    xMax = 500;
    yMax = 500;
    label = new QLabel(this);
    pixmapList.push_back(new QPixmap(xMax,yMax));
    curPix = pixmapList.size()-1;
    pixmapList[curPix]->fill();
    painter = new QPainter(pixmapList[curPix]);
    label->setPixmap(*pixmapList[curPix]);
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    //deciding what to draw depending on current
    if(parent->getDrawEnable())
    {
        xMove = event->pos().x();
        yMove = event->pos().y();
        draw();

    }
    if(parent->getRectangleEnable())
    {
        xMove = event->pos().x();
        yMove = event->pos().y();
        drawProvisionalRectangle();
    }
    if(parent->getCircleEnable())
    {
        xMove = event->pos().x();
        yMove = event->pos().y();
        drawProvisionalCircle();
    }
    if(parent->getTraitEnable())
    {
        xMove = event->pos().x();
        yMove = event->pos().y();
        drawProvisionalTrait();
    }

}
void Canvas::mousePressEvent(QMouseEvent* event)
{
    if(parent->getRectangleEnable()||parent->getCircleEnable()||parent->getTraitEnable())
    {
        xPress = event->pos().x();
        yPress = event->pos().y();

    }
    if(parent->getDrawEnable())
    {
        pixmapList.push_back(new QPixmap(xMax,yMax));
        curPix = curPix+1;
        pixmapList[curPix]->operator =(*pixmapList[curPix-1]);
        painter->end();
        delete painter;
        painter = new QPainter(pixmapList[curPix]);
        xPress = event->pos().x(); //getDrawEnable
        yPress = event->pos().y();
        path = new QPainterPath(QPointF(xPress,yPress));
        path->moveTo(xPress,yPress);
    }

}
void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if(parent->getRectangleEnable())
    {
        xRelease = event->pos().x();
        yRelease = event->pos().y();
        drawRectangle();

    }
    if(parent->getCircleEnable())
    {
        xRelease = event->pos().x();
        yRelease = event->pos().y();
        drawCircle();

    }
    if(parent->getTraitEnable())
    {
        xRelease = event->pos().x();
        yRelease = event->pos().y();
        drawTrait();

    }
    if(parent->getDrawEnable()){   delete path;    }

}

void Canvas::draw()
{
    QPen pen;

    path->lineTo(xMove,yMove);
    pen.setColor(parent->getColor());
    pen.setWidth(parent->getValueSlider());
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(*path);

    label->setPixmap(*pixmapList[curPix]);
}
void Canvas::drawRectangle()
{
    QPen pen;
    pen.setColor(parent->getColor());
    pen.setWidth(parent->getValueSlider());

    pixmapList.push_back(new QPixmap(xMax,yMax));
    curPix = curPix+1;
    pixmapList[curPix]->operator =(*pixmapList[curPix-1]);
    painter->end();
    delete painter;
    painter = new QPainter(pixmapList[curPix]);

    painter->setPen(pen);
    painter->drawRect(xPress,yPress,xRelease-xPress,yRelease-yPress);

    label->setPixmap(*pixmapList[curPix]);
}
void Canvas::drawProvisionalRectangle()
{
    QPen pen;
    pen.setColor(parent->getColor());
    pen.setWidth(parent->getValueSlider());

    pixmapList.push_back(new QPixmap(xMax,yMax));
    curPix = curPix+1;
    pixmapList[curPix]->operator =(*pixmapList[curPix-1]);
    painter->end();
    delete painter;
    painter = new QPainter(pixmapList[curPix]);

    painter->setPen(pen);
    painter->drawRect(xPress,yPress,xMove-xPress,yMove-yPress);
    label->setPixmap(*pixmapList[curPix]);
    pixmapList.remove(curPix);
    curPix = pixmapList.size()-1;
}

void Canvas::drawCircle()
{
    QPen pen;
    pen.setColor(parent->getColor());
    pen.setWidth(parent->getValueSlider());

    pixmapList.push_back(new QPixmap(xMax,yMax));
    curPix = curPix+1;
    pixmapList[curPix]->operator =(*pixmapList[curPix-1]);
    painter->end();
    delete painter;
    painter = new QPainter(pixmapList[curPix]);

    painter->setPen(pen);
    painter->drawEllipse(xPress,yPress,xRelease-xPress,yRelease-yPress);
    label->setPixmap(*pixmapList[curPix]);
}
void Canvas::drawProvisionalCircle()
{
    QPen pen;
    pen.setColor(parent->getColor());
    pen.setWidth(parent->getValueSlider());

    pixmapList.push_back(new QPixmap(xMax,yMax));
    curPix = curPix+1;
    pixmapList[curPix]->operator =(*pixmapList[curPix-1]);
    painter->end();
    delete painter;
    painter = new QPainter(pixmapList[curPix]);

    painter->setPen(pen);
    painter->drawEllipse(xPress,yPress,xMove-xPress,yMove-yPress);
    label->setPixmap(*pixmapList[curPix]);
    pixmapList.remove(curPix);
    curPix = pixmapList.size() - 1;
}

void Canvas::drawTrait()
{
    QPen pen;
    pen.setColor(parent->getColor());
    pen.setWidth(parent->getValueSlider());

    pixmapList.push_back(new QPixmap(xMax,yMax));
    curPix = curPix+1;
    pixmapList[curPix]->operator =(*pixmapList[curPix-1]);
    painter->end();
    delete painter;
    painter = new QPainter(pixmapList[curPix]);

    painter->setPen(pen);
    painter->drawLine(xPress,yPress,xRelease,yRelease);
    label->setPixmap(*pixmapList[curPix]);

}
void Canvas::drawProvisionalTrait()
{
    QPen pen;
    pen.setColor(parent->getColor());
    pen.setWidth(parent->getValueSlider());

    pixmapList.push_back(new QPixmap(xMax,yMax));
    curPix = curPix+1;
    pixmapList[curPix]->operator =(*pixmapList[curPix-1]);
    painter->end();
    delete painter;
    painter = new QPainter(pixmapList[curPix]);

    painter->setPen(pen);
    painter->drawLine(xPress,yPress,xMove,yMove);
    label->setPixmap(*pixmapList[curPix]);
    pixmapList.remove(curPix);
    curPix = pixmapList.size()-1;
}

void Canvas::saveCanvas()
{
    QString filename = QFileDialog::getSaveFileName(0, "Enregistrer l'image", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    pixmapList[curPix]->save(filename);
}

void Canvas::openCanvas()
{
    QString filename = QFileDialog::getOpenFileName(0,"Open image",QString(),"Images (*.png *.gif *.jpg *.jpeg)");
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
    xMax = WinSize::getLength();
    yMax = WinSize::getHeight();

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

void Canvas::paintEvent(QPaintEvent *event){    }
