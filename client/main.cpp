#include "fenclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FenClient w;
    w.show();

    return a.exec();
}
