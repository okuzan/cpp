#ifndef HEADER_WINSIZE
#define HEADER_WINSIZE

#include "Canvas.h"
#include <QtWidgets>

class WinSize : public QWidget
{
    Q_OBJECT
public:
    WinSize(Canvas *canvas);
    static int getLength();
    static int getHeight();



public slots:
    void createClick();
    void getLengthLine(QString lLine);
    void getHeightLine(QString hLine);

private:
    static int length;
    static int height;
    QLineEdit *lengthLine;
    QLineEdit *heightLine;
    QPushButton *create;

};

#endif
