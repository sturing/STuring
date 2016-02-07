#include "controller.h"

Controller::Controller(QApplication *app_, QObject *parent) : QObject(parent) {
    app = app_;
    ui = new UI(app_);
    turing = new STuring();
    changeSpeed(ui->speedSlider->value());
    isTableParametres = false;

    QObject::connect(ui->tmRunBtn, SIGNAL(clicked()), this, SLOT(tmRun()));
    QObject::connect(turing, SIGNAL(Runable(bool)), this, SLOT(setRunable(bool)));
    QObject::connect(ui->speedSlider, SIGNAL(valueChanged(int)), this, SLOT(changeSpeed(int)));
    QObject::connect(ui->tmStopBtn, SIGNAL(clicked()), this, SLOT(tmStop()));
    QObject::connect(turing, SIGNAL(updateLine(QString)), ui, SLOT(setLine(QString)));
    QObject::connect(turing, SIGNAL(updatePointer(int)), ui, SLOT(setPointer(int)));
    QObject::connect(ui->maxSpeedCkb, SIGNAL(toggled(bool)), turing, SLOT(maxSpeedEnable(bool)));
    QObject::connect(ui->historyCkb, SIGNAL(toggled(bool)), this, SLOT(changeTableParameter(bool)));
    QObject::connect(turing, SIGNAL(commandExecuted(QString,QString,int, QString)), this, SLOT(addHistory(QString, QString, int, QString)));
    QObject::connect(ui->history, SIGNAL(cellClicked(int,int)), this, SLOT(updateFromTable(int, int)));
    //QObject::connect(ui->tmSrc, SIGNAL(textChanged()), history, SLOT(clearAllHistory()));
    //QObject::connect(ui->tmLine, SIGNAL(textChanged(QString)), history, SLOT(clearAllHistory()));
    QObject::connect(ui->tmSrc, SIGNAL(textChanged()), ui->history, SLOT(clearAllHistory()));
    QObject::connect(ui->tmLine, SIGNAL(textChanged(QString)), this, SLOT(tmLineChanged()));
}

void Controller::tmLineChanged() {
    if(!turing->isRunning && ui->tmLine->hasFocus()/*!ui->history->isActiveWindow()*/) {
        ui->history->clearAllHistory();
    }
}

void Controller::updateFromTable(int r, int c) {
    ui->tmLine->setText(ui->history->getLine(r));
    ui->tmLine->setSelection(ui->history->getPointer(r), 1);
}

void Controller::addHistory(QString state, QString line, int pointer, QString command) {
    ui->history->addItem(state, line, pointer, command);
}

void Controller::changeTableParameter(bool b) {
    isTableParametres = b;
    ui->history->setEnabled(b);
}

void Controller::tmRun() {
    QString src = ui->tmSrc->document()->toPlainText();

    if(!isTableParametres) {
        ui->history->clearAllHistory();
    }

    if(isTableParametres && !ui->history->isEmpty()) {
        ui->history->clearPart();
        turing->setCustomSettings(ui->history->getState(ui->history->getNumberHistoryItem()),
                                  ui->history->getLine(ui->history->getNumberHistoryItem()),
                                  ui->history->getPointer(ui->history->getNumberHistoryItem())
        );
    }
    else {
        turing->setStandardSettings(ui->tmLine->text());
    }
    turing->run(src);
}

void Controller::tmStop() {
    setRunable(false);
}

void Controller::setRunable(bool r) {
    turing->isRunning = r;

    ui->tmRunBtn->setEnabled(!r);
    ui->tmStopBtn->setEnabled(r);
    ui->clearHistoryBtn->setEnabled(!r);

    ui->tmSrc->setReadOnly(r);
    ui->tmLine->setReadOnly(r);
}

void Controller::changeSpeed(int n) {
    int value = 110 - n;
    turing->speed = value;
}
