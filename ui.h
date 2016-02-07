#ifndef UI_H
#define UI_H

#include <QObject>
#include <QtWidgets>
#include <string>
#include "codeeditor.h"
#include "history.h"

using namespace std;

class UI : public QObject
{
    Q_OBJECT
private:
    void createActions();

public:
    QString programmNameString;
    QIcon icon;
    QWidget mainWindow;
    QLineEdit* tmLine;
    QPushButton* tmRunBtn;
    QPushButton* tmStopBtn;
    QPushButton* clearHistoryBtn;
    CodeEditor* tmSrc;
    QHBoxLayout* upLayout;
    QVBoxLayout* turingLayout;
    QTime time;
    QHBoxLayout* downLayout;
    QHBoxLayout* menuLayout;
    QHBoxLayout* maxSpdLayout;
    QLabel* infoLbl;
    QLabel* speedLbl;
    QFont fontLine, fontSrc, fontLbl;
    QSlider* speedSlider;

    QLabel* maxSpeedLbl;
    QCheckBox* maxSpeedCkb;

    QHBoxLayout* historyCkbLayout;
    QLabel* historyLbl;
    QCheckBox* historyCkb;

    QAction* saveAction;
    QAction* openAction;

    QMenuBar* menuBar;
    QMenu* fileMenu;
    QMenu* about;

    QApplication* app;

    QWidget aboutDialog;
    QPixmap logo;
    QLabel* logoLbl;
    QLabel* programName;
    QLabel* aboutLbl;
    QVBoxLayout* dialogMainLayout;

    QHBoxLayout* appLayout;
    QVBoxLayout* historyLayout;
    QVBoxLayout* mainVerticalSeparator;
    History* history;
    int dialogW = 300, dialogH = 200;
public:
    explicit UI(QApplication *app_, QObject *parent = 0);
signals:

public slots:
    void setSrcSize();
    void setPointer(int);
    void setLine(QString);
    void dialogShow();
    void createTableHistory();
};

#endif // UI_H
