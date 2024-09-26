#include "my_first.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    my_first w;
    w.show();
    return a.exec();
}
