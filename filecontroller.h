#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <QFileDialog>
#include <QTextStream>

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

signals:
    void opennedFile(QString src, QString line);
    void savedFile();
public slots:
    void openDialogEnable();
    void saveDialogEnable();
    void createNewFile();
    //QString getLine();
    //QString getSrc();
};

#endif // FILECONTROLLER_H
