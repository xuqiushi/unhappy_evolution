#include "Unhappy.h"
//#pragma push_macro("slots")
//#undef slots
//#include "Python.h"
//#pragma pop_macro("slots")

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Unhappy w;
    w.show();
    return QApplication::exec();
}
