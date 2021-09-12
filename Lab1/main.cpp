#include <QCoreApplication>
#include <iostream>
#include "Phonebook.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Phonebook pb;
    pb.fill_with_data();
    pb.start();
    return a.exec();
}
