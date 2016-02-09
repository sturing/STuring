#include "history.h"

History::History()
{
    setColumnCount(2);
    setMinimumWidth(400);
    setMaximumWidth(400);
    colWidth = 180;
    QStringList header;
    header << "История выполнения" << "Команда";
    setHorizontalHeaderLabels(header);

    for(int i = 0; i < colorCount(); ++i) {setColumnWidth(i, colWidth);}
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setEditTriggers(QTableWidget::NoEditTriggers);
    numberHistoryItem;

    QObject::connect(this, SIGNAL(cellPressed(int,int)), this, SLOT(changeNumberHistoryItem(int,int)));
}

bool History::isEmpty() {
    return (historyItem.size() == 0);
}

int History::getNumberHistoryItem() {
    return numberHistoryItem;
}

void History::changeNumberHistoryItem(int r, int c) {
    numberHistoryItem = r;
}

void History::addItem(QString state, QString line, int pointer) {
    if(!isFirstHave()) {
        historyItem.push_back(HistoryItem(state, line, pointer));
    }

    updateTable();
}

bool History::isFirstHave() {
    for(int i = 0; i < historyItem.size(); ++i) {
        if(!historyItem[i].getCommand().isEmpty()) {return 1;}
    }

    return 0;
}

void History::addItem(QString state, QString line, int pointer, QString command) {
    //if(!(command.isEmpty() && !isFirstHave)) {
        historyItem.push_back(HistoryItem(state, line, pointer, command));
   // }
    updateTable();
}

void History::clearAllHistory() {
    historyItem.clear();
    numberHistoryItem = 0;
    updateTable();
}

void History::clearPart() {
    historyItem.remove(numberHistoryItem + 1, historyItem.size() - numberHistoryItem - 1);
    updateTable();
}

void History::updateTable() {
    setRowCount(historyItem.size());

    for(int i = 0; i < rowCount(); ++i) {
        setItem(i, 0, new QTableWidgetItem(historyItem[i].getLine()));
        setItem(i, 1, new QTableWidgetItem(historyItem[i].getCommand()));
    }

    this->scrollToBottom();
}

QString History::getState(int n) {return historyItem[n].getState();}
QString History::getLine(int n) {return historyItem[n].getLine();}
int History::getPointer(int n) {return historyItem[n].getPointer();}
