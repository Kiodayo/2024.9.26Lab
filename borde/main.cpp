#include "borde.h"
#include<iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    borde w;
    w.show();

    return a.exec();
}
