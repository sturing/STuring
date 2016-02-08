#include "errorcontroller.h"

ErrorController::ErrorController(QString src_, QString line_) : src(src_), line(line_), errorsHave(0)
{
    QStringList commandList = src.split('\n');

    for(int i = 0; i < commandList.size(); ++i) {
        cmd.push_back(commandList.at(i));
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
     *  "> Переход в состояние "04" не определен"
     * 4) Ошибка синтаксиса (нехватка параметров)
     *  "> Не хватает параметров (1) в строке 34"
     * 5) Переизбыток параметров
     *  "> Слишком много параметров (2) в строке 21"
     * 6) Использование запрещенного символа в параметрах 1/3 команды МТ
     * "> Использование запрещенного символа '<' для параметра (1) в строке 17"
     * 7) Использование слишком длинных параметров (для 1 и 3)
     * "> Использование слишком длинного аргумента в параметре (3) в строке 52"
     * */

    //Проверка ленты МТ на неправильные параметры
    errorString += errorTest1();
    errorString += errorTest2();

    errorsHave = !errorString.isEmpty();

    return errorString;

}

bool ErrorController::getErrorTest() {
    return errorsHave;
}

QString ErrorController::errorTest1() {
    QString res = "> Использование запрещенных символов (#, <, >) в ленте МТ.\n";

    for(int i = 0; i < line.size(); ++i) {
        if(line[i] == '<' || line[i] == '>' || line[i] == '#') {return res;}
    }

    return "";

}

QString ErrorController::errorTest2() {
    QString res;

    for(int i = 0; i < cmd.size(); ++i) {
        for(int j = 0; j < cmd.size(); ++j) {
            if(!cmd[i].isEmpty() &&  !cmd[i].isEmpty() && i < j) {
                if(uncomment(cmd[i]) == uncomment(cmd[j])) {
                    res += "> Команды в строках ";
                    res += QString::number(i);
                    res += " и ";
                    res += QString::number(j);
                    res += " повторяются. Удалите повторяющиеся команды.\n";
                }
            }
        }
    }

    return res;
}

QString ErrorController::errorTest3() {

}

QString ErrorController::errorTest4() {

}

QString ErrorController::errorTest5() {

}

QString ErrorController::errorTest6() {

}

QString ErrorController::errorTest7() {

}
