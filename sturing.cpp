#include "sturing.h"

STuring::STuring(QObject *parent) : QObject(parent)
{

}

void STuring::run(QString src_, string line_) {
    emit Runable(true);

    stopped = false;

    stackSrc.clear();
    nowState = "00";

    QString tmp1 = src_;
    line = line_;
    pointer = line.size();
    line.push_back(' ');

    QStringList srcList = src_.split('\n');

    for(int i = 0; i < srcList.size(); ++i) {
        QString tmp3 = srcList.at(i);
        string cmd = tmp3.toStdString();
        cmd = uncomment(cmd);
        if(cmd.size() > 0) {
            stackSrc.push_back(cmd);
        }
    }

    errorsTest();

    if(!stopped) {
        go();
        //printResult();
        //qDebug() << "Success!" << endl;
    }

    emit Runable(false);

}

void STuring::errorsTest() {
    int s = 0;
    for(int i = 0; i < stackSrc.size(); ++i) {
        string state = getState(stackSrc[i]);
        string readLetter = getReadLetter(stackSrc[i]);
        string writeLetter = getWriteLetter(stackSrc[i]);
        string nextState = getNextState(stackSrc[i]);

        if(state.size() == 0 || readLetter.size() == 0 || readLetter.size() > 1 || writeLetter.size() == 0 || writeLetter.size() > 1 || nextState.size() == 0) {
            //Error::error(i);
            stopped = true;
            ++s;
        }
    }
}

void STuring::go() {

    emit Runable(true);

    for(int i = 0; i < stackSrc.size() && !stopped && isRunning; ++i) {
        if(testOfExecute(stackSrc[i])) {
            time.start();
            for(;time.elapsed() < speed;) {
                qApp->processEvents();
            }
            emit updateLine(line);

            executeCommand(stackSrc[i]);
            emit updatePointer(pointer);
            i = -1;
        }
        if(i == stackSrc.size() - 1) {
            //Error::undefinedTransition(nowState, line[pointer]);
            i = -1;
            stopped = true;
        }
    }

    emit Runable(false);
}

string STuring::get(string& cmd, int k) {
    int s = 0;
    string tmp;

    for(int i = 0; i < cmd.size(); ++i) {
        if(cmd[i] == ',') {++s; ++i;}
        if(s == k && i < cmd.size()) tmp.push_back(cmd[i]);
        if(s > k) return tmp;
    }

    return tmp;
}

string STuring::getState(string& cmd) {return get(cmd, 0);}
string STuring::getReadLetter(string& cmd) {return get(cmd, 1);}
string STuring::getWriteLetter(string& cmd) {return get(cmd, 2);}
string STuring::getNextState(string& cmd) {return get(cmd, 3);}

string STuring::uncomment(string& str) {
    string tmp;

    for(int i = 0; i < str.size(); ++i) {
        if(str[i] == '/' && i < str.at(i) - 1) {
            if(str[i+1] == '/') {
                return tmp;
            }

            else {
                tmp.push_back(str[i]);
                continue;
            }
        }
        tmp.push_back(str[i]);
    }
}

bool STuring::validationCommandTest(/*string& cmd*/) {
    return true;
}

bool STuring::testOfExecute(string& cmd) {
    string state = getState(cmd);
    string readLetter = getReadLetter(cmd);

    return state == nowState && readLetter[0] == line[pointer];
}

void STuring::executeCommand(string& cmd) {
    string writeLetter = getWriteLetter(cmd);
    string nextState = getNextState(cmd);

    if(writeLetter == ">") {moveRight();}
    else if(writeLetter == "<") {moveLeft();}
    else if(writeLetter == "#") {stopped = true;}
    else {changeLetter(writeLetter[0]);}

    nowState = nextState;

    QString tmp = QString::fromStdString(line);
    //qDebug() << QString::fromStdString(line);
    //tmLine->clear();
    //tmLine->insert(tmp);

}

void STuring::changeLetter(char let) {
    line[pointer] = let;
}

void STuring::moveRight() {
    pointer++;
    if(pointer >= line.size()) {

        line.push_back(' ');
    }
}

void STuring::moveLeft() {
    if(pointer > 0) {
        pointer--;
    }
}
