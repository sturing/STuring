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

    static void undefined_transition(string st, char lt) {
        //qDebug() << "Error! Undefined transition from state " << "[" << QString::fromStdString(st) << "]" << " and the letter " << "[" << lt << "]" << endl;
    }
};

class STuring : public QObject
{
    Q_OBJECT
private:
    QWidget mainwindow;
    QLineEdit* TMLine;
    QPushButton* TMRunBtn;
    QPushButton* TMStop;
    QTextEdit* TMSrc;
    QHBoxLayout* up;
    QVBoxLayout* main_layout;
    QTime time;
    QHBoxLayout* down;
    QLabel* info_lbl;
    QLabel* speedLbl;
    QFont fontline, fontsrc, fontlbl;
    QSlider* speedSlider;

    string s;
    int pointer;
    bool stopped;
    string now_state, line;
    vector<string>stack_src;
    bool isRunning;
    double speed;

    void go();
    void execute_command(string& cmd);
    void change_letter(char let);
    void move_right();
    void move_left();
    void stop();

    string get_state(string& cmd);
    string get_read_letter(string& cmd);
    string get_write_letter(string& cmd);
    string get_next_state(string& cmd);
    string get(string& cmd, int k);
    string uncomment(string& str);

    bool test_of_execute(string& cmd);
    bool validation_command_test(string& cmd);
    bool errors_test();
public:
    STuring();
    void print_result();

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
