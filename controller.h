#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <vector>
#include <string>
#include <QtWidgets>
#include "sturing.h"
#include "errorcontroller.h"
#include "ui.h"
#include "settings.h"

using namespace std;

class Controller : public QObject
{
    Q_OBJECT
private:
    STuring* turing;
    QApplication* app;
    UI* ui;
    ErrorController* errControl;
    bool isTableParametres;
    bool maxSpdEnabled;

    //QSettings* settings;
    Settings* settings;
public:
    explicit Controller(QApplication *app_, QObject *parent = 0);
    ~Controller();

signals:

public slots:
    void kill();
    void loadRecentFile(QString path);
    void tmRun();
    void setRunable(bool);
    void changeSpeed(int n);
    void tmStop();
    void updateFromTable(int, int);
    void changeTableParameter(bool);
    void addHistory(QString state, QString line, int pointer, QString command);
    void tmLineChanged();
    void errorTest();
    void setHistoryEnabled(bool);
    void maxSpdValueChange(bool b);
    void saveSettings();
    void maxSpdWidgetsBlocker(bool b);
};

#endif // CONTROLLER_H
