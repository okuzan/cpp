#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QPainter;
class QImage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent (QPaintEvent *e) override;
    void mousePressEvent (QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
private slots:
    void on_actionClose_triggered();

    void on_actionPen_color_triggered();

    void on_actionPen_width_triggered();

    void open();
    void save();

private:
    Ui::MainWindow *ui;
    QPainter *mPainter;
    QImage *mImage;
    QPoint mBegin;
    QPoint mEnd;
    QColor mColor;
    bool mEnabled;
    int mSize;
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

};
#endif // MAINWINDOW_H
