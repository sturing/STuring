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

QString FileController::getPathString() {
    return path;
}

void FileController::openDialogEnable() {
    QString pathTmp = QFileDialog::getOpenFileName(0, "Открыть файл...", "", "*.stur");

    if(!pathTmp.isEmpty()) {
        clear();
        path = pathTmp;
        file = new QFile(path);

        if(file->open(QIODevice::ReadWrite)) {
            copyDataFromFile();
        }

        emit opennedFile(src, line);
        emit sendPath(path);
    }
}

void FileController::copyDataFromFile() {
    QTextStream tStream(file);
    QString fileData = tStream.readAll();
    QStringList list = fileData.split('\n');

    for(int i = 0; i < list.size(); ++i) {
        lines.push_back(list.at(i));
    }

    if(lines.size() >= 1) {
        line = lines[0];
        for(int i = 1; i < lines.size(); ++i) {
            if(i != 1) {src.push_back('\n');}

            src.push_back(lines[i]);
        }
    }

    fileOpenned = 1;
}

void FileController::openFromPath(QString p) {

    if(!p.isEmpty()) {
        clear();
        path = p;
        file = new QFile(path);

        if(file->open(QIODevice::ReadWrite)) {
            copyDataFromFile();
        }

        emit opennedFile(src, line);
        emit sendPath(path);
    }
}

void FileController::saveFile(QString src, QString line) {
    if(path.isEmpty()) {
        saveDialogEnable();
    }
    else {

        QFile file(path);
        file.open(QIODevice::ReadWrite);
        QByteArray srcBytes;
        QByteArray lineBytes;

        string lineStd = line.toStdString();
        for(int i = 0; i < lineStd.size(); ++i) {
            lineBytes.push_back(lineStd[i]);
        }

        string srcStd = src.toStdString();

        for(int i = 0; i < srcStd.size(); ++i) {
            srcBytes.push_back(srcStd[i]);
        }
        file.resize(0);

        file.write(lineBytes);
        file.write("\n");
        file.write(srcBytes);
    }
}

QString FileController::getPath(QString p) {
    if(p.size() >= 5) {
        if(p[p.size() - 1] == 'r' && p[p.size() - 2] == 'u' && p[p.size() - 3] == 't' && p[p.size() - 4] == 's' && p[p.size() - 5] == '.') {
            return p;
        } else {return p + ".stur";}
    } else {return p + ".stur";}
}

void FileController::saveDialogEnable() {
    QFileDialog sDialog;

    QString pathTmp = sDialog.getSaveFileName(0, tr("Сохранить файл как..."), "", tr("STuring files (*.stur)"));

    if(!pathTmp.isEmpty()) {
        lines.clear();
        path = pathTmp;
        emit saveFileSign();
        file = new QFile(path);

        QFileInfo info(*file);
        if(info.suffix().isEmpty()) {
            info.suffix() = ".stur";
        }

        file->open(QIODevice::ReadWrite);

        emit sendPath(path);
    }
}

void FileController::createNewFile() {
    clear();

    emit opennedFile(src, line);
    emit sendPath("Новый");
}

FileController::~FileController() {
    delete file;
}
