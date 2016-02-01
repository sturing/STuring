#include "sturing.h"

STuring::STuring() {
    TMLine = new QLineEdit();
    TMRunBtn = new QPushButton("Запустить");
    TMStop = new QPushButton("Остановить");
    TMSrc = new QTextEdit();
    info_lbl = new QLabel("");
    speedSlider = new QSlider(Qt::Horizontal);
    speedLbl = new QLabel("Скорость: ");

    up = new QHBoxLayout();
    down = new QHBoxLayout();
    main_layout = new QVBoxLayout();
    up->setSpacing(3);
    up->addWidget(TMLine);
    up->addWidget(TMRunBtn);
    up->addWidget(TMStop);
    down->addWidget(info_lbl);
    down->addWidget(speedLbl, 0, Qt::AlignRight);
    down->addWidget(speedSlider);
    speedSlider->setValue(50);
    speedSlider->setMaximumWidth(250);
    speedSlider->setMinimumWidth(60);

    fontline.setPointSize(14);
    fontline.setFamily("Monospace");
    fontsrc.setFamily("Monospace");
    fontline.setStyleHint(QFont::TypeWriter);
    fontsrc.setStyleHint(QFont::TypeWriter);
    fontsrc.setPointSize(12);
    fontlbl.setFamily("Monospace");
    fontlbl.setStyleHint(QFont::TypeWriter);
    fontlbl.setPointSize(12);
    TMLine->setFont(fontline);
    TMSrc->setFont(fontsrc);
    info_lbl->setFont(fontlbl);

    main_layout = new QVBoxLayout();
    main_layout->setSpacing(3);
    main_layout->setMargin(3);
    main_layout->addLayout(up);
    main_layout->addWidget(TMSrc);
    main_layout->addLayout(down);

    down->setMargin(3);
    down->setSpacing(5);
    //speed = 50;
    changeSpeed();
    speedLbl->setFont(fontlbl);

    TMStop->setEnabled(false);
    setSrcSize();

    QIcon window_icon;
    window_icon.addFile(":/ico");

    mainwindow.setLayout(main_layout);
    mainwindow.setWindowTitle("STuring - v2.3");
    mainwindow.setWindowIcon(window_icon);


    mainwindow.show();

    QObject::connect(this->TMRunBtn, SIGNAL(clicked()), this, SLOT(run()));
    QObject::connect(this->TMStop, SIGNAL(clicked()), this, SLOT(stopButtonEnabled()));
    QObject::connect(this->TMSrc, SIGNAL(textChanged()), this, SLOT(setSrcSize()));
    QObject::connect(this->TMSrc, SIGNAL(textChanged()), this, SLOT(clearFontSrc()));
    QObject::connect(this->speedSlider, SIGNAL(valueChanged(int)), this, SLOT(changeSpeed()));
}

void STuring::changeSpeed() {
    int spd = 100 - speedSlider->value() + 10;
    speed = spd;
}

void STuring::run() {
    TMStop->setEnabled(true);
    TMRunBtn->setEnabled(false);
    isRunning = true;
    stopped = false;
    stack_src.clear();
    now_state = "00";

    QString tmp1 = TMLine->text();
    line = tmp1.toStdString();

    pointer = line.size();
    line.push_back(' ');

    QString tmp2 = TMSrc->toPlainText();
    QStringList src_list = tmp2.split('\n');

    for(int i = 0; i < src_list.size(); ++i) {
        QString tmp3 = src_list.at(i);
        string cmd = tmp3.toStdString();
        cmd = uncomment(cmd);
        if(cmd.size() > 0) {
            stack_src.push_back(cmd);
        }
    }

    errors_test();

    if(!stopped) {
        go();
        print_result();
        //qDebug() << "Success!" << endl;
    }

    isRunning = false;
    TMStop->setEnabled(false);
    TMRunBtn->setEnabled(true);

}

void STuring::clearFontSrc() {
    TMSrc->font().cleanup();
    TMSrc->setFont(fontsrc);
}

bool STuring::errors_test() {
    int s = 0;
    for(int i = 0; i < stack_src.size(); ++i) {
        string state = get_state(stack_src[i]);
        string read_letter = get_read_letter(stack_src[i]);
        string write_letter = get_write_letter(stack_src[i]);
        string next_state = get_next_state(stack_src[i]);

        if(state.size() == 0 || read_letter.size() == 0 || read_letter.size() > 1 || write_letter.size() == 0 || write_letter.size() > 1 || next_state.size() == 0) {
            Error::error(i);
            stopped = true;
            ++s;
        }
    }
}

void STuring::stopButtonEnabled() {
    isRunning = false;

    TMStop->setEnabled(false);
    TMRunBtn->setEnabled(true);
}

void STuring::go() {
    TMLine->setReadOnly(true);
    TMRunBtn->setDisabled(true);
    for(int i = 0; i < stack_src.size() && !stopped && isRunning; ++i) {
        if(test_of_execute(stack_src[i])) {
            time.start();
            for(;time.elapsed() < speed;) {
                qApp->processEvents();
            }
            TMLine->setText(QString::fromStdString(line));
            execute_command(stack_src[i]);
            TMLine->setSelection(pointer, 1);
            i = -1;
        }
        if(i == stack_src.size() - 1) {
            Error::undefined_transition(now_state, line[pointer]);
            i = -1;
            stopped = true;
        }
    }
    TMLine->setReadOnly(false);
    TMRunBtn->setDisabled(false);
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

    int num_chars = TMSrc->document()->characterCount() - 1;
    QString num_chars_s = QString::number(num_chars);

    str += num_chars_s;
    str += "; Строки: ";

    int num_strings = TMSrc->document()->lineCount();
    QString num_strings_s = QString::number(num_strings);

    str += num_strings_s;
    str += ".";

    info_lbl->setText(str);
}

string STuring::get_state(string& cmd) {return get(cmd, 0);}
string STuring::get_read_letter(string& cmd) {return get(cmd, 1);}
string STuring::get_write_letter(string& cmd) {return get(cmd, 2);}
string STuring::get_next_state(string& cmd) {return get(cmd, 3);}

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

bool STuring::validation_command_test(string& cmd) {
    return true;
}

bool STuring::test_of_execute(string& cmd) {
    string state = get_state(cmd);
    string read_letter = get_read_letter(cmd);

    return state == now_state && read_letter[0] == line[pointer];
}

void STuring::execute_command(string& cmd) {
    string write_letter = get_write_letter(cmd);
    string next_state = get_next_state(cmd);

    if(write_letter == ">") {move_right();}
    else if(write_letter == "<") {move_left();}
    else if(write_letter == "#") {stopped = true;}
    else {change_letter(write_letter[0]);}

    now_state = next_state;

    QString tmp = QString::fromStdString(line);
    //qDebug() << QString::fromStdString(line);
    TMLine->clear();
    TMLine->insert(tmp);

}

void STuring::change_letter(char let) {
    line[pointer] = let;
}

void STuring::move_right() {
    pointer++;
    if(pointer >= line.size()) {
        line.push_back(' ');
    }
}

void STuring::move_left() {
    if(pointer > 0) {
        pointer--;
    }
}

void STuring::print_result() {
    //qDebug() << QString::fromStdString(line) << endl;

    for(int i = 0; i < pointer; ++i) {
        //qDebug() << " ";
    }

    //qDebug() << "^" << endl << endl;
}
