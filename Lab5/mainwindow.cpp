#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QPaintEvent>
#include <QFileDialog>
#include <QPainter>
#include <QImage>
#define DEFAULT_SIZE 5

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mImage = new QImage(QApplication::desktop()->size(), QImage::Format_ARGB32_Premultiplied);
    mPainter = new QPainter(mImage);
    mEnabled = false;
    mColor = QColor(Qt::black);
    mSize = DEFAULT_SIZE;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mPainter;
    delete mImage;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.fillRect(mImage->rect(), Qt::white);
    painter.drawImage(0,0, *mImage);
    e->accept();
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    mEnabled = true;
    mBegin = e->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(!mEnabled){
        e->accept();
        return;
    }
    QPen pen(mColor);
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(mSize);
    mEnd = e->pos();
    mPainter->setPen(pen);
    mPainter->drawLine(mBegin, mEnd);
    mBegin = mEnd;
    update();
    e->accept();
}

// Check if the current image has been changed and then
// open a dialog to open a file
void MainWindow::open()
{
    // Check if changes have been made since last save
    // maybeSave() returns true if no changes have been made
    if (maybeSave()) {

        // Get the file to open from a dialog
        // tr sets the window title to Open File
        // QDir opens the current dirctory
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open File"), QDir::currentPath());

        // If we have a file name load the image and place
        // it in the scribbleArea
        if (!fileName.isEmpty())
            scribbleArea->openImage(fileName);
    }
}

bool MainWindow::maybeSave()
{
    // Check for changes since last save
    if (scribbleArea->isModified()) {
       QMessageBox::StandardButton ret;

       // Scribble is the title
       // Add text and the buttons
       ret = QMessageBox::warning(this, tr("Scribble"),
                          tr("The image has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard
                          | QMessageBox::Cancel);

       // If save button clicked call for file to be saved
        if (ret == QMessageBox::Save) {
            return saveFile("png");

        // If cancel do nothing
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

// Called when the user clicks Save As in the menu
void MainWindow::save()
{
    // A QAction represents the action of the user clicking
    QAction *action = qobject_cast<QAction *>(sender());

    // Stores the array of bytes of the users data
    QByteArray fileFormat = action->data().toByteArray();

    // Pass it to be saved
    saveFile(fileFormat);
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    // Define path, name and default file type
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    // Get selected file from dialog
    // Add the proper file formats and extensions
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));

    // If no file do nothing
    if (fileName.isEmpty()) {
        return false;
    } else {

        // Call for the file to be saved
        return scribbleArea->saveImage(fileName, fileFormat.constData());
    }
}


void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    mEnabled = false;
    e->accept();
}


void MainWindow::on_actionClose_triggered()
{
    close();
}

void MainWindow::on_actionPen_color_triggered()
{
    mColor = QColorDialog::getColor(Qt::black, this, "This is a color of a pen");
}

void MainWindow::on_actionPen_width_triggered()
{
    mSize = QInputDialog::getInt(this, "Width of the pen", "Now:", 5, 1);
}
