#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <QObject>

class Localization : public QObject
{
    Q_OBJECT
private:
    int local;
    const int RU = 0;
    const int EN = 1;
public:
    explicit Localization(QObject *parent = 0);

signals:

public slots:
    void setLocale(QString loc);

    QString getTmRunBtnLocale();
    QString getTmStopBtnLocale();
    QString getClearHistoryBtnLocale();
    QString maxSpeedCkb();
};

#endif // LOCALIZATION_H
