#include "unhappy.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Unhappy w;
    w.show();
    return a.exec();
}
