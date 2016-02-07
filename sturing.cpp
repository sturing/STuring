#include "sturing.h"

STuring::STuring(QObject *parent) : QObject(parent)
{

}

void STuring::run(QString src_) {
    emit Runable(true);
    stopped = false;
    stackSrc.clear();

    QString tmp1 = src_;
    QStringList srcList = src_.split('\n');

    for(int i = 0; i < srcList.size(); ++i) {
        QString cmd = srcList.at(i);
        cmd = uncomment(cmd);
        if(cmd.size() > 0) {
            stackSrc.push_back(cmd);
        }
    }

    errorsTest();

    if(!stopped) {
        go();
    }

    emit Runable(false);

}

void STuring::setStandardSettings(QString line_) {
    nowState = "00";
    line = line_;
    pointer = line.size();
    line.push_back(' ');
}

void STuring::setCustomSettings(QString state_, QString line_, int pointer_) {
    nowState = state_;
    line = line_;
    pointer = pointer_;
}

void STuring::maxSpeedEnable(bool b) {
    maxSpeed = b;
}

void STuring::errorsTest() {
    int s = 0;
    for(int i = 0; i < stackSrc.size(); ++i) {
        QString state = getState(stackSrc[i]);
        QString readLetter = getReadLetter(stackSrc[i]);
        QString writeLetter = getWriteLetter(stackSrc[i]);
        QString nextState = getNextState(stackSrc[i]);

        if(state.size() == 0 || readLetter.size() == 0 || readLetter.size() > 1 || writeLetter.size() == 0 || writeLetter.size() > 1 || nextState.size() == 0) {
            //Error::error(i);
            stopped = true;
            ++s;
        }
    }
}

void STuring::go() {

    emit Runable(true);
    emit commandExecuted(nowState, line, pointer, "");
    for(int i = 0; i < stackSrc.size() && !stopped && isRunning; ++i) {
        if(testOfExecute(stackSrc[i])) {
            if(!maxSpeed) {
                time.start();
                for(;time.elapsed() < speed;) {
                    qApp->processEvents();
                }
            }
            else {
                time.start();
                for(;time.elapsed() < 0.00001;) {
                    qApp->processEvents();
                }
            }

            executeCommand(stackSrc[i]);
            emit updateLine(line);
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

QString STuring::get(QString& cmd, int k) {
    int s = 0;
    QString tmp;

    for(int i = 0; i < cmd.size(); ++i) {
        if(cmd[i] == ',') {++s; ++i;}
        if(s == k && i < cmd.size()) tmp.push_back(cmd[i]);
        if(s > k) return tmp;
    }

    return tmp;
}

QString STuring::getState(QString& cmd) {return get(cmd, 0);}
QString STuring::getReadLetter(QString& cmd) {return get(cmd, 1);}
QString STuring::getWriteLetter(QString& cmd) {return get(cmd, 2);}
QString STuring::getNextState(QString& cmd) {return get(cmd, 3);}

QString STuring::uncomment(QString& str) {
    QString tmp;

    for(int i = 0; i < str.size(); ++i) {
        if(str[i] == '/' && i < str.at(i).unicode() - 1) {
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

bool STuring::testOfExecute(QString &cmd) {
    QString state = getState(cmd);
    QString readLetter = getReadLetter(cmd);

    return state == nowState && readLetter[0] == line[pointer];
}

void STuring::executeCommand(QString& cmd) {
    QString writeLetter = getWriteLetter(cmd);
    QString nextState = getNextState(cmd);

    if(writeLetter == ">") {moveRight();}
    else if(writeLetter == "<") {moveLeft();}
    else if(writeLetter == "#") {stopped = true;}
    else {changeLetter(writeLetter[0]);}

    nowState = nextState;

    emit commandExecuted(nowState, line, pointer, cmd);

}

void STuring::changeLetter(QChar let) {
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
