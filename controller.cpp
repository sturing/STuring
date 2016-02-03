#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent) {
    ui = new UI();
    turing = new STuring();
    changeSpeed(ui->speedSlider->value());

    QObject::connect(ui->tmRunBtn, SIGNAL(clicked()), this, SLOT(tmRun()));
    QObject::connect(turing, SIGNAL(Runable(bool)), this, SLOT(setRunable(bool)));
    QObject::connect(ui->speedSlider, SIGNAL(valueChanged(int)), this, SLOT(changeSpeed(int)));
    QObject::connect(ui->tmStopBtn, SIGNAL(clicked()), this, SLOT(tmStop()));
    QObject::connect(turing, SIGNAL(updateLine(string)), ui, SLOT(setLine(string)));
    QObject::connect(turing, SIGNAL(updatePointer(int)), ui, SLOT(setPointer(int)));
}

void Controller::tmRun() {
    QString src = ui->tmSrc->document()->toPlainText();
    string line(ui->tmLine->text().toStdString());
    turing->run(src, line);
}

void Controller::tmStop() {
    setRunable(false);
}

void Controller::setRunable(bool r) {
    turing->isRunning = r;
    //turing->stopped = !r;

    ui->tmRunBtn->setEnabled(!r);
    ui->tmStopBtn->setEnabled(r);
}

void Controller::changeSpeed(int n) {
    int value = 110 - n;
    turing->speed = value;
}
