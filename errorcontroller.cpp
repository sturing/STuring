#include "errorcontroller.h"

ErrorController::ErrorController(QString src_, QString line_) : src(src_), line(line_), errorsHave(0)
{
    QStringList commandList = src.split('\n');

    for(int i = 0; i < commandList.size(); ++i) {
        cmd.push_back(commandList.at(i));
        cmd[i] = uncomment(cmd[i]);
    }

}

ErrorController::ErrorController() : line(""), errorsHave(0) {

}

QString ErrorController::errorTest() {
    /*
     * Типы ошибок
     *
     * 1) Использование запрещенного символа в ленте МТ. Запрещенные символы: (>,<,#)
     *  "> Использование запрещенного символа '#' в ленте МТ. Нельзя использовать эти символы: (#,>,<)"
     * 2) Дублирование команд
     *  "> Команды в строках 5, 7 повторяются. Удалите повторяющиеся команды."
     * 3) Переход в несуществующее состояние
     *  "> Состояние "04" не определено"
     * 4) Ошибка синтаксиса (нехватка параметров)
     *  "> Не хватает параметров (1) в строке 34"
     * 5) Переизбыток параметров
     *  "> Слишком много параметров (2) в строке 21"
     * 6) Использование запрещенного символа в параметрах 1/3 команды МТ
     * "> Использование запрещенного символа '<' для параметра (1) в строке 17"
     * 7) Использование слишком длинных параметров (для 1 и 3)
     * "> Использование слишком длинного аргумента в параметре (3) в строке 52"
     *
     * */

    //Проверка ленты МТ на неправильные параметры
    errorString += errorTest1();
    errorString += errorTest2();
    errorString += errorTest3();

    errorsHave = !errorString.isEmpty();

    return errorString;

}

bool ErrorController::getErrorTest() {
    return errorsHave;
}

QString ErrorController::errorTest1() { //Ошибки синтаксиса в ленте МТ (1)
    QString res = "> Использование запрещенных символов (#, <, >) в ленте МТ.\n";

    for(int i = 0; i < line.size(); ++i) {
        if(line[i] == '<' || line[i] == '>' || line[i] == '#') {return res;}
    }

    return "";

}

QString ErrorController::errorTest2() { //Повторение команд (5)
    QString res;

    for(int i = 0; i < cmd.size(); ++i) {
        for(int j = 0; j < cmd.size(); ++j) {
            if(!cmd[i].isEmpty() &&  !cmd[i].isEmpty() && i < j) {
                if(cmd[i] == cmd[j]) {
                    res += "> Команды в строках ";
                    res += QString::number(i + 1);
                    res += " и ";
                    res += QString::number(j + 1);
                    res += " повторяются. Удалите повторяющиеся команды.\n";
                }
            }
        }
    }

    return res;
}

QString ErrorController::errorTest3() { //Состояния (4)
    QString res;

    QVector<QString>inputState;
    for(int i = 0; i < cmd.size(); ++i) {
        inputState.push_back(getState(cmd[i]));
    }

    QVector<QString>outputState;
    for(int i = 0; i < cmd.size(); ++i) {
        outputState.push_back(getNextState(cmd[i]));
    }

    for(int i = 0; i < inputState.size(); ++i) {
        if(inputState[i] == "00") {break;}
        if(i == inputState.size() - 1) {
            res += "> Точки входа (состояния \'00\') не существует!\n";

            return cmd;
        }
    }

    for(int i = 0; i < inputState.size(); ++i) {
        for(int j = 0; j < outputState.size(); ++j) {
                if(inputState[i] == outputState[j] || inputState[i] == "00") {break;}
                if(j == inputState.size() - 1) {
                    res += "> Перехода в состояние \'";
                    res += inputState[i];
                    res += "\' не существует.\n";
                }
        }
    }

    for(int i = 0; i < outputState.size(); ++i) {
        for(int j = 0; j < inputState.size(); ++j) {
                if(outputState[i] == inputState[j]) {break;}
                if(j == outputState.size() - 1) {
                    res += "> Состояния \'";
                    res += outputState[i];
                    res += "\' не существует.\n";
                }
        }
    }

    return res;


}

QString ErrorController::errorTest4() { //Синтаксис (2) - лишние параметры
    QString res;

    for(int i = 0; i < cmd.size(); ++i) {
        if(getExtraParametres(cmd[i]) > 0) {
            res += "> Лишние параметры (";
            res += QString::number(getExtraParametres(cmd[i]));
            res += ") в команде на строке ";
            res += QString::number(i);
            res += "\n"
        }

        else if(getExtraParametres(cmd[i]) < 0) {
            res += "> Лишние параметры (";
            res += QString::number(-getExtraParametres(cmd[i]));
            res += ") в команде на строке ";
            res += QString::number(i);
            res += "\n"
        }
    }


}

QString ErrorController::errorTest5() { //Синтаксис (3) - нехватка аргументов
    /*for(int i = 0;) {

    }*/
}

QString ErrorController::errorTest6() {

}

QString ErrorController::errorTest7() {

}

int ErrorController::getExtraParametres(QString s) {
    int c = 0;

    for(int i = 0; i < s; ++i) {
        if(s[i] == ',') ++c;
    }

    return s - 3;
}
