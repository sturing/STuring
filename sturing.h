#ifndef STURING_H
#define STURING_H

#include <vector>
#include <QDebug>
#include <string>
#include <QCoreApplication>
#include <QtWidgets>

using namespace std;

class Error {
public:
    static void error(int line) {
        //qDebug() << "Error in " << line + 1 << " line" << endl;
    }

    //static void undefinedTransition(string st, char lt) {
        //qDebug() << "Error! Undefined transition from state " << "[" << QString::fromStdString(st) << "]" << " and the letter " << "[" << lt << "]" << endl;
    //}
};

class STuring : public QObject
{
    Q_OBJECT
private:
    QWidget mainWindow;
    QLineEdit* tmLine;
    QPushButton* tmRunBtn;
    QPushButton* tmStopBtn;
    QTextEdit* tmSrc;
    QHBoxLayout* upLayout;
    QVBoxLayout* mainLayout;
    QTime time;
    QHBoxLayout* downLayout;
    QLabel* infoLbl;
    QLabel* speedLbl;
    QFont fontLine, fontSrc, fontLbl;
    QSlider* speedSlider;

    string s;
    int pointer;
    bool stopped;
    string nowState, line;
    vector<string>stackSrc;
    bool isRunning;
    double speed;

    void go();
    void executeCommand(string& cmd);
    void changeLetter(char let);
    void moveRight();
    void moveLeft();
    void stop();

    string getState(string& cmd);
    string getReadLetter(string& cmd);
    string getWriteLetter(string& cmd);
    string getNextState(string& cmd);
    string get(string& cmd, int k);
    string uncomment(string& str);

    bool testOfExecute(string& cmd);
    bool validationCommandTest(/*string& cmd*/);
    void errorsTest();
public:
    STuring();
    void printResult();

signals:
    void getData();
    void getSource();

public slots:
    void run();
    void stopButtonEnabled();
    void setSrcSize();
    void clearFontSrc();
    void changeSpeed();
};

#endif // STURING_H
