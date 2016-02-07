#include "historyitem.h"

HistoryItem::HistoryItem(QString state_, QString line_, int pointer_) : state(state_), line(line_), pointer(pointer_) {}
HistoryItem::HistoryItem(QString state_, QString line_, int pointer_, QString command_) : state(state_), line(line_), pointer(pointer_), command(command_) {}
HistoryItem::HistoryItem() : state("00"), line(""), pointer(0), command("") {}

QString HistoryItem::getState() {return state;}
QString HistoryItem::getLine() {return line;}
QString HistoryItem::getCommand() {return command;}
int HistoryItem::getPointer() {return pointer;}
