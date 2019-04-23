#include "fenserveur.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FenServeur w;
    w.show();

    return a.exec();
}
