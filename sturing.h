#ifndef STURING_H
#define STURING_H

#include <QObject>
#include <QtWidgets>


using namespace std;

class STuring : public QObject
{
    Q_OBJECT

public:
    int pointer;
    bool stopped;
    QString nowState, line;
    QVector<QString>stackSrc;
    bool isRunning;
    bool maxSpeed;
    double speed;
    QTime time;

    void go();
    void executeCommand(QString& cmd);
    void changeLetter(QChar let);
    void moveRight();
    void moveLeft();
    void stop();

    QString getState(QString& cmd);
    QString getReadLetter(QString& cmd);
    QString getWriteLetter(QString& cmd);
    QString getNextState(QString& cmd);
    QString get(QString& cmd, int k);
    QString uncomment(QString& str);

    bool testOfExecute(QString& cmd);
    bool validationCommandTest(/*string& cmd*/);
    void errorsTest();
public:
    explicit STuring(QObject *parent = 0);

signals:
    void getData();
    void getSource();
    void Runable(bool);
    void updateLine(QString);
    void updatePointer(int);
    void getSettings();
    void commandExecuted(QString state, QString line, int pointer, QString command);

public slots:
    void run(QString src_);
    void maxSpeedEnable(bool);
    void setStandardSettings(QString line_);
    void setCustomSettings(QString state_, QString line_, int pointer_);
};

#endif // STURING_H
