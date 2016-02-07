#include <QApplication>
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller* mainController;
    mainController = new Controller(&a);

    return a.exec();
}
