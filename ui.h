#ifndef UI_H
#define UI_H

#include <QObject>
#include <QtWidgets>
#include <string>
#include <QDebug>
#include "codeeditor.h"
#include "history.h"
#include "filecontroller.h"

using namespace std;

class UI : public QObject
{
    Q_OBJECT
private:
    void createActions();

public:
    FileController* fControl;
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
    QTextEdit* errorConsole;
    QLabel* errorLbl;

    QHBoxLayout* appLayout;
    QVBoxLayout* rightLayout;
    QVBoxLayout* mainVerticalSeparator;
    History* history;
    QString allWindowTitle;
    int dialogW = 300, dialogH = 200;
    bool fileSaved;

    //QMessageBox* saveMsg;

public:
    explicit UI(QApplication *app_, QObject *parent = 0);
    ~UI();
signals:
    void saveSettings();

public slots:
    void setSrcSize();
    void setPointer(int);
    void setLine(QString);
    void dialogShow();
    void createTableHistory();
    void openFile(QString, QString);
    void saveFile();
    void fileNameWindow(QString str);
    void createNewFile();
    void addUnSaved();
    void addSaved();
};

#endif // UI_H
