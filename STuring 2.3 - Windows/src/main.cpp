#include <QApplication>
#include <QtWidgets>
#include "sturing.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    STuring* mashine = new STuring();

    return a.exec();
}
