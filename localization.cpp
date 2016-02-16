#include "localization.h"

Localization::Localization(QObject *parent) : QObject(parent)
{
    local = 0;
}

void Localization::setLocale(QString loc) {
    if(loc == "ru") { local = RU;}
    else if(loc == "en") {local = EN;}
    else {local = RU;}
}

QString Localization::getTmRunBtnLocale() {
    if(local == RU) {
        return "Запустить";
    } else if(local == EN) {
        return "Run";
    }

}

QString Localization::getTmStopBtnLocale() {
    if(local == RU) {
        return "Остановить";
    } else if(local == EN) {
        return "Stop";
    }

}
QString Localization::getClearHistoryBtnLocale() {
    if(local == RU) {
        return "Очистить историю";
    } else if(local == EN) {
        return "Clear history";
    }
}

QString Localization::maxSpeedCkb() {
    if(local == RU) {
        return "Максимальная скорость";
    } else if(local == EN) {
        return "Max speed";
    }
}
