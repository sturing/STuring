#include "filecontroller.h"

FileController::FileController(QObject *parent) : QObject(parent)
{
    fileOpenned = 0;
}

void FileController::clear() {
    src.clear();
    lines.clear();
    line.clear();
    path.clear();
}

void FileController::openDialogEnable() {
    clear();
    path = QFileDialog::getOpenFileName(0, "Открыть файл...", "", "*.stur");

    file = new QFile(path);

    if(file->open(QIODevice::ReadWrite)) {
        QTextStream tStream(file);
        QString fileData = tStream.readAll();
        QStringList list = fileData.split('\n');

        for(int i = 0; i < list.size(); ++i) {
            lines.push_back(list.at(i));
        }

        if(lines.size() >= 1) {
            line = lines[0];
            for(int i = 1; i < lines.size(); ++i) {
                src.push_back(lines[i]);
                src.push_back('\n');
            }
        }

        fileOpenned = 1;
    }

    emit opennedFile(src, line);
}

void FileController::saveFile(QString src, QString line) {
    if(path.isEmpty()) {saveDialogEnable();}
    else {
        QFile file(path);
        file.open(QIODevice::ReadWrite);
        //file.write(QString::fromline);
        //file.write('\n');
        //file.write(src);
    }
}

void FileController::saveDialogEnable() {
    lines.clear();

    path = QFileDialog::getSaveFileName(0, "Сохранить файл как...", "", "*.stur");

    file = new QFile(path);

    file->open(QIODevice::ReadWrite);
}

void FileController::createNewFile() {
    clear();

    emit opennedFile(src, line);
}
