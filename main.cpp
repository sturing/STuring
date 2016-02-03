#include <QApplication>
#include "controller.h"

//#include "sturing.h"
//#include "ui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller* mainController;
    mainController = new Controller();

    return a.exec();
}
