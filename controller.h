#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <vector>
#include <string>
#include <QtWidgets>
#include "sturing.h"
#include "ui.h"
#include <utility>

using namespace std;

class Controller : public QObject
{
    Q_OBJECT
private:
    STuring* turing;
    UI* ui;
public:
    explicit Controller(QObject *parent = 0);
    //Controller(STuring turing_, UI ui_);

signals:

public slots:
    void tmRun();
    void setRunable(bool);
    void changeSpeed(int n);
    void tmStop();
};

#endif // CONTROLLER_H
