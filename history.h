#ifndef HISTORY_H
#define HISTORY_H
#include <QtWidgets>
#include "historyitem.h"

class History : public QTableWidget
{
    Q_OBJECT
private:
    QVector<HistoryItem>historyItem;
    int colWidth;
    int numberHistoryItem;
public:
    History();
    void addItem(QString state, QString line, int pointer);
    void addItem(QString state, QString line, int pointer, QString command);
    void updateTable();
    void clearPart();
    QString getState(int n);
    QString getLine(int n);
    int getPointer(int n);
    int getNumberHistoryItem();
    bool isEmpty();
public slots:
    void changeNumberHistoryItem(int r, int c);
    void clearAllHistory();
};

#endif // HISTORY_H
