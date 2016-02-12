#include "controller.h"

Controller::Controller(QApplication *app_, QObject *parent) : QObject(parent) {
    app = app_;
    ui = new UI(app_);
    turing = new STuring();
    changeSpeed(ui->speedSlider->value());
    isTableParametres = false;
    errControl = new ErrorController();
    maxSpdEnabled = 0;

    settings = new QSettings("settings.conf", QSettings::IniFormat);

    QString recentPath = settings->value("pathFile/recentFile", "").toString();


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
    QObject::connect(turing, SIGNAL(testErrors()), this, SLOT(errorTest()));
    //QObject::connect(errControl, SIGNAL(errorHave(QString)), this, SLOT(printErrors(QString)));
    QObject::connect(ui->maxSpeedCkb, SIGNAL(toggled(bool)), this, SLOT(setHistoryEnabled(bool)));
    QObject::connect(ui->maxSpeedCkb, SIGNAL(toggled(bool)), this, SLOT(maxSpdValueChange(bool)));
    QObject::connect(app, SIGNAL(aboutToQuit()), this, SLOT(saveSettings()));

    loadRecentFile(recentPath);
}

void Controller::loadRecentFile(QString path) {
    ui->fControl->openFromPath(path);
}

void Controller::saveSettings() {
    settings->setValue("pathFile/recentFile", ui->fControl->getPathString());
    settings->sync();
}

void Controller::maxSpdValueChange(bool b) {
    maxSpdEnabled = b;

    if(b) {
        ui->history->clearAllHistory();
    }
}

void Controller::setHistoryEnabled(bool b) {
    ui->history->setHidden(b);
    ui->historyCkb->setHidden(b);
    ui->historyLbl->setHidden(b);
    ui->clearHistoryBtn->setHidden(b);
}

void Controller::errorTest() {
    errControl = new ErrorController(ui->tmSrc->toPlainText(), ui->tmLine->text());
    QString errOut = errControl->errorTest();
    turing->errorsHave = errControl->getErrorTest();

    ui->errorConsole->setText(errOut);
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
    if(!maxSpdEnabled) {
        if(command.isEmpty()) {
                if(ui->history->getNumberHistoryItem() == 0) {
                    ui->history->addItem(state, line, pointer, command);
                }
        }
        else {
            ui->history->addItem(state, line, pointer, command);
        }
    }
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
    ui->maxSpeedCkb->setDisabled(r);
}

void Controller::changeSpeed(int n) {
    int value = 110 - n;
    turing->speed = value;
}
