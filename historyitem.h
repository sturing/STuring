#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include <QString>

using namespace std;

class HistoryItem
{
private:
    QString state, line, command;
    int pointer;
public:
    HistoryItem(QString state_, QString line_, int pointer_);
    HistoryItem(QString state_, QString line_, int pointer, QString command_);
    HistoryItem();
    QString getState();
    QString getLine();
    QString getCommand();
    int getPointer();
};

#endif // HISTORYITEM_H
