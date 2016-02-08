#ifndef ERRORCONTROLLER_H
#define ERRORCONTROLLER_H

#include <QObject>
#include "sturing.h"

class ErrorController : public STuring
{
    Q_OBJECT
private:
    QString errorString;
    QVector<QString>stackSrc;
    void errorTest();
public:
    explicit ErrorController(QVector<QString>stackSrc_);

signals:

public slots:
};

#endif // ERRORCONTROLLER_H
