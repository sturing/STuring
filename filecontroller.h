#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <QFileDialog>
#include <QTextStream>
#include <string>
#include <QDebug>

using namespace std;

class FileController : public QObject
{
    Q_OBJECT
    QFile* file;
    QString path;
    bool fileOpenned;

    QString src, line;
    QVector<QString>lines;
public:
    explicit FileController(QObject *parent = 0);
    ~FileController();

signals:
    void opennedFile(QString src, QString line);
    void saveFileSign();
    void sendPath(QString);
public slots:
    QString getPath(QString p);
    void clear();
    void openDialogEnable();
    void saveDialogEnable();
    void saveFile(QString src, QString line);
    void createNewFile();
    QString getPathString();
    void openFromPath(QString);
};

#endif // FILECONTROLLER_H
