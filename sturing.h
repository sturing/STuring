#ifndef STURING_H
#define STURING_H

#include <QObject>
#include <QtWidgets>


using namespace std;

class STuring : public QObject
{
    Q_OBJECT

public: //(пришлось сделать public. Пишите, как сделать так, чтобы все работало с инкапсуляцией)
    int pointer;
    bool stopped;
    string nowState, line;
    vector<string>stackSrc;
    bool isRunning;
    double speed;
    QTime time;

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
    explicit STuring(QObject *parent = 0);

signals:
    void getData();
    void getSource();
    void Runable(bool);
    void updateLine(string);
    void updatePointer(int);

public slots:
    void run(QString src_, string line_);
};

#endif // STURING_H
