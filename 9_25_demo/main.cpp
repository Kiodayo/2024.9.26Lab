#include "mqtt.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mqtt w;
    w.show();
    return a.exec();
}
