#ifndef ERRORCONTROLLER_H
#define ERRORCONTROLLER_H

#include <QObject>
#include <QDebug>
#include "sturing.h"

class ErrorController : public STuring
{
    Q_OBJECT
private:
    int getExtraParametres(QString s);
    QString errorString;
    QString src;
    QVector<QString>cmd;
    QString line;
    bool errorsHave;
    QString errorTest1();
    QString errorTest2();
    QString errorTest3();
    QString errorTest4();
    QString errorTest5();
    QString errorTest6();
    QString errorTest7();
public:
    explicit ErrorController(QString src_, QString line_);
    ErrorController();
    QString errorTest();
    bool getErrorTest();

signals:

public slots:
};

#endif // ERRORCONTROLLER_H
