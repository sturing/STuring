#include "sturing.h"

STuring::STuring() {
    tmLine = new QLineEdit();
    tmRunBtn = new QPushButton("Пуск");
    tmStopBtn = new QPushButton("Стоп");
    tmSrc = new QTextEdit();
    infoLbl = new QLabel("");
    speedSlider = new QSlider(Qt::Horizontal);
    speedLbl = new QLabel("Скорость: ");

    upLayout = new QHBoxLayout();
    mainLayout = new QVBoxLayout();

    downLayout = new QHBoxLayout();
    upLayout->setSpacing(3);
    upLayout->addWidget(tmLine);
    upLayout->addWidget(tmRunBtn);
    upLayout->addWidget(tmStopBtn);

    downLayout->addWidget(infoLbl);
    downLayout->addWidget(speedLbl, 0, Qt::AlignRight);
    downLayout->addWidget(speedSlider);

    speedSlider->setValue(50);
    speedSlider->setMaximumWidth(250);
    speedSlider->setMinimumWidth(60);

    fontLine.setPointSize(14);
    fontLine.setFamily("Monospace");
    fontSrc.setFamily("Monospace");
    fontLine.setStyleHint(QFont::TypeWriter);
    fontSrc.setStyleHint(QFont::TypeWriter);
    fontSrc.setPointSize(12);
    fontLbl.setFamily("Monospace");
    fontLbl.setStyleHint(QFont::TypeWriter);
    fontLbl.setPointSize(12);
    tmLine->setFont(fontLine);
    tmSrc->setFont(fontSrc);
    infoLbl->setFont(fontLbl);

    mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(3);
    mainLayout->setMargin(3);
    mainLayout->addLayout(upLayout);
    mainLayout->addWidget(tmSrc);
    mainLayout->addLayout(downLayout);

    downLayout->setMargin(3);
    downLayout->setSpacing(5);
    changeSpeed();
    speedLbl->setFont(fontLbl);

    tmStopBtn->setEnabled(false);
    setSrcSize();

    QIcon windowIcon;
    windowIcon.addFile(":/ico");

    mainWindow.setLayout(mainLayout);
    mainWindow.setWindowTitle("STuring - v2.3.1");
    mainWindow.setWindowIcon(windowIcon);


    mainWindow.show();

    QObject::connect(this->tmRunBtn, SIGNAL(clicked()), this, SLOT(run()));
    QObject::connect(this->tmStopBtn, SIGNAL(clicked()), this, SLOT(stopButtonEnabled()));
    QObject::connect(this->tmSrc, SIGNAL(textChanged()), this, SLOT(setSrcSize()));
    QObject::connect(this->tmSrc, SIGNAL(textChanged()), this, SLOT(clearFontSrc()));
    QObject::connect(this->speedSlider, SIGNAL(valueChanged(int)), this, SLOT(changeSpeed()));
}

void STuring::changeSpeed() {
    int spd = 100 - speedSlider->value() + 10;
    speed = spd;
}

void STuring::run() {
    tmStopBtn->setEnabled(true);
    tmRunBtn->setEnabled(false);
    isRunning = true;
    stopped = false;
    stackSrc.clear();
    nowState = "00";

    QString tmp1 = tmLine->text();
    line = tmp1.toStdString();

    pointer = line.size();
    line.push_back(' ');

    QString tmp2 = tmSrc->toPlainText();
    QStringList srcList = tmp2.split('\n');

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
        printResult();
        //qDebug() << "Success!" << endl;
    }

    isRunning = false;
    tmStopBtn->setEnabled(false);
    tmRunBtn->setEnabled(true);

}

void STuring::clearFontSrc() {
    tmSrc->font().cleanup();
    tmSrc->setFont(fontSrc);
}

void STuring::errorsTest() {
    int s = 0;
    for(int i = 0; i < stackSrc.size(); ++i) {
        string state = getState(stackSrc[i]);
        string readLetter = getReadLetter(stackSrc[i]);
        string writeLetter = getWriteLetter(stackSrc[i]);
        string nextState = getNextState(stackSrc[i]);

        if(state.size() == 0 || readLetter.size() == 0 || readLetter.size() > 1 || writeLetter.size() == 0 || writeLetter.size() > 1 || nextState.size() == 0) {
            Error::error(i);
            stopped = true;
            ++s;
        }
    }
}

void STuring::stopButtonEnabled() {
    isRunning = false;

    tmStopBtn->setEnabled(false);
    tmRunBtn->setEnabled(true);
}

void STuring::go() {
    tmLine->setReadOnly(true);
    tmRunBtn->setDisabled(true);
    for(int i = 0; i < stackSrc.size() && !stopped && isRunning; ++i) {
        if(testOfExecute(stackSrc[i])) {
            time.start();
            for(;time.elapsed() < speed;) {
                qApp->processEvents();
            }
            tmLine->setText(QString::fromStdString(line));
            executeCommand(stackSrc[i]);
            tmLine->setSelection(pointer, 1);
            i = -1;
        }
        if(i == stackSrc.size() - 1) {
            //Error::undefinedTransition(nowState, line[pointer]);
            i = -1;
            stopped = true;
        }
    }
    tmLine->setReadOnly(false);
    tmRunBtn->setDisabled(false);
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

void STuring::setSrcSize() {
    QString str = "Символы: ";

    int numChars = tmSrc->document()->characterCount() - 1;
    QString numCharsS = QString::number(numChars);

    str += numCharsS;
    str += "; Строки: ";

    int numStrings = tmSrc->document()->lineCount();
    QString numStringsS = QString::number(numStrings);

    str += numStringsS;
    str += ".";

    infoLbl->setText(str);
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
    tmLine->clear();
    tmLine->insert(tmp);

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

void STuring::printResult() {
    //qDebug() << QString::fromStdString(line) << endl;

    for(int i = 0; i < pointer; ++i) {
        //qDebug() << " ";
    }

    //qDebug() << "^" << endl << endl;
}
